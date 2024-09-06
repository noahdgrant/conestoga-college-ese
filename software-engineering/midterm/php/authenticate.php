<?php
session_start();
$file_path = '../json/users.json';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $contents = file_get_contents($file_path);
    $php_array=json_decode($contents, true);

    foreach ($php_array["users"] as $user) {
        if($user["username"] == $_GET["username"] && $user["password"] == $_GET["password"]) {
            $_SESSION["username"] = $user["username"];
            header("Location:members.php");
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
    <body>
        <div id="page" class="container">
            <div id="content">
                <p>You are not authorized</p>
                <a href="../login.html">Login</a></li>
            </div>
        </div>
    </body>
</html>
