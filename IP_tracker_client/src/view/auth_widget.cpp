#include "view/auth_widget.h"
#include "main_window.h"
#include <iostream>

AuthWidget::AuthWidget(QMainWindow *parent)
        :QWidget(parent) {
    // Setup the layout
    layout_ = new QVBoxLayout;
    central_widget_ = new QWidget;

    central_widget_->setLayout(layout_); 
    parent->setCentralWidget(central_widget_);

    central_widget_->setStyleSheet("background-color: lightblue;");
    layout_->setAlignment(Qt::AlignCenter);
}

void AuthWidget::SetupWidgets() {
    

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
    error_label_->setVisible(1);
}

void AuthWidget::HandleButtonClick() {
    clicked_ = 1;
    std::cout<<username_input_->text().toStdString().c_str()<<" "<<password_input_->text().toStdString().c_str()<<std::endl;
}

void AuthWidget::clear() {
    // Remove all child widgets from the layout
    delete username_label_;
    delete username_input_;
    delete password_label_;
    delete password_input_;
    delete button_;
    delete error_label_;
    delete layout_;
    
}