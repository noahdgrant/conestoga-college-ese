<?php
require_once "database.php";

class Guest {
    public $user;
    public $database;

    public function __construct(string $user) {
        $this->user = $user; 
        $path = "mysql:host=127.0.0.1;dbname=logbook";
        $username = "noah";
        $password = "noah";
        $this->database = new Database($path, $username, $password);
    }

    public function get_credentials() {
        try {
            $user = $this->database->get_user($this->user);
            echo "<p> ID: " . $user["Id"] . "</p>";
            echo "<p> Username: " . $user["Username"] . "</p>";
            echo "<p> Email: " . $user["Email"] . "</p>";
        } catch (PDOException $e) {
            die("error: " . $e->getMessage());
        }
    }

    public function get_logbook_entries() {
        try {
            $user= $this->database->get_user($this->user);
            $rows = $this->database->get_logbook_entries($user["Id"]);
            echo "<table class='table table-striped'>";
            echo "<thead>";
            echo "<tr>";
            echo "<th scope='col'>Id</th>";
            echo "<th scope='col'>Date</th>";
            echo "<th scope='col'>Time</th>";
            echo "<th scope='col'>Text</th>";
            echo "</tr>";
            echo "</thead>";
            echo "<tbody>";
            foreach ($rows as $row){
                echo "<tr>";
                echo "<th scope='row'>".$row["Id"]."</th>";
                echo "<td>".$row["Data"]."</td>";
                echo "<td>".$row["Time"]."</td>";
                echo "<td>".$row["Text"]."</td>";
                echo "</tr>";
            }
            echo "</tbody>";
            echo "</table>";
        } catch (PDOException $e) {
            die("error: " . $e->getMessage());
        }
    }
}
?>
