#ifndef _AUTH_SERVER_IMPL_H_
#define _AUTH_SERVER_IMPL_H_

#include "../build/proto_generated/auth.grpc.pb.h"

class AuthServiceImpl : public AuthService::Service {
public:
    AuthServiceImpl(const std::string& ip, uint16_t port);
        
    void RunServer();

private:

    // This method is called when the client makes the request
    grpc::Status Authenticate(grpc::ServerContext* context, const AuthRequest* request, AuthResponse* response) override;
    
    std::string ip_;
    uint16_t port_;
};

#endif // _AUTH_SERVER_IMPL_H_