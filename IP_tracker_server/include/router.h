#ifndef _ROUTER_H_
#define _ROUTER_H_

#include <string>
#include <curl/curl.h>

class Router {

public:

    Router();
    ~Router();
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output);
    std::string getAllDevices();
    void setToken(const std::string &token);

private:

    std::string token_;
    CURL *curl;
    CURLcode res;
    std::string url;

};

#endif //_ROUTER_H_