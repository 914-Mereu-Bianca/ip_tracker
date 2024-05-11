#include "include/server_impl.h"
#include "include/auth_server_impl.h"
#include "include/data_parser.h"
#include "include/device.h"

#include <fstream>
#include <sstream>

int main() {
    std::string ip = "0.0.0.0";
    int32_t port = 50051;
    Parser parser;
    //ServiceImpl server(ip, port);
    
    /*AuthServiceImpl server(ip, port);
    server.RunServer();*/
    
    std::ifstream file("../data/data.txt");
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    file.close();

    parser.parseData2(content);
    
    auto dev = parser.getDevices();

    for(auto &d: dev) 
        std::cout<< d.id() << " " <<d.ip_address() << " " << d.mac_address() << " " << d.is_online() << " " << d.is_blocked() << std::endl;

    return 0;
}