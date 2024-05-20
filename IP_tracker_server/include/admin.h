#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <string>

class Admin {

public:
    Admin();
    inline std::string getUsernameHashed() { return username_hashed_; }
    inline std::string getPasswordHashed() { return password_hashed_; }

    void saveCredentials(const std::string &username_hashed, const std::string &password_hashed);

    std::string computeHash(const std::string &credential);

private:

    std::string username_hashed_;
    std::string password_hashed_;

};

#endif