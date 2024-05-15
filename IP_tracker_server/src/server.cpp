#include "../include/server.h"
#include <grpc++/grpc++.h>
#include <curl/curl.h>
#include <thread>
#include <mutex>

MainService::MainService(const std::string& ip, uint16_t port) : ip_(ip), port_(port) { 
    router_.setToken("z%3E%3Eh64h%7C%2B%5Bo%2B%7BlWP9X0pA3PtuDAKFkG!"); 
    router_thread_ = std::thread(&MainService::runBackgroundRouter, this);
}

MainService::~MainService() {
    if (router_thread_.joinable()) {
        router_thread_.join();
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

grpc::Status MainService::StreamData(grpc::ServerContext *context, grpc::ServerReaderWriter<data::Response, data::Request>* stream)
{
    data::Request request;
    data::Response response;

    int i = 0;
    do {
        std::cout<<++i<<std::endl;
        stream->Read(&request);
        std::cout<<request.request()<<" "<<request.device_id()<<std::endl;
        
        parser_.parseData(getRouterResponse());
        devices_ = parser_.getDevices();
        response.clear_devices();

        for(const auto &d: devices_) {
            response.add_devices()->CopyFrom(d);
        }
        
        for(auto &d: response.devices()) {
            std::cout<<d.id() << " " << d.name() << " " << d.ip_address() << std::endl;
            std::cout << d.mac_address() << " " << d.is_online() << " " << d.is_blocked() <<" " << d.is_suspect() <<std::endl;
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

void MainService::runBackgroundRouter() {
    int i = 0;
    std::string response = "";
    while(is_running_) {

        std::cout<<++i<<std::endl;

        response = router_.getAllDevices();

        if(response != "failed") {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(3));
            std::lock_guard lock(data_mutex_);
            router_response_ = response;
        }   
    }
}

std::string MainService::getRouterResponse() {
    std::lock_guard lock(data_mutex_);
    return router_response_;
}