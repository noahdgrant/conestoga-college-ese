<?php
session_start();

$database = new PDO("mysql:host=127.0.0.1;dbname=SoftwareEngineering", "noah", "noah");
$database->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

$query = "SELECT Password FROM User WHERE Username = :username";
$statement = $database->prepare($query);
$statement->bindParam(":username", $_POST["username"], PDO::PARAM_STR);

try {
    $result = $statement->execute();

    $user = $statement->fetch(PDO::FETCH_ASSOC);
    if ($user === false) {
        // The query didn't return any rows
        $_SESSION["login_error"] = "username";
        $_SESSION["username_attempt"] = $_POST["username"];
        $_SESSION["password_attempt"] = $_POST["password"];
        header("location: ../login.php");
        exit();
    }

    if (password_verify($_POST["password"], $user["Password"])){
        // Start session
        $_SESSION["username"] = $_POST["username"];
        header("location: ../index.php");
        exit();
    } else {
        session_unset();
        // If we get to here we know the username exists so the password must not match
        $_SESSION["login_error"] = "password";
        $_SESSION["username_attempt"] = $_POST["username"];
        $_SESSION["password_attempt"] = $_POST["password"];
        header("location: ../login.php");
        exit();
    }
} catch (PDOException $e) {
    echo "Database login error";
}
?>
