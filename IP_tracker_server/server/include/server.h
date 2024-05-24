#ifndef _SERVER_H_
#define _SERVER_H_

#include "../../build/proto_generated/ip_tracker.grpc.pb.h"
#include "../../build/proto_generated/ip_tracker.pb.h"
#include "../include/server_controller.h"
#include "../include/admin.h"
#include <thread>
#include <mutex>
#include <grpc++/grpc++.h>

class MainService : public data::IPService::Service {
public:
    MainService(const std::string& ip, uint16_t port, Admin admin);
    ~MainService();
    void runServer();
    inline void shutdown() { server->Shutdown(); }

private:

    grpc::Status StreamData(grpc::ServerContext* context, grpc::ServerReaderWriter<data::Response, data::Request>* stream) override;
    grpc::Status Authenticate(grpc::ServerContext* context, const data::Credentials* request, data::OperationResponse* response) override;
    grpc::Status ChangeCredentials(grpc::ServerContext* context, const data::NewCredentials* request, data::OperationResponse* response) override;
    grpc::Status ChangeEmail(grpc::ServerContext* context, const data::Email* request, data::OperationResponse* response) override;

    std::string ip_;
    uint16_t port_;
    bool is_running_ = 1;

    ServerController server_controller_;
    Admin admin_;

    std::vector<data::Device> devices_;
    std::unique_ptr<grpc::Server> server;

};

#endif // _SERVER_H_