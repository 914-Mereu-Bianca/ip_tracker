#include "../include/server_controller.h"


ServerController::ServerController() {
    update_devices_ = std::thread(&ServerController::updateDevices, this);
}

ServerController::~ServerController() {
    is_running_ = false;
    if(update_devices_.joinable()) {
        update_devices_.join();
    }
    router_controller_.stop();
}

void ServerController::changeMail(const std::string &new_email) {
    mail_.setEmail(new_email);
}

void ServerController::sendHandleRequest(data::Request request) {
    router_controller_.handleRequest(request);
}

std::vector<data::Device> ServerController::getDevices() {
    std::unique_lock lock(devices_mutex_);
    return devices_;

}

void ServerController::setDevices(std::vector<data::Device> devices) { 
    std::unique_lock lock(devices_mutex_);
    devices_ = devices;
}

void ServerController::updateDevices() {
    // The parser gets the data from the handler 
    // to get the devices together with information about each of them
    std::string response;
    while (is_running_) {
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(4));
        response = router_controller_.getAllDevicesResponse();
        if(response != "")
            parser_.parseData(response);
        response = router_controller_.getAllBlockedDevicesResponse();
        if(response != "") {
            parser_.parseBlockedDevices(response);
        }

        old_devices_ = getDevices();
        setDevices(parser_.getDevices());
        checkNewDevices();
    }
}

void ServerController::checkNewDevices() {

    current_devices_ = getDevices();

    if(old_devices_.size() && old_devices_.size() != current_devices_.size()) {
        for (const auto& newDevice : current_devices_) {
            // Check if newDevice's MAC address is not in old_devices_
            if (std::find_if(old_devices_.begin(), old_devices_.end(), 
                            [&newDevice](const auto& oldDevice) {
                                return oldDevice.mac_address() == newDevice.mac_address();
                            }) == old_devices_.end()) {
                new_devices_.push_back(newDevice);
                std::cout<<newDevice.mac_address()<<std::endl;
            }
        }
        for (const auto& device : new_devices_) {
            data::Request request;
            request.set_request("Block");
            request.set_mac(device.mac_address());
            router_controller_.handleRequest(request);
            mail_.send();
        }
        new_devices_.clear();
    }

}
