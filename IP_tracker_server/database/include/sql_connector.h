#ifndef _SQL_CONNECTOR_H_
#define _SQL_CONNECTOR_H_

#include <memory>
#include <sqlite3.h>
#include "../../build/proto_generated/ip_tracker.grpc.pb.h"
#include "../../build/proto_generated/ip_tracker.pb.h"

class SqlConnector {

public:
    
    SqlConnector();
    ~SqlConnector();
    void createTable(const std::string &table);
    void dropTable(const std::string &table);
    void addDevice(data::Device device);
    std::vector<data::Device> getDevices();

private:

    void executeCommand(const std::string &command);
    sqlite3* database_;

};

#endif