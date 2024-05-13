#include "include/data_parser.h"
#include "include/server.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <thread>

int main() {

    /*std::thread auth_thread_ = std::thread(&authServer, this);
    std::thread main_thread_ = std::thread(&mainServer, this);*/

    MainService server("0.0.0.0", 50051);
    server.RunServer();
    
    /*std::ifstream file("../data/data.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    file.close();
    Parser parser;
    parser.parseData(content);
    
    auto dev = parser.getDevices();

    for(auto &d: dev) 
        std::cout<< d.id() << " " <<d.name() << " " <<d.ip_address() << " " << d.mac_address() << " " << d.is_online() << " " << d.is_blocked() << std::endl;*/

    return 0;
}