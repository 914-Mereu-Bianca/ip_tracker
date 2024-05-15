#include "../include/router.h"
#include <iostream>

Router::Router() {

}

Router::~Router() {
}

size_t Router::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string Router::getAllDevices()
{

    CURL *curl = curl_easy_init();
    std::string response;
    if (curl) {

        std::string url = "http://tplinkwifi.net/?code=2&asyn=1&id=" + token_;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "13|1,0,0"); // Set the body data

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Router::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl); // Perform the POST request

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