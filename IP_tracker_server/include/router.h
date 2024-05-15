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
    std::string blockDevice(std::string &name, std::string &mac);
    void setToken(const std::string &token);

private:

    std::string token_;
    CURL *curl;
    CURLcode res;
    std::string url_get_;
    std::string url_block_;

};

#endif //_ROUTER_H_