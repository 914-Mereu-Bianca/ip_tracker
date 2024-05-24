#include "view/main_widget.h"
#include "view/main_window.h"
#include "client_modelview.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QHeaderView>
#include <QFile>

MainWidget::MainWidget(QMainWindow *parent)
        :QWidget(parent),
        credentialsDialog_(new CredentialsDialog(this)) {

    layout_ = new QVBoxLayout;
    central_widget_ = new QWidget;
    central_widget_->setLayout(layout_); 
    parent->setCentralWidget(central_widget_);
    layout_->setAlignment(Qt::AlignCenter);

    LoadStylesheet();
    SetupLoginPage();

    connect(credentialsDialog_, &CredentialsDialog::saveCredentials, this, &MainWidget::saveCredentials);
    connect(this, &MainWidget::displayMessageDialogCredentials, credentialsDialog_, &CredentialsDialog::displayMessageDialogCredentials);
}

void MainWidget::LoadStylesheet() {
    QFile file("/home/bianca/ip_tracker/IP_tracker_client/resources/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        styleSheet_ = new QLatin1String(file.readAll());
        central_widget_->setStyleSheet(*styleSheet_);
    }
}

void MainWidget::SetupLoginPage() {

    // ------ Setup the Logo -------
    QPixmap pixmap("/home/bianca/ip_tracker/IP_tracker_client/utils/iptrackerlogo.png");
    image_label_ = new QLabel(this);
    image_label_->setFixedSize(400, 100);
    image_label_->setAlignment(Qt::AlignCenter);
    image_label_->setPixmap(pixmap);
    layout_->addWidget(image_label_);

    // ------ Setup the Username Input -------
    username_input_ = new QLineEdit(this);
    username_input_->setPlaceholderText("Username");
    layout_->addWidget(username_input_, 0, Qt::AlignCenter);
    username_input_->setFixedWidth(240);

    // ------ Setup the Password Input -------
    password_input_ = new QLineEdit(this);
    password_input_->setFixedWidth(240);
    password_input_->setEchoMode(QLineEdit::Password);
    password_input_->setPlaceholderText("Password");
    layout_->addWidget(password_input_, 0, Qt::AlignCenter);

    // ------ Setup the Login button -------
    button_ = new QPushButton("Login", this);  
    button_->setFixedSize(100, 35);
    layout_->addWidget(button_, 0, Qt::AlignCenter);
    connect(button_, &QPushButton::clicked, this, &MainWidget::HandleLogin);

    // ------ Setup the Error Message -------
    error_label_ = new QLabel("Authentication Failed!", this);
    error_label_->setStyleSheet("QLabel { color: rgb(182, 197, 219); }");
    layout_->addWidget(error_label_, 0, Qt::AlignCenter);
}

void MainWidget::setupMainPage() {
    // ----- Set the visibility to false for the widgets from the login page -----
    username_input_->setVisible(0);
    password_input_->setVisible(0);
    button_->setVisible(0);
    error_label_->setVisible(0);
    image_label_->setVisible(0);
    
    SetupButtonsMainPage();
    // Design and add the admin button
    layout_->addWidget(admin_button_, 0, Qt::AlignRight);
    layout_->addWidget(change_email_button_, 0, Qt::AlignRight);

    // Add the labels for the router's information
    router_ip_ = new QLabel("Router's IP address:", this);
    router_mac_ = new QLabel("Router's MAC address:", this);  
    layout_->addWidget(router_ip_); 
    layout_->addWidget(router_mac_); 

    // Design and add the buttons 
    button_layout_->addWidget(button_filter_all_);
    button_layout_->addWidget(button_filter_online_);
    button_layout_->addWidget(button_filter_blocked_);
    layout_->addLayout(button_layout_);

    connect(admin_button_, &QPushButton::clicked, credentialsDialog_, &QDialog::exec);

    SetupEmailDialogBox();
    connect(change_email_button_, &QPushButton::clicked, [&]() {
        dialog_box_email_->exec();
    });
    connect(button_save_email_, &QPushButton::clicked, [&]() {
        emit saveEmail(new_email_->text().toStdString().c_str(), current_password_email_->text().toStdString().c_str());
    });

    // Desgin and add the table
    table_ = new QTableWidget;
    layout_->addWidget(table_); 
    table_->setColumnCount(8);
    table_->setHorizontalHeaderLabels(QStringList() << "ID" << "Device Name" << "IP Address" << "MAC Address" << "Online" << "Blocked" << "Trusted" << "Manage device");
    table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(table_, &QTableWidget::cellClicked, this, &MainWidget::onCellClicked);
}

void MainWidget::SetupEmailDialogBox() {
    dialog_box_email_ = new QDialog(this);
    dialog_box_email_->setWindowTitle("New Email");
    dialog_box_layout_email_ = new QVBoxLayout(dialog_box_email_);

    new_email_ = new QLineEdit;
    new_email_->setFixedWidth(240);
    new_email_->setPlaceholderText("New Email");
    new_email_->setStyleSheet("QLineEdit { height: 30px; background-color: white; border: 1px solid rgb(37, 39, 48); border-radius: 15px; padding-left: 10px; } QLineEdit:hover { border-color: rgb(129, 140, 140);}");
    dialog_box_layout_email_->addWidget(new_email_);

    current_password_email_ = new QLineEdit;
    current_password_email_->setFixedWidth(240);
    current_password_email_->setEchoMode(QLineEdit::Password);
    current_password_email_->setPlaceholderText("Current Password");
    current_password_email_->setStyleSheet("QLineEdit { height: 30px; background-color: white; border: 1px solid rgb(37, 39, 48); border-radius: 15px; padding-left: 10px; } QLineEdit:hover { border-color: rgb(129, 140, 140);}");
    dialog_box_layout_email_->addWidget(current_password_email_);

    button_save_email_ = new QPushButton("Save");
    button_save_email_->setFixedWidth(100);
    button_save_email_->setStyleSheet("QPushButton { height: 30px; background-color: rgb(37, 39, 48); color: rgb(255, 255, 255); border-radius: 15px; } QPushButton:hover { background-color: rgb(129, 140, 140);}");
    dialog_box_layout_email_->addWidget(button_save_email_, 0, Qt::AlignCenter);

    error_label_box_email_ = new QLabel("Error", this);
    error_label_box_email_->setStyleSheet("color: rgb(235, 235, 235);");
    dialog_box_layout_email_->addWidget(error_label_box_email_, 0, Qt::AlignCenter);
}

void MainWidget::displayMessageDialogEmail(const std::string &message) {
    error_label_box_email_->setText(QString::fromStdString(message));
    error_label_box_email_->setStyleSheet("color: red;");
    QTimer::singleShot(1500, [=]() {
        error_label_box_email_->setStyleSheet("color: rgb(235, 235, 235);");
    });
}

void MainWidget::SetupButtonsMainPage() {
    // Setup and design the buttons on the main page
    button_layout_ = new QHBoxLayout;
    button_filter_all_ = new QPushButton("All devices", this);
    button_filter_online_ = new QPushButton("Online Devices", this);  
    button_filter_blocked_ = new QPushButton("Blocked Devices", this);  
    admin_button_ = new QPushButton("Change Credentials", this);
    admin_button_->setFixedWidth(200);
    change_email_button_ = new QPushButton("Change Email", this);
    change_email_button_->setFixedWidth(200);
    connect(button_filter_all_, &QPushButton::clicked, [&]() {
        emit setFilter(0);
    });
    connect(button_filter_online_, &QPushButton::clicked, [&]() {
        emit setFilter(1);
    });
    connect(button_filter_blocked_, &QPushButton::clicked, [&]() {
        emit setFilter(2);
    });
}

void MainWidget::HandleLogin() {
    std::cout<<username_input_->text().toStdString().c_str()<<" "<<password_input_->text().toStdString().c_str()<<std::endl;
    emit authenticate(username_input_->text().toStdString().c_str(), password_input_->text().toStdString().c_str());
}

void MainWidget::onCellClicked(int row, int column) {
    std::cout<<row<<" "<<column<<" "<<table_->item(row, column)->text().toStdString().c_str()<<std::endl<<table_->item(row, 1)->text().toStdString().c_str()<<std::endl<< table_->item(row, 3)->text().toStdString().c_str()<<std::endl;
    if(column == 7) {
        emit setRequest(table_->item(row, column)->text().toStdString().c_str(), table_->item(row, 1)->text().toStdString().c_str(), table_->item(row, 3)->text().toStdString().c_str());
    }
}

void MainWidget::displayErrorMessageLogin() {
    error_label_->setStyleSheet("QLabel { color: red; }");
    QTimer::singleShot(1500, [=]() {
        error_label_->setStyleSheet("QLabel { color: rgb(182, 197, 219); }");
    });
}

void MainWidget::populate(data::Response data) {
    
    table_->clearContents();
    table_->setRowCount(data.devices_size() - 1);
    int row = -1;

    for(const auto &device: data.devices()) {
        if(device.id() == 0)
        {
            router_ip_->setText("Router's IP address: " + QString::fromStdString(device.ip_address()));
            router_mac_->setText("Router's MAC address: " + QString::fromStdString(device.mac_address()));
        }
        else {
            row++;
            table_->setItem(row, 0, new QTableWidgetItem(QString::number(device.id())));
            table_->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(device.name())));
            table_->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(device.ip_address())));
            table_->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(device.mac_address())));

            QTableWidgetItem *item_is_o = new QTableWidgetItem(QString::fromStdString("off"));
            item_is_o->setForeground(Qt::red);
            if(device.is_online()){
                item_is_o = new QTableWidgetItem(QString::fromStdString("on"));
                item_is_o->setForeground(QColor(0, 100, 0));
            }
            table_->setItem(row, 4, item_is_o);
            

            QTableWidgetItem *item_is_b = new QTableWidgetItem(QString::fromStdString("no"));
            item_is_b->setForeground(QColor(0, 100, 0));
            if(device.is_blocked()){
                item_is_b = new QTableWidgetItem(QString::fromStdString("yes"));
                item_is_b->setForeground(Qt::red);
            }
            table_->setItem(row, 5, item_is_b);

            QTableWidgetItem *item_is_t = new QTableWidgetItem(QString::fromStdString("no"));
            item_is_t->setForeground(QColor(0, 100, 0));
            if(device.is_trusted()){
                item_is_t = new QTableWidgetItem(QString::fromStdString("yes"));
                item_is_t->setForeground(Qt::red);
            }
            table_->setItem(row, 6, item_is_t);

            QTableWidgetItem *item_b = new QTableWidgetItem(QString::fromStdString("Block"));
            item_b->setBackground(Qt::red);
            if(device.is_blocked()){
                item_b = new QTableWidgetItem(QString::fromStdString("Unblock"));
                item_b->setBackground(Qt::green);
            }
            table_->setItem(row, 7, item_b);
        }
    }

}