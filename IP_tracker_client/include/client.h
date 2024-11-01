#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "../build/proto_generated/ip_tracker.grpc.pb.h"
#include <grpc++/grpc++.h>
#include <grpcpp/grpcpp.h>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

class MainClient {

public:

    MainClient(std::shared_ptr<grpc::Channel> channel);
    ~MainClient();
    void runClient();
    void StreamData();
    bool Authenticate(const std::string& username, const std::string& password);
    data::OperationResponse ChangeCredentials(const std::string& username, const std::string& password, const std::string& current_password, bool reset);
    data::OperationResponse ChangeEmail(const std::string& email, const std::string& password);
    data::OperationResponse ManageDevice(const std::string& operation, const std::string& name, const std::string &mac);
    inline bool isAuth() { return is_auth_; }
    inline void setAuth(bool auth) { is_auth_ = auth; }
    inline void Stop() { is_running_ = 0; }
    inline bool isRunning() { return is_running_; }
    data::Response getDevices();
    void setRequest(const std::string &request, const std::string &name, const std::string &mac);
       
private:

    std::unique_ptr<data::IPService::Stub> _stub;
    data::Response devices_;
    std::thread read_data_thread_;
    std::mutex data_mutex_;
    std::mutex request_mutex_;
    bool is_auth_ = 0;
    bool is_running_ = 1;
    std::string request_ = "";
    std::string name_ = "";
    std::string mac_ = "";

};

#endif  // _CLIENT_H_