#ifndef _CLIENT_VIEW_H_
#define _CLIENT_VIEW_H_

#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "client.h"
#include "view/main_window.h"
#include "view/main_widget.h"
#include "view/credentials_dialog.h"
#include <memory>
#include <thread>

class ClientModelView : public QObject {
    Q_OBJECT
public:
    ClientModelView(QWidget *parent = nullptr);
    ClientModelView(ClientModelView &other) = delete;
    ClientModelView& operator=(ClientModelView &other) = delete;
    ClientModelView(ClientModelView &&other) = default;
    ClientModelView& operator=(ClientModelView &&other) = default;
    // This function allows the client to authenticate to the server
    void startApplication();
    void runClient();
    data::Response filterDevices(data::Response devices);
    ~ClientModelView();

signals:
    void populateTable(data::Response data);
    void setupMainPage();
    void displayErrorMessageLogin();
    void displayMessageDialogCredentials(const std::string &message);
    void displayMessageDialogEmail(const std::string &message);
    void displayMainMessage(const std::string &message);

public slots:
    void authenticate(const std::string &username, const std::string &password);
    void resetCredentials();
    void saveCredentials(const std::string &username, const std::string &password, const std::string &current_password);
    void saveEmail(const std::string &email, const std::string &current_password);
    void manageDevice(const std::string &request, const std::string &name, const std::string &mac);
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