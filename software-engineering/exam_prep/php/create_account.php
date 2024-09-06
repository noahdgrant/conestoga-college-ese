<?php
session_start();

$database = new PDO("mysql:host=127.0.0.1;dbname=SoftwareEngineering", "noah", "noah");
$database->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

$hashed_password = password_hash($_POST["password"], PASSWORD_BCRYPT);

$query = "INSERT INTO User (Username, Password) VALUES (:username, :password)";
$statement = $database->prepare($query);
$statement->bindParam(":username", $_POST["username"], PDO::PARAM_STR);
$statement->bindParam(":password", $hashed_password, PDO::PARAM_STR);

try {
    $result = $statement->execute();
    if ($result) {
        $_SESSION["username"] = $_POST["username"];
        header("Location: ../index.php");
        exit();
    }
} catch (PDOException $e) {
    if ($e->errorInfo[1] == 1062) {
        // Error code 1062 corresponds to ER_DUP_ENTRY in MySQL, indicating a duplicate key error
        $_SESSION["signup_error"] = "username_exists";
        $_SESSION["username_attempt"] = $_POST["username"];
        $_SESSION["password_attempt"] = $_POST["password"];
        header("location: ../signup.php");
        exit();
    } else {
        $_SESSION["signup_error"] = "database_error";
        echo "Database error";
    }
}
?>
