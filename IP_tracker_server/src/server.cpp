#include "../include/server.h"
#include <grpc++/grpc++.h>
#include <curl/curl.h>
#include <thread>
#include <mutex>

MainService::MainService(const std::string& ip, uint16_t port) : ip_(ip), port_(port) {
    update_devices_ = std::thread(&MainService::updateDevices, this);
}

MainService::~MainService() {
    is_running_ = false;
    if(update_devices_.joinable()) {
        update_devices_.join();
    }
    request_handler_.stop();
}

grpc::Status MainService::Authenticate(grpc::ServerContext *context, const data::Credentials* request, data::OperationResponse* response) {
    std::cout<<request->username()<< " "<<request->password()<<std::endl;

    if (admin_.computeHash(request->username()) == admin_.getUsernameHashed() && admin_.computeHash(request->password()) == admin_.getPasswordHashed()) {
        response->set_success(true);
        response->set_message("Authentication successful");
    } else {
        response->set_success(false);
        response->set_message("Authentication failed");
    }
    
    return grpc::Status::OK;
}


grpc::Status MainService::StreamData(grpc::ServerContext *context, grpc::ServerReaderWriter<data::Response, data::Request>* stream) {

    data::Request request;
    data::Response response;

    do {
        // Read the request from the client and send it to be handled
        stream->Read(&request);
        request_handler_.handleRequest(request);

        response.clear_devices();

        for(const auto &d: devices_) {
            response.add_devices()->CopyFrom(d);
        }
        // The devices are send to the client
    } while (stream->Write(response));

    return grpc::Status();
}

void MainService::runServer() {

    std::string server_address = ip_ + ":" + std::to_string(port_);
    
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(this);
    // initialize the server declared in header file
    server = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();

}

void MainService::updateDevices() {
    // The parser gets the data from the handler 
    // to get the devices together with information about each of them
    std::string response;
    while (is_running_) {
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(4));
        response = request_handler_.getAllDevicesResponse();
        if(response != "")
            parser_.parseData(response);
        response = request_handler_.getAllBlockedDevicesResponse();
        if(response != "") 
            parser_.parseBlockedDevices(response);

        old_devices_ = devices_;
        devices_ = parser_.getDevices();
        checkNewDevices();
    }
}

void MainService::checkNewDevices() {

    if(old_devices_.size() && old_devices_.size() != devices_.size()) {
        for (const auto& newDevice : devices_) {
            // Check if newDevice's MAC address is not in old_devices_
            if (std::find_if(old_devices_.begin(), old_devices_.end(), 
                            [&newDevice](const auto& oldDevice) {
                                return oldDevice.mac_address() == newDevice.mac_address();
                            }) == old_devices_.end()) {
                new_devices_.push_back(newDevice);
                std::cout<<newDevice.mac_address()<<std::endl;
            }
        }
        for (const auto& device : new_devices_) {
            data::Request request;
            request.set_request("Block");
            request.set_mac(device.mac_address());
            request_handler_.handleRequest(request);
            mail_.send();
        }
        new_devices_.clear();
    }

}
