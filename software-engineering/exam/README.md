# Software Engineering Final Exam

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

To create the Credentials table...

```mysql
mysql> CREATE TABLE Credentials(
Id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
Username VARCHAR(128) NOT NULL UNIQUE KEY,
Password VARCHAR(256) NOT NULL,
Email VARCHAR(128) NOT NULL
) ENGINE=InnoDB;
```

Add entries to the Credentials table...

```mysql
mysql> INSERT INTO Credentials(Username, Password, Email) VALUES ("<username>", "<password>", "<email>");
```

To create the LogbookEntries table...

```mysql
mysql> CREATE TABLE LogbookEntries(
Id INT UNSIGNED NOT NULL, 
Date DATE NOT NULL DEFAULT (CURRENT_DATE()), 
Time TIME NOT NULL DEFAULT (CURRENT_TIME()), 
Text TEXT NOT NULL
) ENGINE=InnoDB;
```

Add entries to the LogbookEntries table...

```mysql
mysql> INSERT INTO LogbookEntries(Text) VALUES ("<text>");
```
