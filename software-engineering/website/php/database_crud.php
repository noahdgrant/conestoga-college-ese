<?php 
function connect(string $path, string $user, string $password) {
    try {
        $database = new PDO($path, $user, $password);
        $database->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    } catch (PDOException $e) {
        die("Database connect error: " . $e->getMessage());
    }

    return $database; 
}

// CRUD (Create, Read, Update, Delete) functions
// Create
function insert(string $path, string $user, string $password, string $method, int $floor) : void {
    $database = connect($path, $user, $password);

    $query = "INSERT INTO RequestHistory (Method, Floor) VALUES (:method, :floor)";
    $statement = $database->prepare($query);
    $statement->bindParam(":method", $method, PDO::PARAM_STR);
    $statement->bindParam(":floor", $floor, PDO::PARAM_INT);

    try {
        $result = $statement->execute(); 
    } catch (PDOException $e) {
        die("Database insert error: " . $e->getMessage());
    }
}

// Read
function show_request_history(string $path, string $user, string $password) : void {
    $database = connect($path, $user, $password); 

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

// Update
function update(string $path, string $user, string $password, int $id, string $method, int $floor) : void {
    $database = connect($path, $user, $password);

    $query = 'UPDATE RequestHistory SET Method = :method, Floor = :floor WHERE Id = :id';
    $statement = $database->prepare($query); 
    $statement->bindParam(":method", $method, PDO::PARAM_STR);
    $statement->bindParam(":floor", $floor, PDO::PARAM_INT);
    $statement->bindParam(":id", $id, PDO::PARAM_INT);

    try {
        $result = $statement->execute(); 
    } catch (PDOException $e) {
        die("Database update error: " . $e->getMessage());
    }
}

// Delete
function delete(string $path, string $user, string $password, string $table, int $id) : void {
    $database = connect($path, $user, $password);

    $query = 'DELETE FROM ' . $table . ' WHERE Id = :id'; // NOTE: risk of SQL injection
    $statement = $database->prepare($query); 
    $statement->bindParam(":id", $id, PDO::PARAM_INT);

    try {
        $result = $statement->execute(); 
    } catch (PDOException $e) {
        die("Database delete error: " . $e->getMessage());
    }
}

// Used to call function from javascript
if ($_GET["function"] == "show_request_history") {
    show_request_history("mysql:host=127.0.0.1;dbname=SoftwareEngineering", "noah", "noah");
}

// Used to update database
if(isset($_POST["update"])) {
    update("mysql:host=127.0.0.1;dbname=SoftwareEngineering", "noah", "noah",
           $_POST["Id"], $_POST["Method"], $_POST["Floor"]);
    header('location: ../request_history.php');
    exit();
} elseif (isset($_POST["insert"])) {
    insert("mysql:host=127.0.0.1;dbname=SoftwareEngineering", "noah", "noah",
           $_POST["Method"], $_POST["Floor"]);
    header('location: ../request_history.php');
    exit();
} elseif (isset($_POST["delete"])) {
    delete("mysql:host=127.0.0.1;dbname=SoftwareEngineering", "noah", "noah",
           "RequestHistory", $_POST["Id"]);
    header('location: ../request_history.php');
    exit();
} else {
    // Do nothing
}
?>
