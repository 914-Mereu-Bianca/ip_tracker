#include "../include/send_mail.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

SendMail::SendMail() {
    setEmail("biamereu2002@gmail.com");
}

void SendMail::send() {
    std::lock_guard<std::mutex> lock(mail_mutex_);
    system(command_blocked_.c_str());
}

void SendMail::resetCredentials(const std::string &username, const std::string &password) {
    std::lock_guard<std::mutex> lock(mail_mutex_);
    updateMailContentReset(username, password);
    system(command_reset_.c_str());
}

void SendMail::setEmail(const std::string &email_receiver) {
    std::lock_guard<std::mutex> lock(mail_mutex_);
    email_receiver_ = email_receiver; 
    updateMailContent();
}

void SendMail::updateMailContent() {
    std::string mail_content_blocked_ = "From: \"Router Admin\" <" + email_sender_ + ">\n"
                            "To: \"Admin\" <" + email_receiver_ + ">\n"
                            "Subject: Security Alert\n"
                            "\n"
                            "Hi Admin,\n"
                            "A new device has connected.";
    
    std::string path_to_mail = "./mail.txt";

    std::ofstream file(path_to_mail);
    if (file.is_open()) {
        file << mail_content_blocked_;
        file.close();
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }

    command_blocked_ = "curl --ssl-reqd "
               "--url \"" + smtp_server_ + "\" "
               "--user \"" + email_sender_ + ":" + password_sender_ + "\" "
               "--mail-from \"" + email_sender_ + "\" "
               "--mail-rcpt \"" + email_receiver_ + "\" "
               "--upload-file \"" + path_to_mail + "\"";
    
}

void SendMail::updateMailContentReset(const std::string &username, const std::string &password) {
    std::string mail_content_reset_ = "From: \"Router Admin\" <" + email_sender_ + ">\n"
                          "To: \"Admin\" <" + email_receiver_ + ">\n"
                          "Subject: New Credentials\n"
                          "\n"
                          "Hi Admin,\n"
                          "The credentials have been resetted. The new credentials are username: "+ username +" password: "+ password ;
    
    std::string path_to_mail = "./reset.txt";

    std::ofstream file(path_to_mail);
    if (file.is_open()) {
        file << mail_content_reset_;
        file.close();
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }

    command_reset_ = "curl --ssl-reqd "
               "--url \"" + smtp_server_ + "\" "
               "--user \"" + email_sender_ + ":" + password_sender_ + "\" "
               "--mail-from \"" + email_sender_ + "\" "
               "--mail-rcpt \"" + email_receiver_ + "\" "
               "--upload-file \"" + path_to_mail + "\"";
    
}