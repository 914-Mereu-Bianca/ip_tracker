USE ip_tracker;

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