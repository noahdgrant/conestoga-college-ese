<?php
session_start();

function connect(string $path, string $user, string $password) {
    try {
        $database = new PDO($path, $user, $password);
        $database->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    } catch (PDOException $e) {
        die("Database connect error: " . $e->getMessage());
    }

    return $database; 
}

function update(string $path, string $user, string $password, int $floorNumber) : void {
    $database = connect($path, $user, $password);

    $query = 'UPDATE carNode SET floorNumber = :floorNumber';
    $statement = $database->prepare($query); 
    $statement->bindParam(":floorNumber", $floorNumber, PDO::PARAM_INT);

    try {
        $result = $statement->execute(); 
    } catch (PDOException $e) {
        die("Database update error: " . $e->getMessage());
    }
}

function show(string $path, string $user, string $password) : void {
    $database = connect($path, $user, $password); 

    $query = "SELECT elevatorNodes.nodeID, elevatorNodes.info, elevatorNodes.status, carNode.floorNumber FROM elevatorNodes LEFT JOIN carNode ON elevatorNodes.nodeID = carNode.nodeID";

    try {
        $rows = $database->query($query);

        echo "<table class='table table-striped'>";
        echo "<thead>";
        echo "<tr>";
        echo "<th scope='col'>Node Id</th>";
        echo "<th scope='col'>Info</th>";
        echo "<th scope='col'>Status</th>";
        echo "<th scope='col'>Floor Number</th>";
        echo "</tr>";
        echo "</thead>";
        echo "<tbody>";
        foreach ($rows as $row){
            echo "<tr>";
            echo "<td>".$row["nodeID"]."</th>";
            echo "<td>".$row["info"]."</td>";
            echo "<td>".$row["status"]."</td>";
            echo "<td>".$row["floorNumber"]."</td>";
            echo "</tr>";
        }
        echo "</tbody>";
        echo "</table>";

    } catch (PDOException $e) {
        die("Database request error: " . $e->getMessage());
    }
}

if(isset($_POST["changeFloor"])) {
    update("mysql:host=127.0.0.1;dbname=quizElevator", "noah", "noah", $_POST["floorNumber"]);
}

?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta name="author" content="Noah Grant">
        <meta name="description" content="Quiz2">
        <meta name="robots" content="noindex">
        <meta http-equiz="pragma" content="no-cache">
        <title>Home</title>
    </head>
    <body>
        <header>
        </header>
        <main>
            <h1>Welcome to the Members Only Page</h1>
            <form method="POST">
                <label for="floorNumber">Enter a floor number to send the elevator to</label>
                <input type="number" id="floorNumber" name="floorNumber"/>
                <input type="submit" name="changeFloor"/>
            </form>
            <h2>Database Contents</h2>
            <?php show("mysql:host=127.0.0.1;dbname=quizElevator", "noah", "noah"); ?>
            <?php 
            echo "<h2>The car is now on floor: ";
            echo $_POST["floorNumber"];
            echo "</h2>";
            ?>
        </main>
        <footer>
        </footer>
    </body>
</html>
