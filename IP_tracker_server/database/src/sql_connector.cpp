#include "../include/sql_connector.h"
//#include <sqlite3.h>
#include <iostream>

SqlConnector::SqlConnector() {

    driver = get_driver_instance();
    con.reset(driver->connect("tcp://127.0.0.1:3306", "bia", "root"));
    con->setSchema("ip_tracker");
    pstmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(
        "UPDATE device SET name=?, ip=?, blocked=?, remembered=? WHERE mac=?"));
    pstmt_rename = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(
        "UPDATE device SET name=? WHERE mac=?"));
    pstmt_remembered = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(
        "UPDATE device SET remembered=? WHERE mac=?"));

}

SqlConnector::~SqlConnector() {
}

void SqlConnector::clearTable() {
    stmt.reset(con->createStatement());
    std::string truncateQuery = "TRUNCATE TABLE device";
    stmt->executeUpdate(truncateQuery);
}

void SqlConnector::addDevice(data::Device device) {
    stmt.reset(con->createStatement());
    std::string insertQuery = "INSERT INTO device (name, ip, mac, blocked, remembered) VALUES ('" + device.name() + "', '" + device.ip_address() + "', '" + device.mac_address() + "', " + (device.is_blocked() ? "1" : "0") + ", " + (device.is_remembered() ? "1" : "0") + ")";
    stmt->executeUpdate(insertQuery);
}


void SqlConnector::updateDevice(data::Device device) {
    pstmt->setString(1, device.name());
    pstmt->setString(2, device.ip_address());
    pstmt->setInt(3, device.is_blocked() ? 1 : 0);
    pstmt->setInt(4, device.is_remembered() ? 1 : 0);
    pstmt->setString(5, device.mac_address());

    pstmt->executeUpdate();
}

void SqlConnector::renameDevice(const std::string &name, const std::string &mac_address) {
    pstmt_rename->setString(1, name);
    pstmt_rename->setString(2, mac_address);

    pstmt_rename->executeUpdate();
}

void SqlConnector::setRemembered(bool remembered, const std::string &mac_address) {
    pstmt_remembered->setInt(1, remembered);
    pstmt_remembered->setString(2, mac_address);

    pstmt_remembered->executeUpdate();
}


void SqlConnector::removeDevice(const std::string &mac_address) {
    stmt.reset(con->createStatement());
    std::string deleteQuery = "DELETE FROM device WHERE mac = '" + mac_address + "'";
    stmt->executeUpdate(deleteQuery);
}

bool SqlConnector::checkIfMacExists(const std::string &mac_address) {
    stmt.reset(con->createStatement());
    std::string checkQuery = "SELECT COUNT(*) FROM device WHERE mac = '" + mac_address + "'";
    res.reset(stmt->executeQuery(checkQuery));
    if (res->next() && res->getInt(1) > 0) {
       return true;
    }
    return false;
}

bool SqlConnector::checkIsBlocked(const std::string &mac_address) {
    stmt.reset(con->createStatement());
    std::string checkQuery = "SELECT blocked FROM device WHERE mac = '" + mac_address + "'";
    res.reset(stmt->executeQuery(checkQuery));
    if (res->next()) {
        return res->getInt(1);
    } else {
        throw std::runtime_error("No matching records found.");
    }
}

bool SqlConnector::checkIsRemembered(const std::string &mac_address) {
    stmt.reset(con->createStatement());
    std::string checkQuery = "SELECT remembered FROM device WHERE mac = '" + mac_address + "'";
    res.reset(stmt->executeQuery(checkQuery));
    if (res->next()) {
        return res->getInt(1);
    } else {
        throw std::runtime_error("No matching records found.");
    }
}

std::string SqlConnector::getName(const std::string &mac_address) {
    stmt.reset(con->createStatement());
    std::string checkQuery = "SELECT name FROM device WHERE mac = '" + mac_address + "'";
    res.reset(stmt->executeQuery(checkQuery));
    if (res->next()) {
        return res->getString(1);
    } else {
        throw std::runtime_error("No matching records found.");
    }
}

std::vector<data::Device> SqlConnector::getDevices() {
    std::vector<data::Device> devices;
    stmt.reset(con->createStatement());

    res.reset(stmt->executeQuery("SELECT * FROM device"));

    data::Device device;
    while (res->next()) {
        device.set_id(res->getInt("id"));
        device.set_name(res->getString("name"));
        device.set_ip_address(res->getString("ip"));
        device.set_mac_address(res->getString("mac"));
        device.set_is_blocked(res->getInt("blocked"));
        device.set_is_remembered(res->getInt("remembered"));
        devices.push_back(device);
    }
    return devices;
}
    
