#ifndef _SEND_MAIL_H_
#define _SEND_MAIL_H_

#include <string>
#include <curl/curl.h>

class SendMail {

public:
    SendMail() : email_receiver_("biamereu2002@gmail.com") {}
    SendMail(const std::string &email_receiver) : email_receiver_(email_receiver) {}
    inline void setEmail(const std::string &email_receiver) { email_receiver_ = email_receiver; };
    void send();

private:

    std::string email_receiver_ = "";
    std::string email_sender_ = "routera575@gmail.com";
    std::string password = "njya umcc pzyz wgab";

};

#endif  //_SEND_MAIL_H_