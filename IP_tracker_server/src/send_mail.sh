#!/bin/bash

SMTP_SERVER="smtps://smtp.gmail.com:465"
USERNAME="routera575@gmail.com"
PASSWORD="njya umcc pzyz wgab"
MAIL_FROM="routera575@gmail.com"
MAIL_RCPT="biamereu2002@gmail.com"
MAIL_FILE="../utils/mail.txt"

curl --ssl-reqd \
     --url "$SMTP_SERVER" \
     --user "$USERNAME:$PASSWORD" \
     --mail-from "$MAIL_FROM" \
     --mail-rcpt "$MAIL_RCPT" \
     --upload-file "$MAIL_FILE"
