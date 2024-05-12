#include "auth_client_impl.h"
#include <grpc++/grpc++.h>


AuthClientImpl::AuthClientImpl(std::shared_ptr<grpc::Channel> channel)
: _stub(data::IPService::NewStub(channel))
{
}

bool AuthClientImpl::Authenticate(const std::string& username, const std::string& password)
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

