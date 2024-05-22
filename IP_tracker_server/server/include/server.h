#ifndef _SERVER_H_
#define _SERVER_H_

#include "../../build/proto_generated/ip_tracker.grpc.pb.h"
#include "../../build/proto_generated/ip_tracker.pb.h"
#include "../../router_communication/include/request_handler.h"
#include "../../mail_communication/include/send_mail.h"
#include "../../parser/include/data_parser.h"
#include "../include/admin.h"
#include <thread>
#include <mutex>
#include <grpc++/grpc++.h>

class MainService : public data::IPService::Service {
public:
    MainService(const std::string& ip, uint16_t port, Admin admin);
    ~MainService();
    void runServer();
    void checkNewDevices();
    void updateDevices();
    inline void shutdown() { server->Shutdown(); }

private:

    grpc::Status StreamData(grpc::ServerContext* context, grpc::ServerReaderWriter<data::Response, data::Request>* stream) override;
    grpc::Status Authenticate(grpc::ServerContext* context, const data::Credentials* request, data::OperationResponse* response) override;
    grpc::Status ChangeCredentials(grpc::ServerContext* context, const data::NewCredentials* request, data::OperationResponse* response) override;
    grpc::Status ChangeEmail(grpc::ServerContext* context, const data::Email* request, data::OperationResponse* response) override;

    std::string ip_;
    uint16_t port_;
    bool is_running_ = 1;

    Parser parser_;
    RequestHandler request_handler_;
    SendMail mail_;
    Admin admin_;

    std::thread update_devices_;
    std::mutex devices_mutex_;
    std::vector<data::Device> devices_;
    std::vector<data::Device> old_devices_;
    std::vector<data::Device> new_devices_;
    std::unique_ptr<grpc::Server> server;

};

#endif // _SERVER_H_