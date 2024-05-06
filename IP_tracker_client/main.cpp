#include <QApplication>
#include "include/client_impl.h"
#include "include/main_window.h"
#include "include/auth_client_impl.h"
#include <grpc++/grpc++.h>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {

    //ClientImpl client{grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())};

    //client.StreamData();
    
    /*QApplication app(argc, argv); 

    MainWindow* main_window_ = new MainWindow(1400, 600);

    main_window_->show();

    return app.exec();*/


    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    AuthClientImpl client(channel);

    // Example authentication
    client.Authenticate("usr", "password");


    return 0;
}