#include "../include/server.h"
#include "../include/data_parser.h"
#include <grpc++/grpc++.h>

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

void MainService::RunServer()
{

    std::string server_address = ip_ + ":" + std::to_string(port_);
    
    grpc::ServerBuilder builder;
    
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    
    builder.RegisterService(this);

    std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};

    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();

}
