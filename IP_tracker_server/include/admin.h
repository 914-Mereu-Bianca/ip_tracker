#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <string>

class Admin {

public:
    inline std::string getName() { return username_; }
    inline std::string getPassword() { return password_; }
    
    void saveCredentials();

private:
    Admin() {}

    std::string username_;
    std::string password_;

};

#endif