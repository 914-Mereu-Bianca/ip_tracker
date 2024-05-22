#include "../include/sql_connector.h"
#include <sqlite3.h>
#include <iostream>

SqlConnector::SqlConnector() {
    int response = sqlite3_open("/home/bianca/ip_tracker/IP_tracker_server/database/ip_tracker.db", &database_);
    if (response != SQLITE_OK) {
        std::cout << "Can't open database: " << sqlite3_errmsg(database_) << std::endl;
    } 
}

SqlConnector::~SqlConnector() {
    sqlite3_close(database_);
}

void SqlConnector::executeCommand(const std::string &command) {
    char *errMsg = nullptr;
    int response = sqlite3_exec(database_, command.c_str(), nullptr, 0, &errMsg);
    if (response != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Command executed successfully" << std::endl;
    }
}

void SqlConnector::createTable(const std::string &table) {
    std::string sql = "CREATE TABLE IF NOT EXISTS " + table + "(" \
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                      "NAME         TEXT," \
                      "IP           TEXT    NOT NULL," \
                      "MAC          TEXT    NOT NULL," \
                      "BLOCKED      INT    NOT NULL," \
                      "TRUSTED      INT    NOT NULL);";
    executeCommand(sql);
}

void SqlConnector::dropTable(const std::string &table) {
    std::string sql = "DROP TABLE IF EXISTS " + table + ";";
    return executeCommand(sql);
}


void SqlConnector::addDevice(data::Device device) {
    std::string sql = "INSERT INTO DEVICE (NAME, IP, MAC, BLOCKED, TRUSTED)" \
        "VALUES ( '" + device.name() + "', '" + device.ip_address() + "', '" + device.mac_address() + "', '" + (device.is_blocked() ? "1" : "0") + "', '" + (device.is_trusted() ? "1" : "0") + "');";
    executeCommand(sql);
}


std::vector<data::Device> SqlConnector::getDevices() {
    std::vector<data::Device> dev;
    std::string sql = "SELECT * FROM DEVICE;";
    sqlite3_stmt *stmt;
    int response = sqlite3_prepare_v2(database_, sql.c_str(), -1, &stmt, nullptr);
    if (response == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            auto name = sqlite3_column_text(stmt, 1);
            auto ip = sqlite3_column_text(stmt, 2);
            auto mac = sqlite3_column_text(stmt, 3);
            auto blocked = sqlite3_column_int(stmt, 4);
            auto trusted = sqlite3_column_int(stmt, 5);
            std::cout << "id: " << id << " name: " << name << " ip: " << ip << " mac: " << mac << " blocked: " << blocked << " trusted: " << trusted << std::endl;
        }
        std::cout<<"OK1"<<std::endl;
        sqlite3_finalize(stmt);
        std::cout<<"OK2"<<std::endl;
    } else {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(database_) << std::endl;
    }
    return dev;
}
    
