<?php 
class Database {
    private $path;
    private $user;
    private $password;

    public function __construct(string $path, string $user, string $password) {
       $this->path = $path; 
       $this->user = $user; 
       $this->password = $password; 
    }

    public function insert(string $method, int $floor) : void {
        $database = $this->connect();

        $query = "INSERT INTO RequestHistory (Method, Floor) VALUES (:method, :floor)";
        $statement = $database->prepare($query);
        $statement->bindParam(":method", $method, PDO::PARAM_STR);
        $statement->bindParam(":floor", $floor, PDO::PARAM_INT);

        try {
            $statement->execute(); 
        } catch (PDOException $e) {
            die("Database insert error: " . $e->getMessage());
        }
    }

    public function get_request_history() : void {
        $database = $this->connect(); 

        $query = "SELECT * FROM RequestHistory ORDER BY Id";

        try {
            $rows = $database->query($query);

            echo "<table class='table table-striped'>";
            echo "<thead>";
            echo "<tr>";
            echo "<th scope='col'>Id</th>";
            echo "<th scope='col'>Method</th>";
            echo "<th scope='col'>Floor</th>";
            echo "<th scope='col'>Date</th>";
            echo "<th scope='col'>Time</th>";
            echo "</tr>";
            echo "</thead>";
            echo "<tbody>";
            foreach ($rows as $row){
                echo "<tr>";
                echo "<th scope='row'>".$row["Id"]."</th>";
                echo "<td>".$row["Method"]."</td>";
                echo "<td>".$row["Floor"]."</td>";
                echo "<td>".$row["Date"]."</td>";
                echo "<td>".$row["Time"]."</td>";
                echo "</tr>";
            }
            echo "</tbody>";
            echo "</table>";

        } catch (PDOException $e) {
            die("Database request error: " . $e->getMessage());
        }
    }

    public function update(int $id, string $method, int $floor) : void {
        $database = $this->connect();

        $query = 'UPDATE RequestHistory SET Method = :method, Floor = :floor WHERE Id = :id';
        $statement = $database->prepare($query); 
        $statement->bindParam(":method", $method, PDO::PARAM_STR);
        $statement->bindParam(":floor", $floor, PDO::PARAM_INT);
        $statement->bindParam(":id", $id, PDO::PARAM_INT);

        try {
            $statement->execute(); 
        } catch (PDOException $e) {
            die("Database update error: " . $e->getMessage());
        }
    }

    public function delete(string $table, int $id) : void {
        $database = $this->connect();

        $query = 'DELETE FROM ' . $table . ' WHERE Id = :id'; // NOTE: risk of SQL injection
        $statement = $database->prepare($query); 
        $statement->bindParam(":id", $id, PDO::PARAM_INT);

        try {
            $statement->execute(); 
        } catch (PDOException $e) {
            die("Database delete error: " . $e->getMessage());
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

$database_name = "SoftwareEngineering";
$path = "mysql:host=127.0.0.1;dbname=" . $database_name;
$username = "noah";
$password = "noah";
$database = new Database($path, $username, $password);

// Used to call function from javascript
if ($_GET["function"] == "get_request_history") {
    $database->get_request_history();
}

// Used to update database
if (isset($_POST["update"])) {
    $database->update($_POST["Id"], $_POST["Method"], $_POST["Floor"]);
    header('location: ../request_history.php');
    exit();
} elseif (isset($_POST["insert"])) {
    $database->insert($_POST["Method"], $_POST["Floor"]);
    header('location: ../request_history.php');
    exit();
} elseif (isset($_POST["delete"])) {
    $database->delete("RequestHistory", $_POST["Id"]);
    header('location: ../request_history.php');
    exit();
} else {
    // Do nothing
}
?>
