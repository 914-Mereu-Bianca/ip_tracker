
-- Ensure the user exists
CREATE USER IF NOT EXISTS 'bia'@'%' IDENTIFIED BY 'root';

-- Alter the user to use mysql_native_password authentication
ALTER USER 'bia'@'%' IDENTIFIED WITH mysql_native_password BY 'root';

-- Flush privileges to apply changes
FLUSH PRIVILEGES;

INSERT INTO admin (id, username, password)
SELECT 1, '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918', '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918'
WHERE NOT EXISTS (SELECT 1 FROM admin WHERE id = 1);