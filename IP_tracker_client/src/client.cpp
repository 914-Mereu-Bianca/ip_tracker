#include <grpc++/grpc++.h>
#include "../include/client.h"

MainClient::MainClient(std::shared_ptr<grpc::Channel> channel)
: _stub(data::IPService::NewStub(channel))
{
}

bool MainClient::Authenticate(const std::string& username, const std::string& password)
{

    data::AuthRequest request;
    request.set_username(username);
    request.set_password(password);

    data::AuthResponse response;
    grpc::ClientContext context;

    grpc::Status status = _stub->Authenticate(&context, request, &response);

    if (status.ok()) {
      std::cout << "Authentication status: " << response.message() << std::endl;
      return response.success();
    } else {
      std::cout << "RPC failed: " << status.error_message() << std::endl;
      return false;
    }
    
}

void MainClient::StreamData()
{
    
    data::Request request;
    request.set_request("a");

    // send request
    data::Response response;
    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReaderWriter<data::Request, data::Response>> stream = _stub->StreamData(&context);
    std::cout<<"cl"<< std::endl;
    stream->Write(request);
    std::cout<<"cll"<< std::endl;
    while (stream->Read(&response)) {  // true => it can continue reading, false => the message stream has ended
        std::cout<<response.devices_size()<< std::endl;
        
        for(auto &d: response.devices()) {
            std::cout<<d.id() << " " << d.name() << " " << d.ip_address() << " " << d.mac_address() << " " << d.is_online() << " " << d.is_blocked() <<" " << d.is_suspect() <<std::endl;
        }
        //data_mutex_.lock();
        devices_ = response;

        //data_mutex_.unlock();
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(5));
        stream->Write(request);
    }

    grpc::Status status = stream->Finish();
    // Handle response
    if (!status.ok()) {
        std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void MainClient::runClient() {
    read_data_thread_ = std::thread(&MainClient::StreamData, this);
}

data::Response MainClient::getDevices() {
    //data_mutex_.lock();
    return devices_;
    //data_mutex_.unlock();
}

MainClient::~MainClient() {
    if(read_data_thread_.joinable())
        read_data_thread_.join();
}