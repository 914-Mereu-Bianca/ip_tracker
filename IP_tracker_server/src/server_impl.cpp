#include <grpc++/grpc++.h>
#include "../include/server_impl.h"
#include "../include/data_parser.h"
#include <chrono>
#include <thread>
#include <iostream>

ServiceImpl::ServiceImpl(const std::string &ip, uint16_t port)
    : ip_(ip), port_(port) {}


grpc::Status ServiceImpl::StreamData(grpc::ServerContext *context, grpc::ServerReaderWriter<data::Response, data::Request>* stream)
{
    data::Request request;
    data::Response response;

    std::ifstream file("../data/data.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    Parser parser;
    parser.parseData(content);

    std::vector<data::Device> devices = parser.getDevices();
    
    for(const auto &d: devices) {
        response.add_devices()->CopyFrom(d);
    }

    do {
        stream->Read(&request);
        std::cout<<request.request()<<std::endl;

    } while (stream->Write(response));

    return grpc::Status();
}


void ServiceImpl::RunServer()
{

    std::string server_address = ip_ + ":" + std::to_string(port_);
    
    grpc::ServerBuilder builder;
    
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    
    builder.RegisterService(this);

    std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};

    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();

}

