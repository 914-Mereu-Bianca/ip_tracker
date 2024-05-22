#ifndef _CLIENT_VIEW_H_
#define _CLIENT_VIEW_H_

#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "client.h"
#include "view/main_window.h"
#include "view/main_widget.h"
#include <memory>
#include <thread>

class ClientView : public QObject {
    Q_OBJECT
//This class controls the way the data from the client is displayed
public:
    ClientView( QWidget *parent = nullptr);
    ClientView(ClientView &other) = delete;
    ClientView& operator=(ClientView &other) = delete;
    ClientView(ClientView &&other) = default;
    ClientView& operator=(ClientView &&other) = default;
    // This function allows the client to authenticate to the server
    void startApplication();
    void runClient();
    data::Response filterDevices(data::Response devices);
    ~ClientView();

signals:
    void populateTable(data::Response data);
    void setupMainPage();
    void displayErrorMessage();
    void displayMessageDialog(const std::string &message);

public slots:
    void authenticate(const std::string &username, const std::string &password);
    void saveCredentials(const std::string &username, const std::string &password, const std::string &current_password);
    void setRequest(const std::string &request, const std::string &name, const std::string &mac);
    void setFilter(int filter_number);

private:
    MainWindow* main_window_;
    std::shared_ptr<MainClient> client_;
    MainWidget* main_widget_;
    // thread on which the authentication process runs
    std::thread main_thread_;
    std::mutex auth_mutex_;
    bool authenticated = 0;
    int filter_number_ = 0;
};

#endif