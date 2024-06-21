#include "server/include/server.h"
#include "server/include/admin.h"
#include "database/include/sql_connector.h"
#include "mail_communication/include/send_mail.h"
#include <fstream>
#include <sstream>
#include <memory>
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"


int main() {
    std::cout<<"OK"<<std::endl;
    MainService server("0.0.0.0", 50051); 
    server.runServer();
}