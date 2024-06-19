#include "view/validation_dialog.h"

ValidationDialog::ValidationDialog(QWidget *parent) 
    : QDialog(parent) {
    setWindowTitle("Validation");
    layout_= new QVBoxLayout(this);
    button_layout_ = new QHBoxLayout;
    validation_label_ = new QLabel(this);
    layout_->addWidget(validation_label_, 0, Qt::AlignCenter);
    
    ok_button_ = new QPushButton("Yes");
    ok_button_->setFixedWidth(100);
    ok_button_->setStyleSheet("QPushButton { height: 30px; background-color: rgb(37, 39, 48); color: rgb(255, 255, 255); border-radius: 15px; } QPushButton:hover { background-color: rgb(129, 140, 140);}");

    cancel_button_ = new QPushButton("No");
    cancel_button_->setFixedWidth(100);
    cancel_button_->setStyleSheet("QPushButton { height: 30px; background-color: rgb(37, 39, 48); color: rgb(255, 255, 255); border-radius: 15px; } QPushButton:hover { background-color: rgb(129, 140, 140);}");

    button_layout_->addWidget(cancel_button_);
    button_layout_->addWidget(ok_button_);
    layout_->addLayout(button_layout_);

    connect(ok_button_, &QPushButton::clicked, [&]() {
        emit performRequest(request_, name_, mac_);
        this->close();
    });
    connect(cancel_button_, &QPushButton::clicked, [&]() {
        this->close();
    });
}

void ValidationDialog::execute(const std::string &request, const std::string &name, const std::string &mac) {
    request_ = request;
    name_ = name;
    mac_ = mac;
    if(request == "reset credentials")
        validation_label_->setText("  Are you sure you want to \n    reset the credentials?");
    else 
        validation_label_->setText(QString::fromStdString("  Are you sure you want to " + std::string(request) + "\nthe device having its MAC address\n           " + std::string(mac)));
    this->exec();
}