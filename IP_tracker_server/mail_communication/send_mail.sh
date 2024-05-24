#!/bin/bash

SMTP_SERVER=$1
USERNAME=$2
PASSWORD=$3
MAIL_FROM=$4
MAIL_RCPT=$5
MAIL_FILE=$6

curl --ssl-reqd \
     --url "$SMTP_SERVER" \
     --user "$USERNAME:$PASSWORD" \
     --mail-from "$MAIL_FROM" \
     --mail-rcpt "$MAIL_RCPT" \
     --upload-file "$MAIL_FILE"
