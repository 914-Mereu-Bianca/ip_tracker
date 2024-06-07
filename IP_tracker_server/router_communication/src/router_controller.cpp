#include "../include/router_controller.h"

#include <curl/curl.h>
#include <thread>
#include <mutex>


RouterController::RouterController()
{
    router_.setToken("4sk*%2B4o14qoInoz%2CYB%3CmDsysyrHAVQN%2B"); 
    get_devices_thread_ = std::thread(&RouterController::runBackgroundGetDevices, this);
    get_blocked_devices_thread_ = std::thread(&RouterController::runBackgroundGetBlockedDevices, this);
}

RouterController::~RouterController()
{
    if (get_devices_thread_.joinable()) {
        get_devices_thread_.join();
    }
    if (get_blocked_devices_thread_.joinable()) {
        get_blocked_devices_thread_.join();
    }
}

std::string RouterController::handleRequest(data::Request request) {
    if(request.request()!="")
        std::cout<<request.request()<<std::endl<<request.name()<<std::endl<<request.mac()<<std::endl;
    
    std::string response = "";

    if(request.request() == "Block") {
        std::unique_lock u_lock(request_mutex_);
        std::string name = request.name();
        std::string mac = request.mac();
        response = router_.blockDevice(name, mac);
        std::cout<<response<<std::endl;
    } else if (request.request() == "Unblock") {
        std::unique_lock u_lock(request_mutex_);
        std::string mac = request.mac();
        response = router_.unblockDevice(mac);
        std::cout<<response<<std::endl;
    }

    return response;
        
}


void RouterController::runBackgroundGetDevices() {
    std::string response = "";
    while(is_running_) {

        std::unique_lock u_lock(request_mutex_);
        response = router_.getAllDevices();
        u_lock.unlock();
        
        if(response != "failed") {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(3));
            std::lock_guard lock(get_devices_mutex_);
            router_response_get_all_ = response;
        }   
    }
}

std::string RouterController::getAllDevicesResponse() {
    std::lock_guard lock(get_devices_mutex_);
    return router_response_get_all_;
}

void RouterController::runBackgroundGetBlockedDevices() {
    std::string response = "";
    while(is_running_) {

        std::unique_lock u_lock(request_mutex_);
        response = router_.getAllBlockedDevices();
        u_lock.unlock();

        if(response != "failed") {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(3));
            std::lock_guard lock(get_blocked_devices_mutex_);
            router_response_get_all_blocked_ = response;
        }   
    }
}

std::string RouterController::getAllBlockedDevicesResponse() {
    std::lock_guard lock(get_blocked_devices_mutex_);
    return router_response_get_all_blocked_;
}