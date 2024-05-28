#include "server/include/server.h"
#include "server/include/admin.h"
#include "database/include/sql_connector.h"
#include "mail_communication/include/send_mail.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <sqlite3.h>
//#include <mysqlx/xdevapi.h
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"


int main() {
    Admin admin("../utils/credentials.txt");
    MainService server("0.0.0.0", 50051, admin); 
    server.runServer();

    
    /*SqlConnector sc;
    data::Device d;
    d.set_id(3); d.set_name(""); d.set_ip_address("172.20.10.9"); d.set_mac_address("f8-94-c2-04-34-c2");
    d.set_is_blocked(0); d.set_is_online(1); d.set_is_trusted(0);
    sc.updateDevice(d);*/
    //sc.clearTable();
    /*d.set_id(0); d.set_name("deviceee"); d.set_ip_address("1.2.2.3"); d.set_mac_address("4a-35-2b-90-22-44");
    d.set_is_blocked(1); d.set_is_online(1); d.set_is_trusted(1);
    //sc.addDevice(d);
    //d.set_mac_address("54-8c-a0-3a-8c-ba");
    //sc.removeDevice(d.mac_address());
    for(const auto &d : sc.getDevices()) {
        std::cout<<d.id()<< " " << d.ip_address()<<" "<<d.mac_address()<<std::endl;
    }

    std::cout<<sc.checkIfMacExists("4a-35-2b-90-22-64")<<std::endl;
    std::cout<<sc.checkIfMacExists("4a-35-2b-90-22")<<std::endl;*/
}