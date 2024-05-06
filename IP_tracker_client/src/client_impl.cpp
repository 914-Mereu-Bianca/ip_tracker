#include <grpc++/grpc++.h>
#include "../include/client_impl.h"

ClientImpl::ClientImpl(std::shared_ptr<grpc::Channel> channel)
: _stub(data::IPService::NewStub(channel))
{
}

void ClientImpl::StreamData()
{

    data::Request request;
    request.set_request("a");

    // send request
    data::Response response;
    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReaderWriter<data::Request, data::Response>> stream = _stub->StreamData(&context);
    
    stream->Write(request);
    
    stream->Read(&response);
    std::cout<<response.response()<<std::endl;

    /*while (stream->Read(&response)) {  // true => it can continue reading, false => the message stream has ended
    
        std::cout<<response.response()<<std::endl;

        stream->Write(request);
    }*/

    grpc::Status status = stream->Finish();
    // Handle response
    if (!status.ok()) {
        std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
    }
    
}

void ClientImpl::runClient() {
    
}