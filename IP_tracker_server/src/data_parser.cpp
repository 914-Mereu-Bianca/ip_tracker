
#include "../include/data_parser.h"

void Parser::parseData(const std::string &input_file) {

    std::vector<data::Device> devices;

    std::ifstream file(input_file);

    std::string line;
    
    std::getline(file, line);  // jump over response
    std::getline(file, line);  // jump over the id of the id of the request

    int n = 95, nr_devices = 0;
    
    data::Device d;
    data::Response resp;

    while (std::getline(file, line) && n) {
        if(line[6] != '0' && line[6] != '.') {
            if (nr_devices < 10) {
                d.set_ip_address(line.substr(5));   // case 'ip x <ip_address>' => ip_address starts from 5
            }
            else {
                d.set_ip_address(line.substr(6));   // case 'ip xx <ip_address>' => ip_address starts from 6
            }
            devices.push_back(d);
            nr_devices++;
        }
        n--;
    }
    
    n = 0;

    while (std::getline(file, line) && n < nr_devices) {
        if(line.substr(6) != "00-00-00-00-00-00" && line.substr(7) != "00-00-00-00-00-00") {
            if (n < 10) {
                devices[n].set_mac_address(line.substr(6));   // case 'mac x <mac_address>' => mac_address starts from 6
            }
            else {
                devices[n].set_mac_address(line.substr(7));   // case 'mac xx <mac_address>' => mac_address starts from 7
            }
        }
        n++;
    }

    jumpOver(file, 96 - nr_devices - 1); //jump over the rest of the mac addresses
    jumpOver(file, 96); // jump over reserved information
    jumpOver(file, 96); // jump over bindEntry information
    jumpOver(file, 96); // jump over staMgtEntry information

    std::getline(file, line);
    std::cout<<line<<std::endl;
    std::cout<<nr_devices<<std::endl;

    for(auto &d: devices) {
        std::cout<<d.ip_address()<<" "<<d.mac_address()<<std::endl;
    }

    file.close();    

    

}

void Parser::jumpOver(std::ifstream &file, int lines_to_be_skipped) {

    std::string line;

    while(lines_to_be_skipped && std::getline(file, line)) {
        lines_to_be_skipped--;
    }

}

void Parser::parseData2(const std::string &string) {
    
    parseIP(string);
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

void Parser::parseMAC(const std::string &string) {
    
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