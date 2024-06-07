#ifndef _MAIN_WIDGET_H_
#define _MAIN_WIDGET_H_

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QLayoutItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDialog>
#include <../build/proto_generated/ip_tracker.grpc.pb.h>
#include <../build/proto_generated/ip_tracker.pb.h>
#include "credentials_dialog.h"
#include "email_dialog.h"
#include "validation_dialog.h"
#include "change_name_dialog.h"

class MainWidget: public QWidget {
public:
    MainWidget(QMainWindow* parent=nullptr);
    ~MainWidget()=default;
    void LoadStylesheet();
    void SetupLoginPage();
    void SetupButtonsMainPage();

signals:
    void authenticate(const std::string &username, const std::string &password);
    void saveCredentials(const std::string &username, const std::string &password, const std::string &current_password);
    void saveEmail(const std::string &email, const std::string &current_password);
    void manageDevice(const std::string &request, const std::string &name, const std::string &mac);
    void setRequest(const std::string &request, const std::string &name, const std::string &mac);
    void setFilter(int filter_number);
    void displayMessageDialogCredentials(const std::string &message);
    void displayMessageDialogEmail(const std::string &message);

public slots:
    void HandleLogin();
    void onCellClicked(int row, int column);
    void populate(data::Response devices);
    void setupMainPage();
    void displayErrorMessageLogin(); 
    void performRequest(const std::string &request, const std::string &name, const std::string &mac);
    
    
private:
    Q_OBJECT
    QVBoxLayout *layout_;
    QWidget* central_widget_;

    QLabel *image_label_;
    QLineEdit *username_input_;
    QLineEdit *password_input_;
    QPushButton *button_;
    QLabel *error_label_;
    QPushButton *reset_credentials_button_;
    
    QPushButton *admin_button_;
    CredentialsDialog *credentialsDialog_;
    
    QPushButton *change_email_button_;
    EmailDialog *emailDialog_;

    ValidationDialog *validationDialog_;
    ChangeNameDialog *changeNameDialog_;

    QLabel *router_ip_;
    QLabel *router_mac_;

    QPushButton *button_filter_online_;
    QPushButton *button_filter_blocked_;
    QPushButton *button_filter_all_;
    QHBoxLayout *button_layout_;
    QTableWidget *table_;

    QLatin1String *styleSheet_;

    bool auth = 0;
};
#endif  // _MAIN_WIDGET_H_  