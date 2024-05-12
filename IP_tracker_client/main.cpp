#include <QApplication>
#include "include/client_view.h"
#include "include/client.h"
#include "include/client_impl.h"
#include <grpc++/grpc++.h>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {

    //ClientImpl client{grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())};

    //client.StreamData();
    
    QApplication app(argc, argv); 

    ClientView client_;

    client_.runClient();

    return app.exec();


    /*std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    AuthClientImpl client(channel);

    // Example authentication
    client.Authenticate("usr", "password");*/

    /*std::shared_ptr<grpc::Channel> channel_client = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    ClientImpl client(channel_client);

    client.StreamData();*/

    return 0;
}