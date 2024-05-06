#include "include/server_impl.h"
#include "include/auth_server_impl.h"


int main() {
    std::string ip = "0.0.0.0";
    int32_t port = 50051;

    //ServiceImpl server(ip, port);
    AuthServiceImpl server(ip, port);
    server.RunServer();
    
    return 0;
}