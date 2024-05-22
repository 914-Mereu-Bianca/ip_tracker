#include "../include/send_mail.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void SendMail::send() {

    system("/home/bianca/ip_tracker/IP_tracker_server/mail_communication/send_mail.sh");

}
