#include "view/main_widget.h"
#include "view/main_window.h"
#include "client_modelview.h"
#include "view/rounded_item_delegate.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>


MainWidget::MainWidget(QMainWindow *parent)
        :QWidget(parent),
        credentialsDialog_(new CredentialsDialog(this)), emailDialog_(new EmailDialog(this)), validationDialog_(new ValidationDialog(this)), changeNameDialog_(new ChangeNameDialog(this)) {

    layout_ = new QVBoxLayout;
    central_widget_ = new QWidget;
    central_widget_->setLayout(layout_); 
    parent->setCentralWidget(central_widget_);
    layout_->setAlignment(Qt::AlignCenter);

    LoadStylesheet();
    SetupLoginPage();

    connect(credentialsDialog_, &CredentialsDialog::saveCredentials, this, &MainWidget::saveCredentials);
    connect(emailDialog_, &EmailDialog::saveEmail, this, &MainWidget::saveEmail);
    connect(changeNameDialog_, &ChangeNameDialog::saveName, this, &MainWidget::manageDevice);
    connect(validationDialog_, &ValidationDialog::performRequest, this, &MainWidget::performRequest);
    connect(this, &MainWidget::displayMessageDialogCredentials, credentialsDialog_, &CredentialsDialog::displayMessageDialogCredentials);
    connect(this, &MainWidget::displayMessageDialogEmail, emailDialog_, &EmailDialog::displayMessageDialogEmail);
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
    button_->setDefault(true);
    connect(button_, &QPushButton::clicked, this, &MainWidget::HandleLogin);

    // ------ Setup the Error Message -------
    error_label_ = new QLabel("Authentication Failed!", this);
    error_label_->setStyleSheet("QLabel { color: rgb(182, 197, 219); }");
    layout_->addWidget(error_label_, 0, Qt::AlignCenter);

    reset_credentials_button_ = new QPushButton("Reset Credentials", this);
    reset_credentials_button_->setFixedSize(150, 35);
    reset_credentials_button_->setStyleSheet(" QPushButton:hover {background-color: red;} QPushButton:focus {background-color: red;}");
    layout_->addWidget(reset_credentials_button_, 0, Qt::AlignCenter);
    connect(reset_credentials_button_, &QPushButton::clicked, [&]() {
        emit validationDialog_->execute("new credentials", "", "");
    });
}

void MainWidget::setupMainPage() {
    // ----- Set the visibility to false for the widgets from the login page -----
    username_input_->setVisible(0);
    password_input_->setVisible(0);
    button_->setVisible(0);
    error_label_->setVisible(0);
    image_label_->setVisible(0);
    reset_credentials_button_->setVisible(0);
    
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

    connect(change_email_button_, &QPushButton::clicked, emailDialog_, &QDialog::exec);
    

    // Desgin and add the table
    table_ = new QTableWidget;
    layout_->addWidget(table_); 
    table_->setColumnCount(8);
    table_->setHorizontalHeaderLabels(QStringList() << "ID" << "Device Name" << "IP Address" << "MAC Address" << "Online" << "Blocked" << "Manage device" << "");
    table_->setShowGrid(false);
    for (int i = 1; i < table_->columnCount() - 1; ++i) {
        table_->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    table_->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    table_->horizontalHeader()->setSectionResizeMode(table_->columnCount() - 1, QHeaderView::Interactive);
    table_->setColumnWidth(0, 30);
    table_->setColumnWidth(table_->columnCount() - 1, 30);
    table_->setItemDelegate(new RoundedItemDelegate(table_));
    table_->horizontalHeader()->setStyleSheet("QHeaderView::section { height: 20px; background-color: black; color: white; padding: 4px; border: 1px solid gray; }");
    
    connect(table_, &QTableWidget::cellClicked, this, &MainWidget::onCellClicked);
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
    if(column == 1) {
        changeNameDialog_->execute(table_->item(row, 1)->text().toStdString().c_str(), table_->item(row, 3)->text().toStdString().c_str());
    }
    if(column == 6) {
        validationDialog_->execute(table_->item(row, column)->text().toStdString().c_str(), table_->item(row, 1)->text().toStdString().c_str(), table_->item(row, 3)->text().toStdString().c_str());
        //emit setRequest(table_->item(row, column)->text().toStdString().c_str(), table_->item(row, 1)->text().toStdString().c_str(), table_->item(row, 3)->text().toStdString().c_str());
    }
    if(column == 7) {
        validationDialog_->execute("delete", table_->item(row, 1)->text().toStdString().c_str(), table_->item(row, 3)->text().toStdString().c_str());
    }
}
 
// preformRequest from validation meaning request can be "delete", "Block" or "Unblock"
void MainWidget::performRequest(const std::string &request, const std::string &name, const std::string &mac) {
    std::cout<<request<<std::endl;
    if(request == "delete") {
        emit manageDevice(request, name, mac);
    }
    else {
        emit setRequest(request, name, mac);
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
        if(device.id() == 1)
        {
            router_ip_->setText("Router's IP address: " + QString::fromStdString(device.ip_address()));
            router_mac_->setText("Router's MAC address: " + QString::fromStdString(device.mac_address()));
        }
        else {
            row++;

            QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(device.id()));
            QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(device.name()));
            QTableWidgetItem* ipItem = new QTableWidgetItem(QString::fromStdString(device.ip_address()));
            QTableWidgetItem* macItem = new QTableWidgetItem(QString::fromStdString(device.mac_address()));

            idItem->setData(Qt::UserRole, device.is_remembered());
            nameItem->setData(Qt::UserRole, device.is_remembered());
            ipItem->setData(Qt::UserRole, device.is_remembered());
            macItem->setData(Qt::UserRole, device.is_remembered());

            table_->setItem(row, 0, idItem);
            table_->setItem(row, 1, nameItem);
            table_->setItem(row, 2, ipItem);
            table_->setItem(row, 3, macItem);

            QTableWidgetItem *item_is_o = new QTableWidgetItem(QString::fromStdString("off"));
            item_is_o->setForeground(Qt::red);
            if(device.is_online()){
                item_is_o = new QTableWidgetItem(QString::fromStdString("on"));
                item_is_o->setForeground(QColor(0, 100, 0));
            }
            item_is_o->setData(Qt::UserRole, device.is_remembered());
            table_->setItem(row, 4, item_is_o);
            

            QTableWidgetItem *item_is_b = new QTableWidgetItem(QString::fromStdString("no"));
            item_is_b->setForeground(QColor(0, 100, 0));
            if(device.is_blocked()){
                item_is_b = new QTableWidgetItem(QString::fromStdString("yes"));
                item_is_b->setForeground(Qt::red);
            }
            item_is_b->setData(Qt::UserRole, device.is_remembered());
            table_->setItem(row, 5, item_is_b);

            QTableWidgetItem *item_b = new QTableWidgetItem(QString::fromStdString("Block"));
            item_b->setTextAlignment(Qt::AlignCenter);
            if(device.is_blocked()){
                item_b->setText(QString::fromStdString("Unblock"));
            }
            table_->setItem(row, 6, item_b);

            QTableWidgetItem *item_delete = new QTableWidgetItem(QString::fromStdString("X"));
            item_delete->setTextAlignment(Qt::AlignCenter);
            item_delete->setForeground(Qt::white);
            table_->setItem(row, 7, item_delete);

        }
    }

}