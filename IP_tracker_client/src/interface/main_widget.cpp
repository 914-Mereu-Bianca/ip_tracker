#include "interface/main_widget.h"
#include "interface/main_window.h"
#include "client_view.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <QStringList>

MainWidget::MainWidget(QMainWindow *parent)
        :QWidget(parent) {

    layout_ = new QVBoxLayout;
    central_widget_ = new QWidget;
    table_ = new QTableWidget;

    central_widget_->setLayout(layout_); 
    parent->setCentralWidget(central_widget_);

    central_widget_->setStyleSheet("background-color: lightblue;");
    layout_->setAlignment(Qt::AlignCenter);

}


void MainWidget::SetupWidgets() {

    username_label_ = new QLabel("Username:", this);
    layout_->addWidget(username_label_);

    username_input_ = new QLineEdit(this);
    layout_->addWidget(username_input_);
    username_input_->setFixedWidth(200);

    password_label_ = new QLabel("Password:", this);
    layout_->addWidget(password_label_);

    password_input_ = new QLineEdit(this);
    password_input_->setFixedWidth(200);
    password_input_->setEchoMode(QLineEdit::Password);
    layout_->addWidget(password_input_);

    // Setup the Login button
    button_ = new QPushButton("Login", this);  
    button_->setFixedSize(100, 35);
    layout_->addWidget(button_);
    
    error_label_ = new QLabel("Authentication Failed!", this);
    layout_->addWidget(error_label_);
    error_label_->setVisible(0);

    connect(button_, &QPushButton::clicked, this, &MainWidget::HandleButtonClick);
}

void MainWidget::HandleButtonClick() {
    std::cout<<username_input_->text().toStdString().c_str()<<" "<<password_input_->text().toStdString().c_str()<<std::endl;
    emit authenticate(username_input_->text().toStdString().c_str(), password_input_->text().toStdString().c_str());
}

void MainWidget::displayErrorMessage() {
    error_label_->setVisible(1);
}

void MainWidget::createTable() {
    
    username_label_->setVisible(0);
    username_input_->setVisible(0);
    password_label_->setVisible(0);
    password_input_->setVisible(0);
    button_->setVisible(0);
    error_label_->setVisible(0);
    
    router_ip_ = new QLabel("Router's IP address:", this);
    router_mac_ = new QLabel("Router's MAC address:", this);
    layout_->addWidget(router_ip_); 
    layout_->addWidget(router_mac_); 
    layout_->addWidget(table_); 
    table_->setColumnCount(7);

    table_->setHorizontalHeaderLabels(QStringList() << "ID" << "Device Name" << "IP Address" << "MAC Address" << "Online" << "Blocked" << "Suspect");
    
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
            table_->setItem(row, 4, new QTableWidgetItem(QString::number(device.is_online())));
            table_->setItem(row, 5, new QTableWidgetItem(QString::number(device.is_blocked())));
            table_->setItem(row, 6, new QTableWidgetItem(QString::number(device.is_suspect())));
        }
    }

}