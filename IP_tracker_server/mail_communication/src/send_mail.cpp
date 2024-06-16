#include "../include/send_mail.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void SendMail::send() {
    std::lock_guard<std::mutex> lock(mail_mutex_);

    command_ = "/home/bianca/ip_tracker/IP_tracker_server/mail_communication/send_mail.sh \"" + 
            smtp_server_ + "\" \"" + email_sender_ + "\" \"" + password_sender_ + "\" \"" +
            email_sender_ + "\" \"" + email_receiver_ + "\" \"" + mail_file_ + "\"";

    system(command_.c_str());

}

void SendMail::setEmail(const std::string &email_receiver) {
    std::lock_guard<std::mutex> lock(mail_mutex_);
    email_receiver_ = email_receiver; 
}
