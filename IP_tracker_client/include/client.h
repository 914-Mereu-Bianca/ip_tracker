#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include "../build/proto_generated/ip_tracker.grpc.pb.h"
#include <grpc++/grpc++.h>
#include <grpcpp/grpcpp.h>

class MainClient {

public:

    MainClient(std::shared_ptr<grpc::Channel> channel);
    void runClient();
    void StreamData();
    bool Authenticate(const std::string& username, const std::string& password);
    inline bool isRunning() { return is_running_; }
    inline void Stop() { is_running_ = 0; }
       
private:

    std::unique_ptr<data::IPService::Stub> _stub;
    bool is_running_ = 1;

};

#endif  // _CLIENT_H_