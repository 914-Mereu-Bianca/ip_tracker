#ifndef _AUTH_CLIENT_IMPL_H_
#define _AUTH_CLIENT_IMPL_H_

#include <memory>
#include <grpcpp/grpcpp.h>
#include "../build/proto_generated/auth.grpc.pb.h"

class AuthClientImpl {

public:
    AuthClientImpl(std::shared_ptr<grpc::Channel> channel);
    bool Authenticate(const std::string& username, const std::string& password);
    inline bool isRunning() { return is_running_; }
    inline void Stop() { is_running_ = 0; }
private:
    std::unique_ptr<AuthService::Stub> _stub;
    bool is_running_ = 1;

};


#endif // _AUTH_CLIENT_IMPL_H_