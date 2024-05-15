#include "include/data_parser.h"
#include "include/server.h"
#include "include/router.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <thread>

void background() {
    
}

int main() {

    MainService server("0.0.0.0", 50051);
    server.RunServer();
    
    /*while(1){
        Router r("55%2Bcg.i!%5EtxqFrc*C.6c.55H.*l90nK!");
        std::string response = r.getAllDevices();
        std::cout << "Response: " << response.substr(response.find("online 0"), 100) << std::endl;
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(5));
    }*/
    
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