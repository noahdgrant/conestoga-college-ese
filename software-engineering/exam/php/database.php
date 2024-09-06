<?php 
session_start();

class Database {
    private $path;
    private $user;
    private $password;

    public function __construct(string $path, string $user, string $password) {
       $this->path = $path; 
       $this->user = $user; 
       $this->password = $password; 
    }

    public function get_user(string $username) {
        $database = $this->connect(); 

        $query = 'SELECT Id, Username, Email FROM Credentials WHERE Username = :user';
        $statement = $database->prepare($query);
        $statement->bindParam(":user", $username, PDO::PARAM_STR);

        try {
            $statement->execute(); 
            $row = $statement->fetch(PDO::FETCH_ASSOC);
        } catch (PDOException $e) {
            die("Database request error: " . $e->getMessage());
        }

        return $row;
    }

    public function get_users() : void {
        $database = $this->connect(); 

        $query = "SELECT * FROM Credentials ORDER BY Username";

        try {
            $rows = $database->query($query);
            foreach ($rows as $row){
                echo "<p>" . $row['Username'] . "</p>";
            }
        } catch (PDOException $e) {
            die("Database request error: " . $e->getMessage());
        }
    }

    public function get_password(string $username) {
        $database = $this->connect(); 

        $query = 'SELECT Password FROM Credentials WHERE Username = :user';
        $statement = $database->prepare($query);
        $statement->bindParam(":user", $username, PDO::PARAM_STR);

        try {
            $statement->execute(); 
            $row = $statement->fetch(PDO::FETCH_ASSOC);
        } catch (PDOException $e) {
            die("Database request error: " . $e->getMessage());
        }

        return $row;
    }

    public function get_logbook_entries(int $user_id) {
        $database = $this->connect(); 

        $query = "SELECT * FROM LogbookEntries WHERE Id = " . $user_id;
        try {

            $rows = $database->query($query);
        } catch (PDOException $e) {
            die("Database request error: " . $e->getMessage());
        }

        return $rows;
    }

    public function insert_logbook_entry(int $user_id, string $entry) {
        $database = $this->connect();

        $query = "INSERT INTO LogbookEntries (Id, Text) VALUES (:id, :text)";
        $statement = $database->prepare($query); 
        $statement->bindParam(":id", $user_id, PDO::PARAM_STR);
        $statement->bindParam(":text", $entry, PDO::PARAM_STR);

        try {
            $statement->execute(); 
        } catch (PDOException $e) {
            die("Database insert error: " . $e->getMessage());
        }

    }

    public function set_email(string $username, string $email) : void {
        $database = $this->connect();

        $query = 'UPDATE Credentials SET Email = :email WHERE Username = :username';
        $statement = $database->prepare($query); 
        $statement->bindParam(":email", $email, PDO::PARAM_STR);
        $statement->bindParam(":username", $username, PDO::PARAM_STR);

        try {
            $statement->execute(); 
        } catch (PDOException $e) {
            die("Database update error: " . $e->getMessage());
        }
    }

    public function set_password(string $username, string $password) : void {
        $database = $this->connect();

        $query = 'UPDATE Credentials SET Password = :password WHERE Username = :username';
        $statement = $database->prepare($query); 
        $statement->bindParam(":password", $password, PDO::PARAM_STR);
        $statement->bindParam(":username", $username, PDO::PARAM_STR);

        try {
            $statement->execute(); 
        } catch (PDOException $e) {
            die("Database update error: " . $e->getMessage());
        }
    }

    private function connect() {
        try {
            $database = new PDO($this->path, $this->user, $this->password);
            $database->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
        } catch (PDOException $e) {
            die("Database connect error: " . $e->getMessage());
        }

        return $database; 
    }
}

//$database_name = "logbook";
//$path = "mysql:host=127.0.0.1;dbname=" . $database_name;
//$username = "noah";
//$password = "noah";
//$database = new Database($path, $username, $password);
//
//if (isset($_POST["SetEmail"])) {
//    $database->set_email($_SESSION["username"], $_POST["email"]);
//    header('location: ../account.php');
//    exit();
//}
?>
