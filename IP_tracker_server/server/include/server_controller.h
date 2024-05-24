#ifndef _SERVER_CONTROLLER_H_
#define _SERVER_CONTROLLER_H_

#include <string>
#include <thread>
#include <mutex>

#include "../../build/proto_generated/ip_tracker.grpc.pb.h"
#include "../../build/proto_generated/ip_tracker.pb.h"
#include "../../router_communication/include/router_controller.h"
#include "../../router_communication/include/router.h"
#include "../../mail_communication/include/send_mail.h"
#include "../../parser/include/data_parser.h"

class ServerController {
// This class is responsible to define the logic between the router devices and the database devices
public:

    ServerController();
    ~ServerController();
    void checkNewDevices();
    void updateDevices();
    void sendHandleRequest(data::Request request);
    std::vector<data::Device> getDevices();
    void setDevices(std::vector<data::Device> devices);
    void changeMail(const std::string &new_email);

private:

    SendMail mail_;
    Parser parser_;
    RouterController router_controller_;
    std::thread update_devices_;
    std::mutex devices_mutex_;

    // devices that are constantly changing due to the requests to the server
    std::vector<data::Device> devices_; 

    // the devices saved before the devices_ changed 
    std::vector<data::Device> old_devices_; 

    // the devices that appear in devices_ but not in old_devices_
    std::vector<data::Device> new_devices_;

    // value from devices_ saved for the checkNewDevices function so the devices_ can be used and 
    // the mutex will not be blocked for the getDevices in server
    std::vector<data::Device> current_devices_;  

    bool is_running_ = true;

};

#endif //_SERVER_CONTROLLER_H_