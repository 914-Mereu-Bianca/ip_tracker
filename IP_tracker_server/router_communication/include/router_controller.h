#ifndef _ROUTER_CONTROLLER_H_
#define _ROUTER_CONTROLLER_H_

#include <string>
#include <curl/curl.h>
#include <thread>
#include <mutex>
#include "router.h"
#include "../../build/proto_generated/ip_tracker.grpc.pb.h"
#include "../../build/proto_generated/ip_tracker.pb.h"

class RouterController {

public:

    RouterController();
    ~RouterController();
    void runBackgroundGetDevices();
    void runBackgroundGetBlockedDevices();
    std::string handleRequest(data::Request request);
    std::string getAllDevicesResponse();
    std::string getAllBlockedDevicesResponse();
    inline void stop() { is_running_ = false; }

private:

    Router router_;
    bool is_running_ = true;
    std::string router_response_get_all_ = "";
    std::string router_response_get_all_blocked_ = "";
    std::thread get_devices_thread_;
    std::thread get_blocked_devices_thread_;
    std::mutex get_devices_mutex_;
    std::mutex get_blocked_devices_mutex_;
    std::mutex request_mutex_;

};

#endif //_ROUTER_CONTROLLER_H_