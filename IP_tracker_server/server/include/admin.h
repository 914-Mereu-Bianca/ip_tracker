#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <string>
#include <memory>
#include "../../database/include/sql_connector.h"

class Admin {

public:
    Admin(std::shared_ptr<SqlConnector> sql_connector);
    bool checkPassword(const std::string &password);
    bool checkUsername(const std::string &username);
    void saveCredentials(const std::string &username, const std::string &password);

private:

    std::string computeHash(const std::string &credential);
    
    std::shared_ptr<SqlConnector> SQL_connector_;
    std::string username_hashed_;
    std::string password_hashed_;

};

#endif