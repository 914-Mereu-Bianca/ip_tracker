#ifndef _SERVER_IMPL_H_
#define _SERVER_IMPL_H_

#include "../build/proto_generated/data.pb.h"
#include "../build/proto_generated/data.grpc.pb.h"

class ServiceImpl : public data::IPService::Service {
public:
    ServiceImpl(const std::string& ip, uint16_t port);
        
    void RunServer();

private:

    // This method is called when the client makes the request
    grpc::Status StreamData(grpc::ServerContext* context, grpc::ServerReaderWriter<data::Response, data::Request>* stream) override;
    
    std::string ip_;
    uint16_t port_;
};

#endif // _SERVER_IMPL_H_