#include "../include/data_parser.h"

void Parser::parseData(const std::string &string) {

    devices_.clear();
    parseIP(string);
    parseName(string);
    parseMAC(string);
    parseOnline(string);
    parseBlocked(string);

}

void Parser::parseIP(const std::string &string) {

    int pos = string.find("ip 0");
    std::string line = string.substr(pos);
    line = line.substr(0, line.find('\n') + 1);

    int n = 0;
    data::Device d;

    while(line.substr(5, 7) != "0.0.0.0" && line.substr(6, 7) != "0.0.0.0" && n < 96) {
        // save ip address in new device
        if(n < 10){
            d.set_ip_address(line.substr(5, line.size() - 6));
        }
        else {
            d.set_ip_address(line.substr(6, line.size() - 7));
        }
        d.set_id(n);
        devices_.push_back(d);

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


void Parser::parseMAC(const std::string &string)
{

    int pos = string.find("mac 0");
    std::string line = string.substr(pos);
    line = line.substr(0, line.find('\n') + 1);

    int n = 0;

    while(line.substr(6, 17) != "00-00-00-00-00-00" && line.substr(7, 17) != "00-00-00-00-00-00" && n < 96) {
        // save mac address in certain device
        if(n < 10){
            devices_[n].set_mac_address(line.substr(6, 17));
        }
        else {
            devices_[n].set_mac_address(line.substr(7, 17));
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

void Parser::parseBlocked(const std::string &string) {
    
    int pos = string.find("blocked 0");
    std::string line = string.substr(pos);
    line = line.substr(0, line.find('\n') + 1);

    int n = 0;

    for(auto &d: devices_) {
        // save mac address in certain device
        if(n < 10){
            d.set_is_blocked(line[10] != '0');
        }
        else {
            d.set_is_blocked(line[11] != '0');
        }

        // go to the next mac address
        pos += line.find('\n') + 1;
        line = string.substr(pos);
        line = line.substr(0, line.find('\n') + 1);
        n++;
    }
}