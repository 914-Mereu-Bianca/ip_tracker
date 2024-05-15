#ifndef _SERVER_H_
#define _SERVER_H_

#include "../build/proto_generated/ip_tracker.grpc.pb.h"
#include "../build/proto_generated/ip_tracker.pb.h"
#include "../include/data_parser.h"
#include "../include/router.h"
#include <thread>
#include <mutex>

class MainService : public data::IPService::Service {
public:
    MainService(const std::string& ip, uint16_t port);
    ~MainService();
    void runServer();
    void runBackgroundRouter();
    std::string handleRequest(data::Request request);
    std::string getRouterResponse();

private:

    grpc::Status StreamData(grpc::ServerContext* context, grpc::ServerReaderWriter<data::Response, data::Request>* stream) override;
    grpc::Status Authenticate(grpc::ServerContext* context, const data::AuthRequest* request, data::AuthResponse* response) override;

    std::string ip_;
    uint16_t port_;
    bool auth = 0;
    bool is_running_ = 1;
    Parser parser_;
    Router router_;
    std::string router_response_;
    std::thread router_thread_;
    std::mutex data_mutex_;
    std::mutex request_mutex_;
    std::vector<data::Device> devices_;

};

#endif // _SERVER_H_