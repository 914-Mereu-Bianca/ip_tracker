#include "interface/main_widget.h"
#include "interface/main_window.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <QStringList>
#include "main_widget.h"

AuthWidget::AuthWidget(QMainWindow *parent)
        :QWidget(parent) {

    layout_ = new QVBoxLayout;
    central_widget_ = new QWidget;

    central_widget_->setLayout(layout_); 
    parent->setCentralWidget(central_widget_);

    central_widget_->setStyleSheet("background-color: lightblue;");
    layout_->setAlignment(Qt::AlignCenter);
}

void AuthWidget::test() {
    test_ = new QLabel("Test", this);
    layout_->addWidget(test_);
}

void AuthWidget::populate(data::Response data)
{

    table_->ClearContents();
    table_->setRowCount(data.devices_size());

    int row = -1;

    for(const auto &device: data.devices()) {
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


void AuthWidget::SetupWidgets()
{

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

    connect(button_, &QPushButton::clicked, this, &AuthWidget::HandleButtonClick);
}

void AuthWidget::setClicked() {
    clicked_ = 0;
}


void AuthWidget::HandleButtonClick() {
    clicked_ = 1;
    std::cout<<username_input_->text().toStdString().c_str()<<" "<<password_input_->text().toStdString().c_str()<<std::endl;
    error_label_->setVisible(1);
    AuthWidget::createTable();
}

void AuthWidget::clear() {
    // Remove all child widgets from the layout
    delete username_label_;
    delete username_input_;
    delete password_label_;
    delete password_input_;
    delete button_;
    delete error_label_;
    auth = 1;
}

void AuthWidget::createTable() {
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    if(auth){
        table_ = new QTableWidget;
        layout_->addWidget(table_); 
        table_->setColumnCount(7);

        table_->setHorizontalHeaderLabels(QStringList() << "ID" << "Device Name" << "IP Address" << "MAC Address" << "Online" << "Blocked" << "Suspect");
    }
}