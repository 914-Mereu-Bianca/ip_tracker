#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <string>

class Admin {

public:
    Admin(const std::string &file_name);
    bool checkPassword(const std::string &password);
    bool checkUsername(const std::string &username);
    void saveCredentials(const std::string &username, const std::string &password);

private:

    std::string computeHash(const std::string &credential);

    std::string file_name_;
    std::string username_hashed_;
    std::string password_hashed_;

};

#endif