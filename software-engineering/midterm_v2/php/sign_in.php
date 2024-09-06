<?php
session_start();

$file_path = "../json/users.json";

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $contents = file_get_contents($file_path);
    $php_array=json_decode($contents, true);

    foreach ($php_array["users"] as $user) {
        if($user["username"] == $_GET["username"] && $user["password"] == $_GET["password"]) {
            $_SESSION["username"] = $user["username"];
        }
    }
}

header('location: ../index.php');
?>
