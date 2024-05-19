#ifndef _SEND_MAIL_H_
#define _SEND_MAIL_H_

#include <string>
#include <curl/curl.h>

class SendMail {

public:
    SendMail();
    static size_t write_callback(void *ptr, size_t size, size_t nmemb, std::string *data);
    void send();

private:

};

#endif  //_SEND_MAIL_H_