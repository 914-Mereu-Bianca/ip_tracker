#include "../../include/mail_communication/send_mail.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

SendMail::SendMail() {
    
}

void SendMail::send() {

    system("/home/bianca/ip_tracker/IP_tracker_server/src/mail_communication/send_mail.sh");

}
