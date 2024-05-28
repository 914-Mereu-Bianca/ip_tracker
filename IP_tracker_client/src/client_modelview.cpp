#include "client_modelview.h"

ClientModelView::ClientModelView(QWidget *parent) : QObject(parent)
{
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    client_ = std::make_shared<MainClient>(channel);
    main_window_ = new MainWindow(900, 600, client_);
    main_widget_ = new MainWidget(main_window_);
    
    connect(this, &ClientModelView::populateTable, main_widget_, &MainWidget::populate);
    connect(this, &ClientModelView::setupMainPage, main_widget_, &MainWidget::setupMainPage);
    connect(this, &ClientModelView::displayErrorMessageLogin, main_widget_, &MainWidget::displayErrorMessageLogin);
    connect(this, &ClientModelView::displayMessageDialogCredentials, main_widget_, &MainWidget::displayMessageDialogCredentials);
    connect(this, &ClientModelView::displayMessageDialogEmail, main_widget_, &MainWidget::displayMessageDialogEmail);
    connect(main_widget_, &MainWidget::authenticate, this, &ClientModelView::authenticate);
    connect(main_widget_, &MainWidget::setRequest, this, &ClientModelView::setRequest);
    connect(main_widget_, &MainWidget::setFilter, this, &ClientModelView::setFilter);
    connect(main_widget_, &MainWidget::saveCredentials, this, &ClientModelView::saveCredentials);
    connect(main_widget_, &MainWidget::saveEmail, this, &ClientModelView::saveEmail);

    main_window_->show();
}


void ClientModelView::authenticate(const std::string &username, const std::string &password)
{   
    authenticated = client_->Authenticate(username, password);
    if (authenticated) {
        emit setupMainPage();
        auth_mutex_.unlock();
    }else {
        emit displayErrorMessageLogin();
    }
    
}

void ClientModelView::saveCredentials(const std::string &username, const std::string &password, const std::string &current_password) {
    std::cout<<username<<" "<<password<<" " <<current_password<<std::endl;
    auto response = client_->ChangeCredentials(username, password, current_password);
    emit displayMessageDialogCredentials(response.message());
}

void ClientModelView::saveEmail(const std::string &email, const std::string &current_password) {
    std::cout<<email<<" " <<current_password<<std::endl;
    auto response = client_->ChangeEmail(email, current_password);
    emit displayMessageDialogEmail(response.message());
}

void ClientModelView::setRequest(const std::string &request, const std::string &name, const std::string &mac) {
    client_->setRequest(request, name, mac);
}

void ClientModelView::setFilter(int filter_number) {
    filter_number_ = filter_number;
}

data::Response ClientModelView::filterDevices(data::Response devices) {
    if(devices.devices().size() == 0 || filter_number_ == 0) return devices;

    data::Response filteredDevices;
    // copy the first device which contains the router's info and filter the rest
    filteredDevices.add_devices()->CopyFrom(devices.devices()[0]);
    
    if (filter_number_ == 1) {
        for (auto it = devices.devices().begin() + 1; it != devices.devices().end(); ++it) {
            if ((*it).is_online()) {
                filteredDevices.add_devices()->CopyFrom(*it);
            }
        }
    }
    else if (filter_number_ == 2 ) {
        for (auto it = devices.devices().begin() + 1; it != devices.devices().end(); ++it) {
            if ((*it).is_blocked()) {
                filteredDevices.add_devices()->CopyFrom(*it);
            }
        }
    }
    return filteredDevices;
}

void ClientModelView::startApplication() {

    auth_mutex_.lock();
    client_->runClient();

    while(client_->isRunning()) {
        data::Response devices = client_->getDevices();
        emit populateTable(filterDevices(devices));
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    }

}

void ClientModelView::runClient() 
{
    auth_mutex_.lock();
    main_thread_ = std::thread(&ClientModelView::startApplication, this);
}

ClientModelView::~ClientModelView()
{
    if(main_thread_.joinable())
        main_thread_.join();
}
