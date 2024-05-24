#include "view/credentials_dialog.h"
#include <QTimer>

CredentialsDialog::CredentialsDialog(QWidget *parent) 
    : QDialog(parent) {
    setWindowTitle("New Credentials");
    dialog_box_layout_ = new QVBoxLayout(this);

    new_username_ = new QLineEdit;
    new_username_->setFixedWidth(240);
    new_username_->setPlaceholderText("New Username");
    new_username_->setStyleSheet("QLineEdit { height: 30px; background-color: white; border: 1px solid rgb(37, 39, 48); border-radius: 15px; padding-left: 10px; } QLineEdit:hover { border-color: rgb(129, 140, 140);}");
    dialog_box_layout_->addWidget(new_username_);

    new_password_ = new QLineEdit;
    new_password_->setFixedWidth(240);
    new_password_->setEchoMode(QLineEdit::Password);
    new_password_->setPlaceholderText("New Password");
    new_password_->setStyleSheet("QLineEdit { height: 30px; background-color: white; border: 1px solid rgb(37, 39, 48); border-radius: 15px; padding-left: 10px; } QLineEdit:hover { border-color: rgb(129, 140, 140);}");
    dialog_box_layout_->addWidget(new_password_);

    current_password_ = new QLineEdit;
    current_password_->setFixedWidth(240);
    current_password_->setEchoMode(QLineEdit::Password);
    current_password_->setPlaceholderText("Current Password");
    current_password_->setStyleSheet("QLineEdit { height: 30px; background-color: white; border: 1px solid rgb(37, 39, 48); border-radius: 15px; padding-left: 10px; } QLineEdit:hover { border-color: rgb(129, 140, 140);}");
    dialog_box_layout_->addWidget(current_password_);

    button_save_credentials_ = new QPushButton("Save");
    button_save_credentials_->setFixedWidth(100);
    button_save_credentials_->setStyleSheet("QPushButton { height: 30px; background-color: rgb(37, 39, 48); color: rgb(255, 255, 255); border-radius: 15px; } QPushButton:hover { background-color: rgb(129, 140, 140);}");
    dialog_box_layout_->addWidget(button_save_credentials_, 0, Qt::AlignCenter);

    error_label_box_ = new QLabel("Error", this);
    error_label_box_->setStyleSheet("color: rgb(235, 235, 235);");
    dialog_box_layout_->addWidget(error_label_box_, 0, Qt::AlignCenter);

    connect(button_save_credentials_, &QPushButton::clicked, [this]() {
        emit saveCredentials(new_username_->text().toStdString().c_str(), new_password_->text().toStdString().c_str(), current_password_->text().toStdString().c_str());
    });
}

void CredentialsDialog::displayMessageDialogCredentials(const std::string &message) {
    error_label_box_->setText(QString::fromStdString(message));
    error_label_box_->setStyleSheet("color: red;");
    QTimer::singleShot(1500, [=]() {
        error_label_box_->setStyleSheet("color: rgb(235, 235, 235);");
    });
}