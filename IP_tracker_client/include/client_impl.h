#ifndef _CLIENT_IMPL_H_
#define _CLIENT_IMPL_H_

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include "../build/proto_generated/data.grpc.pb.h"

class ClientImpl {

public:

    ClientImpl(std::shared_ptr<grpc::Channel> channel);
    void runClient();
    void StreamData();
       
private:

    std::unique_ptr<data::IPService::Stub> _stub;

};

#endif  // _CLIENT_SYNC_IMPL_H_