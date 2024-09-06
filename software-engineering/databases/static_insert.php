<?php
$db = new PDO (
    "mysql:host=127.0.0.1;dbname=elevator",
    "noah",
    "noah"
);

$db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

$query = "INSERT INTO elevatorNetwork
          (status, currentFloor, requestedFloor, otherInfo)
          VALUES (1, 1, 1, 'na')";
$result = $db->exec($query);

if($result === false) {
    $error = $db->errorInfo();
    echo "Error: " . $error[2];
} else {
    var_dump($result);
    echo "<br/><br/>";
}

$rows = $db->query("SELECT * FROM elevatorNetwork");
foreach($rows as $row) {
    var_dump($row);
    echo "<br/><br/>";
}
?>
