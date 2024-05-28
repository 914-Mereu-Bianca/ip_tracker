#include "view/email_dialog.h"
#include <QTimer>

EmailDialog::EmailDialog(QWidget *parent) 
    : QDialog(parent) {
    setWindowTitle("New Email");
    dialog_box_layout_email_ = new QVBoxLayout(this);

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

    connect(button_save_email_, &QPushButton::clicked, [&]() {
        emit saveEmail(new_email_->text().toStdString().c_str(), current_password_email_->text().toStdString().c_str());
    });
}

void EmailDialog::displayMessageDialogEmail(const std::string &message) {
    error_label_box_email_->setText(QString::fromStdString(message));
    error_label_box_email_->setStyleSheet("color: red;");
    QTimer::singleShot(1500, [=]() {
        error_label_box_email_->setStyleSheet("color: rgb(235, 235, 235);");
    });
}