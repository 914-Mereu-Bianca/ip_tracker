#include "../include/server_controller.h"


ServerController::ServerController() {
    setDevices(SQL_connector_.getDevices());
    update_devices_ = std::thread(&ServerController::updateDevices, this);
}

ServerController::~ServerController() {
    is_running_ = false;
    if(update_devices_.joinable()) {
        update_devices_.join();
    }
    router_controller_.stop();

    for(auto &d: devices_) {
        if(SQL_connector_.checkIfMacExists(d.mac_address()))
            SQL_connector_.updateDevice(d);
        else 
            SQL_connector_.addDevice(d);
    }
}

void ServerController::changeMail(const std::string &new_email) {
    mail_.setEmail(new_email);
}

void ServerController::sendHandleRequest(const data::Request &request) {
    router_controller_.handleRequest(request);

    data::Device device;
    device.set_name(request.name());
    device.set_mac_address(request.mac());
    if(request.request() == "Block") {
        device.set_is_blocked(1);
        SQL_connector_.updateDevice(device);
    }
    else if(request.request() == "Unblock") {
        device.set_is_blocked(0);
        SQL_connector_.updateDevice(device);
    }
}

std::vector<data::Device> ServerController::getDevices() {
    std::lock_guard lock(devices_mutex_);
    return devices_;
}

void ServerController::setDevices(std::vector<data::Device> devices) { 
    std::lock_guard lock(devices_mutex_);
    devices_ = devices;
}

void ServerController::updateDevices() {
    // The parser gets the data from the handler 
    // to get the devices together with information about each of them
    std::string response;
    while (is_running_) {
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(4));
        response = router_controller_.getAllDevicesResponse();
        if(response != "" && response.size() > 200)
            parser_.parseData(response);
        response = router_controller_.getAllBlockedDevicesResponse();
        if(response != "" && response.size() > 200) {
            parser_.parseBlockedDevices(response);
        }

        parsed_devices_ = parser_.getDevices();
        checkNewDevices(parser_.getDevices());
    }
}

void ServerController::checkNewDevices(std::vector<data::Device> parsed_devices) {

    // if in the database has no device initially, all the devices connected are added
    if(SQL_connector_.getDevices().size() == 0) {
        std::lock_guard lock(devices_mutex_);
        for(auto& newDevice : parsed_devices) {
            devices_.push_back(newDevice);
            eliminateNonPrintChar(newDevice);
            SQL_connector_.addDevice(newDevice);
        }
    }
    else {
        std::lock_guard lock(devices_mutex_);
        // Suppose each device has been forgotten by the router
        for(auto &d: devices_) d.set_is_remembered(0);
        // Iterate through all the devices and check if there are new ones
        for (auto& device : parsed_devices) {
            bool found = 0;
            for(auto &d: devices_) {
                if(d.mac_address() == device.mac_address()) { 
                    eliminateNonPrintChar(device);
                    device.set_is_remembered(1);
                    SQL_connector_.updateDevice(device);
                    d = device;
                    found = 1;
                    break;
                }
            }
            if(!found) manageNewDevice(device);
            
        }
        // Sync devices_ with database for the devices that are not remembered
        for(auto it = devices_.begin(); it != devices_.end(); ++it) {
            if(!(*it).is_remembered()) {
                if(SQL_connector_.checkIsRemembered((*it).mac_address())) 
                    SQL_connector_.setRemembered(0, (*it).mac_address());
                if(SQL_connector_.checkIfMacExists((*it).mac_address())) {
                    (*it).set_is_blocked(SQL_connector_.checkIsBlocked((*it).mac_address()));
                    (*it).set_name(SQL_connector_.getName((*it).mac_address()));
                }
            }
            else {
                if(!SQL_connector_.checkIsRemembered((*it).mac_address())) 
                    SQL_connector_.setRemembered(1, (*it).mac_address());
            }
        }
    }
}

void ServerController::manageNewDevice(data::Device &device) {
    // Here enters only the new devices (not present in database)
    device.set_is_blocked(1);
    eliminateNonPrintChar(device);
    SQL_connector_.addDevice(device);
    devices_.push_back(device);
    data::Request request;
    request.set_request("Block");
    request.set_mac(device.mac_address());
    router_controller_.handleRequest(request);
    mail_.send();
    
}


void ServerController::deleteDevice(const std::string &mac) {
    std::lock_guard lock(devices_mutex_);
    SQL_connector_.removeDevice(mac);
    for(auto it = devices_.begin(); it != devices_.end(); ++it) {
        if((*it).mac_address() == mac) {
            devices_.erase(it);
        }
    }
}

void ServerController::renameDevice(const data::Request &request) {
    if(SQL_connector_.checkIsRemembered(request.mac())) {
        sendHandleRequest(request);
    } else {
        SQL_connector_.renameDevice(request.name(), request.mac());
    }
}

void ServerController::eliminateNonPrintChar(data::Device &device) {
    std::string name = device.name();
    std::string ip = device.ip_address();
    std::string mac = device.mac_address();
    name.erase(std::remove_if(name.begin(), name.end(), [](unsigned char c){ return !std::isprint(c);}), name.end());
    ip.erase(std::remove_if(ip.begin(), ip.end(), [](unsigned char c){return !std::isprint(c);}), ip.end());    
    mac.erase(std::remove_if(mac.begin(), mac.end(), [](unsigned char c){return !std::isprint(c);}), mac.end());    
    device.set_name(name);
    device.set_ip_address(ip);
    device.set_mac_address(mac);
}
