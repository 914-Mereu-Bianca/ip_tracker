#include "server/include/server.h"
#include "server/include/admin.h"
#include "database/include/sql_connector.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <sqlite3.h>

int main() {
    Admin admin("../utils/credentials.txt");
    MainService server("0.0.0.0", 50051, admin); 
    server.runServer();

    /*SqlConnector sc;
    sc.dropTable("DEVICE");
    sc.createTable("DEVICE");
    data::Device d;
    d.set_id(0);
    d.set_name("device1");
    d.set_ip_address("1.2.2.3");
    d.set_mac_address("aa-ss-sd");
    d.set_is_blocked(1);
    d.set_is_online(1);
    d.set_is_trusted(1);
    sc.addDevice(d);
    sc.getDevices();*/
    
}