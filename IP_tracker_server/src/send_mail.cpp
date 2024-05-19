#include "../include/send_mail.h"

#include <iostream>

SendMail::SendMail() {
    
}

size_t SendMail::write_callback(void *ptr, size_t size, size_t nmemb, std::string *data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

void SendMail::send() {

    CURL *curl;
    CURLcode res;

    // Initialize curl
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl." << std::endl;
    }

    // SMTP server configuration
    curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");

    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<routera575@gmail.com>");
    curl_easy_setopt(curl, CURLOPT_USERNAME, "routera575@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "njya umcc pzyz wgab");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    std::cout<<"OK"<<std::endl;
    struct curl_slist *recipients = NULL;
    recipients = curl_slist_append(recipients, "<biamereu2002@gmail.com>");
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    std::cout<<"OK1"<<std::endl;
    // Email content

    std::string email_data = "From: \"Router Admin\" <routera575@gmail.com>\r\nTo: \"Bia Mereu\" <biamereu2002@gmail.com>\r\nSubject: This is a test\r\n\r\nHi John,\r\nIm sending this mail with curl thru my gmail account.\r\nBye!\r\n";
    std::cout<<email_data;
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, SendMail::write_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, &email_data);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    std::cout<<"OK2"<<std::endl;
    // Perform the SMTP operation
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Failed to send email: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << "Email sent successfully." << std::endl;
    }
    std::cout<<"OK3"<<std::endl;

    // Clean up
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

}
