<?php
$db = new PDO (
    "mysql:host=127.0.0.1;dbname=elevator",
    "noah",
    "noah"
);

$db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

$query = "INSERT INTO elevatorNetwork
          (status, currentFloor, requestedFloor, otherInfo)
          VALUES (:status, :currentFloor, :requestedFloor, :otherInfo)";
$statement = $db->prepare($query);

$params = [
    "status" => 1,
    "currentFloor" => 1,
    "requestedFloor" => 1,
    "otherInfo" => "na"
];

$result = $statement->execute($params);

$rows = $db->query("SELECT * FROM elevatorNetwork");
foreach($rows as $row) {
    var_dump($row);
    echo "<br/><br/>";
}
?>
