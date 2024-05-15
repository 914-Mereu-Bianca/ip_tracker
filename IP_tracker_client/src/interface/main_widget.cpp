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
    table_->setColumnCount(8);

    table_->setHorizontalHeaderLabels(QStringList() << "ID" << "Device Name" << "IP Address" << "MAC Address" << "Online" << "Blocked" << "Suspect" << "Manage device");
    
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

            QTableWidgetItem *item_is_s = new QTableWidgetItem(QString::fromStdString("no"));
            item_is_s->setForeground(QColor(0, 100, 0));
            if(device.is_suspect()){
                item_is_s = new QTableWidgetItem(QString::fromStdString("yes"));
                item_is_s->setForeground(Qt::red);
            }
            table_->setItem(row, 6, item_is_s);

            QTableWidgetItem *item_b = new QTableWidgetItem(QString::fromStdString("Block"));
            item_b->setBackground(Qt::red);
            if(device.is_blocked()){
                item_b = new QTableWidgetItem(QString::fromStdString("Unblock"));
                item_b->setBackground(Qt::green);
            }
            //item_b->setBackground(QColor(211, 211, 211));
            table_->setItem(row, 7, item_b);
        }
    }

}