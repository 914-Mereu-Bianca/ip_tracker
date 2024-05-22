#ifndef _DEVICES_HANDLER_H_
#define _DEVICES_HANDLER_H_

#include <string>
#include <thread>
#include <mutex>
#include "router.h"
#include "../../build/proto_generated/ip_tracker.grpc.pb.h"
#include "../../build/proto_generated/ip_tracker.pb.h"

class DevicesHandler {
// This class is responsible to define the logic between the router devices and the database devices
public:

    DevicesHandler();
    ~DevicesHandler();

private:

    std::thread update_devices_;
    std::mutex devices_mutex_;
    std::vector<data::Device> devices_;
    std::vector<data::Device> old_devices_;
    std::vector<data::Device> new_devices_;

};

#endif //_DEVICES_HANDLER_H_