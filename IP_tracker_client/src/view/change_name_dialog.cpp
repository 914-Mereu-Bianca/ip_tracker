#include "view/change_name_dialog.h"
#include <QTimer>
#include <iostream>

ChangeNameDialog::ChangeNameDialog(QWidget *parent) 
    : QDialog(parent) {
    setWindowTitle("Change Name");
    dialog_box_layout_ = new QVBoxLayout(this);

    new_name_ = new QLineEdit;
    new_name_->setFixedWidth(240);
    new_name_->setStyleSheet("QLineEdit { height: 30px; background-color: white; border: 1px solid rgb(37, 39, 48); border-radius: 15px; padding-left: 10px; } QLineEdit:hover { border-color: rgb(129, 140, 140);}");
    dialog_box_layout_->addWidget(new_name_);

    button_save_ = new QPushButton("Save");
    button_save_->setFixedWidth(100);
    button_save_->setStyleSheet("QPushButton { height: 30px; background-color: rgb(37, 39, 48); color: rgb(255, 255, 255); border-radius: 15px; } QPushButton:hover { background-color: rgb(129, 140, 140);}");
    dialog_box_layout_->addWidget(button_save_, 0, Qt::AlignCenter);

    error_label_box_ = new QLabel("Error", this);
    error_label_box_->setStyleSheet("color: rgb(235, 235, 235);");
    dialog_box_layout_->addWidget(error_label_box_, 0, Qt::AlignCenter);

    connect(button_save_, &QPushButton::clicked, [this]() {
        emit saveName("rename", new_name_->text().toStdString().c_str(), mac_);
        this->close();
    });
}

void ChangeNameDialog::displayMessageDialogName(const std::string &message) {
    error_label_box_->setText(QString::fromStdString(message));
    error_label_box_->setStyleSheet("color: red;");
    QTimer::singleShot(1500, [=]() {
        error_label_box_->setStyleSheet("color: rgb(235, 235, 235);");
    });
}

void ChangeNameDialog::execute(const std::string &name, const std::string &mac) {
    mac_ = mac;
    new_name_->setText(name.c_str());
    this->exec();
}