
-- Ensure the user exists
CREATE USER IF NOT EXISTS 'bia'@'%' IDENTIFIED BY 'root';

-- Alter the user to use mysql_native_password authentication
ALTER USER 'bia'@'%' IDENTIFIED WITH mysql_native_password BY 'root';

-- Flush privileges to apply changes
FLUSH PRIVILEGES;
