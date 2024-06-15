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
#include "../../database/include/sql_connector.h"

class ServerController {
// This class is responsible to define the logic between the router devices and the database devices
public:

    ServerController();
    ~ServerController();
    void checkNewDevices(std::vector<data::Device> parsed_devices);
    void manageNewDevice(data::Device &device);
    void updateDevices();
    void sendHandleRequest(const data::Request &request);
    std::vector<data::Device> getDevices();
    void setDevices(std::vector<data::Device> devices);
    void changeMail(const std::string &new_email);
    void deleteDevice(const std::string &mac);
    void renameDevice(const data::Request &request);

private:

    void eliminateNonPrintChar(data::Device &device);

    SendMail mail_;
    Parser parser_;
    RouterController router_controller_;
    SqlConnector SQL_connector_;
    std::thread update_devices_;
    std::mutex devices_mutex_;
    std::mutex db_devices_mutex_;

    // devices that are constantly changing due to the requests to the server
    std::vector<data::Device> devices_; 

    std::vector<data::Device> parsed_devices_;  

    bool is_running_ = true;

};

#endif //_SERVER_CONTROLLER_H_