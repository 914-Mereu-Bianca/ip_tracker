#include "include/data_parser.h"
#include "include/server.h"
#include "include/mail_communication/send_mail.h"
#include "include/admin.h"

#include <fstream>
#include <sstream>
#include <memory>

int main() {
    Admin admin("../utils/credentials.txt");
    MainService server("0.0.0.0", 50051, admin); 
    server.runServer();

    return 0;
}