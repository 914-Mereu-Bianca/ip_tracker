#!/bin/bash

# Variables
DB_NAME="ip_tracker"
DB_USER="new_user"
DB_PASS="root"
ROOT_PASS="root"

# Create a new database
mysql -u root -p$ROOT_PASS -e "CREATE DATABASE $DB_NAME;"

# Create a new user and grant privileges
mysql -u root -p$ROOT_PASS -e "CREATE USER '$DB_USER'@'localhost' IDENTIFIED BY '$DB_PASS';"
mysql -u root -p$ROOT_PASS -e "GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'localhost';"
mysql -u root -p$ROOT_PASS -e "FLUSH PRIVILEGES;"

# Create the tables in ip_tracker database
mysql -u $DB_USER -p$DB_PASS $DB_NAME <<EOF
CREATE TABLE device (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50),
    ip VARCHAR(50),
    mac VARCHAR(50) UNIQUE, 
    blocked BIT NOT NULL,
    remembered INT NOT NULL
);

CREATE TABLE admin (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(100),
    password VARCHAR(100),
    email VARCHAR(100)
);
EOF

echo "Database and tables created successfully."
