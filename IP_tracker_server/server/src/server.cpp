#include "../include/server.h"
#include <grpc++/grpc++.h>
#include <curl/curl.h>
#include <thread>
#include <mutex>

MainService::MainService(const std::string& ip, uint16_t port) : ip_(ip), port_(port), SQL_connector_(std::make_shared<SqlConnector>()), admin_(SQL_connector_), server_controller_(SQL_connector_) {
}

MainService::~MainService() {
    is_running_ = false;
}

grpc::Status MainService::Authenticate(grpc::ServerContext *context, const data::Credentials* request, data::OperationResponse* response) {
    std::cout<<request->username()<< " "<<request->password()<<std::endl;

    if (admin_.checkUsername(request->username()) && admin_.checkPassword(request->password())) {
        response->set_success(true);
        response->set_message("Authentication successful");
    } else {
        response->set_success(false);
        response->set_message("Authentication failed");
    }
    
    return grpc::Status::OK;
}

grpc::Status MainService::ChangeCredentials(grpc::ServerContext *context, const data::Credentials* request, data::OperationResponse* response) {
    
    if (request->reset()) {
        srand(static_cast<unsigned int>(time(0)));
        std::string username = "admin" + std::to_string(100 + rand() % 900);
        std::string password = "admin" + std::to_string(100 + rand() % 900);
        admin_.saveCredentials(username, password);
        server_controller_.resetCredetials(username, password);
    }
    else {
        if (request->password() != "") {
            if(admin_.checkPassword(request->old_password())) {
                admin_.saveCredentials(request->username(), request->password());
                response->set_success(true);
                response->set_message("Success");
            } else {
                response->set_success(false);
                response->set_message("Wrong current password");
            }
        } else {
            response->set_success(false);
            response->set_message("New password cannot be empty!");
        }
    }
    return grpc::Status::OK;
}

grpc::Status MainService::ChangeEmail(grpc::ServerContext *context, const data::Email* request, data::OperationResponse* response) {
    if (request->email() != "") {
        if(admin_.checkPassword(request->password())) {
            server_controller_.changeMail(request->email());
            std::cout<<request->email()<<std::endl;
            response->set_success(true);
            response->set_message("Success");
        } else {
            response->set_success(false);
            response->set_message("Wrong password");
        }
    } else {
        response->set_success(false);
        response->set_message("Wrong email format!");
    }
    return grpc::Status::OK;
}

grpc::Status MainService::ManageDevice(grpc::ServerContext *context, const data::Request* request, data::OperationResponse* response) {
    std::cout<<request->request()<<" " <<request->name()<<" "<<request->mac()<<std::endl;
    if (request->request() == "rename") {
        server_controller_.renameDevice(*request);
    } else if (request->request() == "delete") {
        server_controller_.deleteDevice(request->mac());
    }
    return grpc::Status::OK;
}

grpc::Status MainService::StreamData(grpc::ServerContext *context, grpc::ServerReaderWriter<data::Response, data::Request>* stream) {

    data::Request request;
    data::Response response;

    do {
        // Read the request from the client and send it to be handled
        stream->Read(&request);
        
        server_controller_.sendHandleRequest(request);
        response.clear_devices();
        devices_ = server_controller_.getDevices();

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
