#include "client_view.h"

ClientView::ClientView()
{
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    auth_client_ = std::make_shared<AuthClientImpl>(channel);
    main_window_ = new MainWindow(900, 600, auth_client_);
    auth_widget_ = std::make_unique<AuthWidget>(main_window_);
    auth_widget_->SetupWidgets();
    
    main_window_->show();
}


void ClientView::authenticate()
{
    while(auth_client_->isRunning()){
        if (auth_widget_->clicked() == 1) {
            authenticated = auth_client_->Authenticate(auth_widget_->getUsername(), auth_widget_->getPassword());
            
            if (authenticated) {
                auth_widget_->clear();
                auth_client_->Stop();
                auth_mutex_.unlock();
            }else {
                auth_widget_->setClicked();
            }
            
        }
    }
}

void ClientView::startApplication() {

    auth_mutex_.lock();
    //auth_widget_->createTable();
    //ip_info_widget_ = std::make_unique<IPInfoWidget>(main_window_);
}

void ClientView::runClient() 
{
    auth_mutex_.lock();
    auth_thread_ = std::thread(&ClientView::authenticate, this);
    main_thread_ = std::thread(&ClientView::startApplication, this);
    //auth_mutex_.lock();
    //ip_info_widget_ = std::make_unique<IPInfoWidget>(main_window_);
}

ClientView::~ClientView()
{
    if(auth_thread_.joinable())
        auth_thread_.join();
}
