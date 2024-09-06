# Software Engineering Mock Site

## Setup

If using a json file for the database, make sure to update the file permissions
so that the frontend can update the file.

```bash
$ sudo chmod 777 users.json
```

## mySQL

Log into mySQL with the following command...

```bash
$ mysql -u <username> -p
```

Some helpful mySQL commands...

```mysql
mysql> SHOW DATABASES;
mysql> CREATE DATABASE <database>;
mysql> USE <database>;
mysql> SHOW TABLES;
mysql> DESCRIBE <table>;
mysql> SELECT * from <table>;
```

To create the User table for this course...

```mysql
mysql> CREATE TABLE User(
Id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
Username VARCHAR(128) NOT NULL UNIQUE KEY,
Password VARCHAR(256) NOT NULL
) ENGINE=InnoDB;
```

To create the Request History table for this course...

```mysql
mysql> CREATE TABLE RequestHistory(
Id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY, 
Date DATE NOT NULL DEFAULT (CURRENT_DATE()), 
Time TIME NOT NULL DEFAULT (CURRENT_TIME()) UNIQUE, 
Method VARCHAR(255) NOT NULL, 
CONSTRAINT check_Method CHECK (Method IN ("FloorOneController", "FloorTwoController", "FloorThreeController", "CarController", "Website", "Voice")), 
Floor TINYINT UNSIGNED NOT NULL, 
CONSTRAINT check_Floor_RH CHECK (Floor IN (1,2,3))
) ENGINE=InnoDB;
```

Add entries to Request History table...

```mysql
mysql> INSERT INTO RequestHistory(Method, Floor) VALUES ("<method>", "<floor>");
```

To create the Floor History table for this course...

```mysql
mysql> CREATE TABLE FloorHistory(
Id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
Date DATE NOT NULL DEFAULT (CURRENT_DATE()),
Time TIME NOT NULL DEFAULT (CURRENT_TIME()) UNIQUE,
Floor TINYINT UNSIGNED NOT NULL,
CONSTRAINT check_Floor CHECK (Floor IN (1,2,3))
) ENGINE=InnoDB;
```
