#include <grpc++/grpc++.h>
#include "../include/auth_server_impl.h"
#include <chrono>
#include <thread>
#include <iostream>

AuthServiceImpl::AuthServiceImpl(const std::string &ip, uint16_t port)
    : ip_(ip), port_(port) {}


grpc::Status AuthServiceImpl::Authenticate(grpc::ServerContext *context, const AuthRequest* request, AuthResponse* response)
{
    std::cout<<request->username()<< " "<<request->password()<<std::endl;
    if (request->username() == "user" && request->password() == "password") {
      response->set_success(true);
      response->set_message("Authentication successful");
    } else {
      response->set_success(false);
      response->set_message("Authentication failed");
    }
    return grpc::Status::OK;
}


void AuthServiceImpl::RunServer()
{

    std::string server_address = ip_ + ":" + std::to_string(port_);
    
    grpc::ServerBuilder builder;
    
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    
    builder.RegisterService(this);

    std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};

    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();

}

