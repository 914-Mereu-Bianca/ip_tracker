#include <grpc++/grpc++.h>
#include "../include/client.h"

MainClient::MainClient(std::shared_ptr<grpc::Channel> channel)
: _stub(data::IPService::NewStub(channel))
{
}

bool MainClient::Authenticate(const std::string& username, const std::string& password)
{

    data::Credentials request;
    request.set_username(username);
    request.set_password(password);

    data::OperationResponse response;
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
        
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));

        std::lock_guard<std::mutex> lock_1(data_mutex_);
        std::lock_guard<std::mutex> lock_2(request_mutex_);

        devices_ = response;

        request.set_request(request_);
        request.set_name(name_);
        request.set_mac(mac_);
        stream->Write(request);
        request_ = "";
    }

    grpc::Status status = stream->Finish();
    if (!status.ok()) {
        std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

data::OperationResponse MainClient::ChangeCredentials(const std::string& username, const std::string& password, const std::string& current_password, bool reset) {
    data::Credentials request;
    request.set_username(username);
    request.set_password(password);
    request.set_old_password(current_password);
    request.set_reset(reset);

    data::OperationResponse response;
    grpc::ClientContext context;

    grpc::Status status = _stub->ChangeCredentials(&context, request, &response);

    if (status.ok()) {
      std::cout << "RPC send successfully: " << response.message() << std::endl;
      return response;
    } else {
      std::cout << "RPC failed: " << status.error_message() << std::endl;
      return response;
    }
}

data::OperationResponse MainClient::ChangeEmail(const std::string& email, const std::string& password) {
    data::Email request;
    request.set_email(email);
    std::cout<<password<<std::endl;
    request.set_password(password);

    data::OperationResponse response;
    grpc::ClientContext context;

    grpc::Status status = _stub->ChangeEmail(&context, request, &response);

    if (status.ok()) {
      std::cout << "RPC send successfully: " << response.message() << std::endl;
      return response;
    } else {
      std::cout << "RPC failed: " << status.error_message() << std::endl;
      return response;
    }
}

data::OperationResponse MainClient::ManageDevice(const std::string& operation, const std::string& name, const std::string &mac) {
    data::Request request;
    request.set_request(operation);
    request.set_name(name);
    request.set_mac(mac);
    data::OperationResponse response;
    grpc::ClientContext context;

    grpc::Status status = _stub->ManageDevice(&context, request, &response);

    if (status.ok()) {
      std::cout << "RPC send successfully: " << response.message() << std::endl;
      return response;
    } else {
      std::cout << "RPC failed: " << status.error_message() << std::endl;
      return response;
    }
}

void MainClient::runClient() {
    read_data_thread_ = std::thread(&MainClient::StreamData, this);
}

data::Response MainClient::getDevices() {
    std::lock_guard<std::mutex> lock(data_mutex_);
    return devices_;
}

void MainClient::setRequest(const std::string &request, const std::string &name, const std::string &mac) {
    std::lock_guard<std::mutex> lock(request_mutex_);
    request_ = request;
    name_ = name;
    mac_ = mac;
}

MainClient::~MainClient() {
    if(read_data_thread_.joinable())
        read_data_thread_.join();
}