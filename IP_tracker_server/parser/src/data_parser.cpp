#include "../include/data_parser.h"

void Parser::parseData(const std::string &string) {

    devices_.clear();
    parseMAC(string);
    parseIP(string);
    parseName(string);
    parseOnline(string);

    if(devices_.size() > 0 && devices_[0].ip_address().substr(devices_[0].ip_address().size() - 3, 2) != ".1") {
        for(int i = 1; i < devices_.size(); i++) {
            if(devices_[i].ip_address().substr(devices_[i].ip_address().size() - 3, 2) == ".1") {
                std::swap(devices_[0], devices_[i]);
                devices_[0].set_id(1);
                devices_[i].set_id(i+1);
                break;
            }
        }
    }

}


void Parser::parseMAC(const std::string &string) {

    int pos = string.find("mac 0");
    std::string line = string.substr(pos);
    line = line.substr(0, line.find('\n') + 1);

    int n = 0;
    data::Device d;

    while(line.substr(6, 17) != "00-00-00-00-00-00" && line.substr(7, 17) != "00-00-00-00-00-00" && n < 96) {
        // save mac address in certain device
        if(n < 10){
            d.set_mac_address(line.substr(6, 17));
        }
        else {
            d.set_mac_address(line.substr(7, 17));
        }
        d.set_id(n + 1);
        d.set_is_remembered(1);

        devices_.push_back(d);

        // go to the next mac address
        pos += line.find('\n') + 1;
        line = string.substr(pos);
        line = line.substr(0, line.find('\n') + 1);
        n++;
    }
}

void Parser::parseIP(const std::string &string) {

    int pos = string.find("ip 0");
    std::string line = string.substr(pos);
    line = line.substr(0, line.find('\n') + 1);

    int n = 0;

    for(auto &d: devices_) {
        // save ip address in new device
        if(n < 10){
            d.set_ip_address(line.substr(5, line.size() - 6));
        }
        else {
            d.set_ip_address(line.substr(6, line.size() - 7));
        }

        // go to the next ip address
        pos += line.find('\n') + 1;
        line = string.substr(pos);
        line = line.substr(0, line.find('\n') + 1);
        n++;
    }

}

void Parser::parseName(const std::string &string)
{
    int pos = string.find("name 0");
    std::string line = string.substr(pos);
    line = line.substr(0, line.find('\n') + 1);

    int n = 0;

    for(auto &d: devices_) {
        // save mac address in certain device
        if(n < 10){
            d.set_name(line.substr(7, line.size() - 8));
        }
        else {
            d.set_name(line.substr(8, line.size() - 9));
        }

        // go to the next mac address
        pos += line.find('\n') + 1;
        line = string.substr(pos);
        line = line.substr(0, line.find('\n') + 1);
        n++;
    }
}

void Parser::parseOnline(const std::string &string) {
    
    int pos = string.find("online 0");
    std::string line = string.substr(pos);
    line = line.substr(0, line.find('\n') + 1);

    int n = 0;

    for(auto &d: devices_) {
        // save mac address in certain device
        if(n < 10){
            d.set_is_online(line[9] != '0');
        }
        else {
            d.set_is_online(line[10] != '0');
        }

        // go to the next mac address
        pos += line.find('\n') + 1;
        line = string.substr(pos);
        line = line.substr(0, line.find('\n') + 1);
        n++;
    }
}

void Parser::parseBlockedDevices(const std::string &string) {
    parseMacBlocked(string);
}

void Parser::parseMacBlocked(const std::string &string) {
    int pos = string.find("mac 0");
    std::string line = string.substr(pos);
    line = line.substr(0, line.find('\n') + 1);

    int n = 0;
    data::Device blocked_device;
    while(line.substr(6, 17) != "00-00-00-00-00-00" && line.substr(7, 17) != "00-00-00-00-00-00" && n < 96) {
        bool found = 0;
        if(n < 10){
            for(auto &d: devices_){
                if(d.mac_address() == line.substr(6, 17)) {
                    d.set_is_blocked(1);
                    found = 1;
                }
            }
            /*if (!found) {
                blocked_device.set_id(devices_.size() + 1);
                blocked_device.set_mac_address(line.substr(6, 17));
                blocked_device.set_is_blocked(1);
                devices_.push_back(blocked_device);
            }*/
        }
        else {
            for(auto &d: devices_){
                if(d.mac_address() == line.substr(7, 17)) {
                    d.set_is_blocked(1);
                    found = 1;
                }
            }
            /*if (!found) {
                blocked_device.set_id(devices_.size() + 1);
                blocked_device.set_mac_address(line.substr(7, 17));
                blocked_device.set_is_blocked(1);
                devices_.push_back(blocked_device);
            }*/
        }
        
        
        // go to the next mac address
        pos += line.find('\n') + 1;
        line = string.substr(pos);
        line = line.substr(0, line.find('\n') + 1);
        n++;
    }
}