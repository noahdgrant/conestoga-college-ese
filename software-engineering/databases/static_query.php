<?php
$db = new PDO (
    "mysql:host=127.0.0.1;dbname=elevator",
    "noah", // Username
    "noah"  // Password
);

$db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

$rows = $db->query("SELECT * FROM elevatorNetwork ORDER BY nodeID");
foreach($rows as $row) {
    var_dump($row);
    echo "<br/><br/>";
}
?>
