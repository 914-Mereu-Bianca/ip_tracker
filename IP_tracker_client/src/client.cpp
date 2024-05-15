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
    data::Response response;

    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReaderWriter<data::Request, data::Response>> stream = _stub->StreamData(&context);
    
    request.set_request("");
    stream->Write(request);
    
    while (stream->Read(&response)) {  // true => it can continue reading, false => the message stream has ended
        
        for(auto &d: response.devices()) {
            std::cout<< d.mac_address() << " " << d.is_online() << " " << d.is_blocked() <<" " << d.is_suspect() << d.id() << " " << d.name() << " " << d.ip_address() <<std::endl;
        }
        
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));

        std::lock_guard<std::mutex> lock_1(data_mutex_);
        std::lock_guard<std::mutex> lock_2(request_mutex_);

        devices_ = response;
        request.set_request(request_);
        request.set_device_id(device_id_);
        stream->Write(request);
        request_ = "";
    }

    grpc::Status status = stream->Finish();
    if (!status.ok()) {
        std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

void MainClient::runClient() {
    read_data_thread_ = std::thread(&MainClient::StreamData, this);
}

data::Response MainClient::getDevices() {
    std::lock_guard<std::mutex> lock(data_mutex_);
    return devices_;
}

void MainClient::setRequest(const std::string &request, int device_id) {
    std::lock_guard<std::mutex> lock(request_mutex_);
    request_ = request;
    device_id = device_id;
}

MainClient::~MainClient() {
    if(read_data_thread_.joinable())
        read_data_thread_.join();
}