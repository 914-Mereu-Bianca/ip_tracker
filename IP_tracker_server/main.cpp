#include "include/server_impl.h"
#include "include/auth_server_impl.h"
#include "include/data_parser.h"
#include "include/device.h"

#include <fstream>

int main() {
    std::string ip = "0.0.0.0";
    int32_t port = 50051;

    //ServiceImpl server(ip, port);
    
    /*AuthServiceImpl server(ip, port);
    server.RunServer();*/
    
    std::ifstream file("../data/data.txt");
    
    std::vector<data::Device> devices;

    std::string line;
    
    std::getline(file, line);
    std::getline(file, line);

    int n = 96, nr_devices = 0;
    
    data::Device d;
    data::Response resp;

    while (std::getline(file, line) && n) {
        std::cout << line << std::endl;
        if(line[6] != '0' && line[6] != '.') {
            if (nr_devices < 10) {
                std::cout<<line.substr(5)<<std::endl;
                d.set_ip_address(line.substr(5));
                std::cout<<d.ip_address()<<std::endl;
                //devices[nr_devices].set_ip_address(); 
            }
            //resp.add_device()->CopyFrom(d);
            nr_devices++;
        }
        n--;
    }

    std::cout<<nr_devices<<std::endl;// << devices[0].ip_address() << " " << devices[1].ip_address() << devices[2].ip_address() << std::endl;
    


    file.close();
    
    return 0;
}