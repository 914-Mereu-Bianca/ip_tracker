#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>

class Device {
public:

    Device(int id, std::string name, std::string ip_address, std::string mac_address, bool is_blocked, bool is_online);

private:

    int id_;
    std::string name_;
    std::string ip_address_;
    std::string mac_address_;
    bool is_blocked_;
    bool is_online_;

};

#endif // _DEVICE_H_