#include "../include/server.h"
#include <grpc++/grpc++.h>
#include <curl/curl.h>
#include <thread>
#include <mutex>

MainService::MainService(const std::string& ip, uint16_t port) : ip_(ip), port_(port) { 
    router_.setToken("%2BKIPjIk%5EP)D5oK%24)%7C6y0PT!5XcY8pf!8"); 
    get_devices_thread_ = std::thread(&MainService::runBackgroundGetDevices, this);
    get_blocked_devices_thread_ = std::thread(&MainService::runBackgroundGetBlockedDevices, this);
}

MainService::~MainService() {
    if (get_devices_thread_.joinable()) {
        get_devices_thread_.join();
    }
    if (get_blocked_devices_thread_.joinable()) {
        get_blocked_devices_thread_.join();
    }
}

grpc::Status MainService::Authenticate(grpc::ServerContext *context, const data::AuthRequest* request, data::AuthResponse* response)
{
    std::cout<<request->username()<< " "<<request->password()<<std::endl;
    if (request->username() == "user" && request->password() == "password") {
      response->set_success(true);
      response->set_message("Authentication successful");
      auth = 1;
    } else {
      response->set_success(false);
      response->set_message("Authentication failed");
    }
    return grpc::Status::OK;
}

std::string MainService::handleRequest(data::Request request) {
    if(request.request()!="")
        std::cout<<request.request()<<std::endl<<request.name()<<std::endl<<request.mac()<<std::endl;
    
    std::string response = "";

    if(request.request() == "Block") {
        std::unique_lock u_lock(request_mutex_);
        std::string name = request.name();
        std::string mac = request.mac();
        response = router_.blockDevice(name, mac);
        std::cout<<response<<std::endl;
    } else if (request.request() == "Unblock") {
        std::unique_lock u_lock(request_mutex_);
        std::string mac = request.mac();
        response = router_.unblockDevice(mac);
        std::cout<<response<<std::endl;
    }

    return response;
        
}


grpc::Status MainService::StreamData(grpc::ServerContext *context, grpc::ServerReaderWriter<data::Response, data::Request>* stream)
{
    data::Request request;
    data::Response response;

    int i = 0;
    do {
        
        stream->Read(&request);
        
        handleRequest(request);

        parser_.parseData(getAllDevicesResponse());
        parser_.parseBlockedDevices(getAllBlockedDevicesResponse());
        devices_ = parser_.getDevices();
        response.clear_devices();

        for(const auto &d: devices_) {
            response.add_devices()->CopyFrom(d);
        }
        
    } while (stream->Write(response));

    return grpc::Status();
}

void MainService::runServer()
{

    std::string server_address = ip_ + ":" + std::to_string(port_);
    
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(this);

    std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();

}

void MainService::runBackgroundGetDevices() {
    std::string response = "";
    while(is_running_) {

        std::unique_lock u_lock(request_mutex_);
        response = router_.getAllDevices();
        u_lock.unlock();

        if(response != "failed") {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(3));
            std::lock_guard lock(get_devices_mutex_);
            router_response_get_all_ = response;
        }   
    }
}

std::string MainService::getAllDevicesResponse() {
    std::lock_guard lock(get_devices_mutex_);
    return router_response_get_all_;
}

void MainService::runBackgroundGetBlockedDevices() {
    std::string response = "";
    while(is_running_) {

        std::unique_lock u_lock(request_mutex_);
        response = router_.getAllBlockedDevices();
        u_lock.unlock();

        if(response != "failed") {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(3));
            std::lock_guard lock(get_blocked_devices_mutex_);
            router_response_get_all_blocked_ = response;
        }   
    }
}

std::string MainService::getAllBlockedDevicesResponse() {
    std::lock_guard lock(get_blocked_devices_mutex_);
    return router_response_get_all_blocked_;
}