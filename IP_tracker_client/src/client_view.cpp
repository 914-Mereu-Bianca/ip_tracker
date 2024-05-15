#include "client_view.h"

ClientView::ClientView(QWidget *parent) : QObject(parent)
{
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    client_ = std::make_shared<MainClient>(channel);
    main_window_ = new MainWindow(900, 600, client_);
    main_widget_ = new MainWidget(main_window_);
    main_widget_->SetupWidgets();
    
    connect(this, &ClientView::populateTable, main_widget_, &MainWidget::populate);
    connect(this, &ClientView::createTableAndClear, main_widget_, &MainWidget::createTable);
    connect(main_widget_, &MainWidget::authenticate, this, &ClientView::authenticate);
    connect(this, &ClientView::displayErrorMessage, main_widget_, &MainWidget::displayErrorMessage);

    main_window_->show();
}


void ClientView::authenticate(const std::string &username, const std::string &password)
{   
    authenticated = client_->Authenticate(username, password);
    if (authenticated) {
        emit createTableAndClear();
        auth_mutex_.unlock();
    }else {
        emit displayErrorMessage();
    }
    
}

void ClientView::startApplication() {

    auth_mutex_.lock();
    
    client_->runClient();

    while(client_->isRunning()) {

        data::Response devices = client_->getDevices();
        emit populateTable(devices);
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        
    }

}

void ClientView::runClient() 
{
    auth_mutex_.lock();
    main_thread_ = std::thread(&ClientView::startApplication, this);
}

ClientView::~ClientView()
{
    if(main_thread_.joinable())
        main_thread_.join();
}
