#ifndef _SEND_MAIL_H_
#define _SEND_MAIL_H_

#include <string>
#include <curl/curl.h>
#include <mutex>

class SendMail {

public:
    SendMail() : email_receiver_("biamereu2002@gmail.com") {}
    SendMail(const std::string &email_receiver) : email_receiver_(email_receiver) {}
    void setEmail(const std::string &email_receiver);
    void send();

private:

    std::mutex mail_mutex_;

    std::string smtp_server_ = "smtps://smtp.gmail.com:465";
    std::string email_receiver_ = "";
    std::string email_sender_ = "routera575@gmail.com";
    std::string password_sender_ = "njya umcc pzyz wgab";
    std::string mail_file_ = "/home/bianca/ip_tracker/IP_tracker_server/utils/mail.txt";
    std::string command_;

};

#endif  //_SEND_MAIL_H_