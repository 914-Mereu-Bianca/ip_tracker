#ifndef _SQL_CONNECTOR_H_
#define _SQL_CONNECTOR_H_

#include <memory>
#include "../../build/proto_generated/ip_tracker.grpc.pb.h"
#include "../../build/proto_generated/ip_tracker.pb.h"
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include <cppconn/prepared_statement.h>

class SqlConnector {

public:
    
    SqlConnector();
    ~SqlConnector();
    void addDevice(data::Device device);
    void updateDevice(data::Device device);
    void removeDevice(const std::string &mac_address);
    void clearTable();
    bool checkIfMacExists(const std::string &mac_address);
    bool checkIsBlocked(const std::string &mac_address);
    bool checkIsRemembered(const std::string &mac_address);
    void renameDevice(const std::string &name, const std::string &mac_address);
    void setRemembered(bool remembered, const std::string &mac_address);
    void setCredentials(const std::string &username, const std::string &password);
    void setEmail(const std::string &email);
    std::string getUsername();
    std::string getPassword();
    std::string getEmail();
    std::string getName(const std::string &mac_address);

    std::vector<data::Device> getDevices();

private:

    sql::Driver* driver; // cannot use unique_ptr for sql::Driver
    std::unique_ptr<sql::Connection> con;
    std::unique_ptr<sql::Statement> stmt;
    std::unique_ptr<sql::ResultSet> res;
    std::unique_ptr<sql::PreparedStatement> pstmt;
    std::unique_ptr<sql::PreparedStatement> pstmt_rename;
    std::unique_ptr<sql::PreparedStatement> pstmt_remembered;
    std::unique_ptr<sql::PreparedStatement> pstmt_credentials;
    std::unique_ptr<sql::PreparedStatement> pstmt_email;

};

#endif