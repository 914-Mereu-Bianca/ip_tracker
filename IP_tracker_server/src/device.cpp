#include "device.h"

Device::Device(int id, std::string name, std::string ip_address, std::string mac_address, bool is_blocked, bool is_online)
 : id_(id), name_(name), ip_address_(ip_address), mac_address_(mac_address), is_blocked_(is_blocked), is_online_(is_online) {}