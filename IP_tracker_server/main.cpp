#include "include/data_parser.h"
#include "include/server.h"
#include "include/mail_communication/send_mail.h"

#include <fstream>
#include <sstream>
#include <memory>

int main() {

    MainService server("0.0.0.0", 50051); 

    server.runServer();

    return 0;
}