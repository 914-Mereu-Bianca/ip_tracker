#ifndef _SERVER_H_
#define _SERVER_H_

#include "../build/proto_generated/ip_tracker.grpc.pb.h"
#include "../build/proto_generated/ip_tracker.pb.h"

class MainService : public data::IPService::Service {
public:
    MainService(const std::string& ip, uint16_t port) : ip_(ip), port_(port) {}
    void RunServer();

private:

    grpc::Status StreamData(grpc::ServerContext* context, grpc::ServerReaderWriter<data::Response, data::Request>* stream) override;
    grpc::Status Authenticate(grpc::ServerContext* context, const data::AuthRequest* request, data::AuthResponse* response) override;

    std::string ip_;
    uint16_t port_;
    bool auth = 0;

};

#endif // _SERVER_H_