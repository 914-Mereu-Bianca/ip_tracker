#include "../include/router.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

Router::Router() {

}

Router::~Router() {
}

void Router::setToken(const std::string &token) {
    token_ = token;
    url_get_ = "http://tplinkwifi.net/?code=2&asyn=1&id=" + token_;
    url_block_ = "http://tplinkwifi.net/?code=0&asyn=0&id=" + token_;
}

size_t Router::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string Router::getAllDevices() {
    curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url_get_.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "13|1,0,0"); // Set the body data
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Router::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);

        res = curl_easy_perform(curl); // Perform the POST request

        // Check for errors
        if (res != CURLE_OK) {
            std::cout << "Failed to perform POST request: " << curl_easy_strerror(res) << std::endl;
            response = "failed";
        }

        curl_easy_cleanup(curl);

    } else {
        std::cerr << "Failed to initialize libcurl" << std::endl;
    }
    return response;
}


std::string Router::getAllBlockedDevices() {
    curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url_get_.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "73|1,0,0"); // Set the body data
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Router::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);

        res = curl_easy_perform(curl); // Perform the POST request
        
        // Check for errors
        if (res != CURLE_OK) {
            std::cout << "Failed to perform POST request: " << curl_easy_strerror(res) << std::endl;
            response = "failed";
        }
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize libcurl" << std::endl;
    }
    return response;
}


std::string Router::blockDevice(std::string &name, std::string &mac)
{

    curl = curl_easy_init();
    std::string response;
    if (curl) {
        
        curl_easy_setopt(curl, CURLOPT_URL, url_block_.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        name.erase(std::remove_if(name.begin(), name.end(), [](unsigned char c){ return !std::isprint(c);}), name.end());
        mac.erase(std::remove_if(mac.begin(), mac.end(), [](unsigned char c){return !std::isprint(c);}), mac.end());
        
        std::string body = "advanced bm -add list:black name:" + name + " mac:" + mac;  
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str()); // Set the body data
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Router::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);

        res = curl_easy_perform(curl); // Perform the POST request

        // Check for errors
        if (res != CURLE_OK) {
            std::cout << "Failed to perform POST request: " << curl_easy_strerror(res) << std::endl;
            response = "failed";
        }

        curl_easy_cleanup(curl);

    } else {
        std::cerr << "Failed to initialize libcurl" << std::endl;
    }

    return response;

}

std::string Router::unblockDevice(std::string &mac)
{

    curl = curl_easy_init();
    std::string response;
    if (curl) {
        
        curl_easy_setopt(curl, CURLOPT_URL, url_block_.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        mac.erase(std::remove_if(mac.begin(), mac.end(), [](unsigned char c){return !std::isprint(c);}), mac.end());
        
        std::string body = "advanced bm rule -del list:black mac:" + mac;  
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str()); // Set the body data
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Router::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);

        res = curl_easy_perform(curl); // Perform the POST request

        // Check for errors
        if (res != CURLE_OK) {
            std::cout << "Failed to perform POST request: " << curl_easy_strerror(res) << std::endl;
            response = "failed";
        }

        curl_easy_cleanup(curl);

    } else {
        std::cerr << "Failed to initialize libcurl" << std::endl;
    }

    return response;

}