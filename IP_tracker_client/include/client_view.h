#ifndef _CLIENT_VIEW_H_
#define _CLIENT_VIEW_H_

#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include "auth_client_impl.h"
#include "main_window.h"
#include "view/auth_widget.h"
#include <memory>
#include <thread>

class ClientView {
//This class controls the way the data from the client is displayed
public:
    ClientView();
    ClientView(ClientView &other) = delete;
    ClientView& operator=(ClientView &other) = delete;
    ClientView(ClientView &&other) = default;
    ClientView& operator=(ClientView &&other) = default;
    // This function allows the client to authenticate to the server
    void authenticate();
    void runClient();
    ~ClientView();
private:
    MainWindow* main_window_;
    std::shared_ptr<AuthClientImpl> auth_client_;
    std::unique_ptr<AuthWidget> auth_widget_;
    std::thread auth_thread_;
    bool authenticated = 0;
};

#endif