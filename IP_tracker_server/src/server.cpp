#include "../include/server.h"
#include <grpc++/grpc++.h>
#include <curl/curl.h>

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

    std::vector<data::Device> devices;
    std::string content;

    int i = 0;
    do {
        std::cout<<++i<<std::endl;
        stream->Read(&request);
        std::cout<<request.request()<<std::endl;

        /*buffer << file.rdbuf();
        content = buffer.str();*/
        
        do {
            content = router.getAllDevices();
            if(content == "failed") std::cout<<"FAILED!!!!"<<std::endl;
        } while (content == "failed");
        
        parser.parseData(content);
        devices = parser.getDevices();
        response.clear_devices();

        for(const auto &d: devices) {
            response.add_devices()->CopyFrom(d);
        }
        
        for(auto &d: response.devices()) {
            std::cout<<d.id() << " " << d.name() << " " << d.ip_address() << std::endl;
            std::cout << d.mac_address() << " " << d.is_online() << " " << d.is_blocked() <<" " << d.is_suspect() <<std::endl;
        }
        
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
