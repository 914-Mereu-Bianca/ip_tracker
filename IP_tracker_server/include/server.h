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
    void runBackgroundGetDevices();
    void runBackgroundGetBlockedDevices();
    std::string handleRequest(data::Request request);
    std::string getAllDevicesResponse();
    std::string getAllBlockedDevicesResponse();

private:

    grpc::Status StreamData(grpc::ServerContext* context, grpc::ServerReaderWriter<data::Response, data::Request>* stream) override;
    grpc::Status Authenticate(grpc::ServerContext* context, const data::AuthRequest* request, data::AuthResponse* response) override;

    std::string ip_;
    uint16_t port_;
    bool auth = 0;
    bool is_running_ = 1;
    Parser parser_;
    Router router_;
    std::string router_response_get_all_;
    std::string router_response_get_all_blocked_;
    std::thread get_devices_thread_;
    std::thread get_blocked_devices_thread_;
    std::mutex get_devices_mutex_;
    std::mutex get_blocked_devices_mutex_;
    std::mutex request_mutex_;
    std::vector<data::Device> devices_;

};

#endif // _SERVER_H_