<?php
$db = new PDO (
    "mysql:host=127.0.0.1;dbname=elevator",
    "noah",
    "noah"
);

$db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

$query = "SELECT * FROM elevatorNetwork WHERE nodeID = :nodeID";
$statement = $db->prepare($query);
$statement->bindValue("nodeID", 1);
$result = $statement->execute();
$rows = $statement->fetchAll();

foreach($rows as $row) {
    var_dump($row);
    echo "<br/><br/>";
}
?>
