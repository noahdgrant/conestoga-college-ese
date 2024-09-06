<?php
session_start();

$database = new PDO("mysql:host=127.0.0.1;dbname=SoftwareEngineering", "noah", "noah");
$database->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

// Check that old password is correct before updating the password
$query = "SELECT Password FROM User WHERE Username = :username";
$statement = $database->prepare($query);
$statement->bindParam(":username", $_SESSION["username"], PDO::PARAM_STR);

try {
    $result = $statement->execute();

    $user = $statement->fetch(PDO::FETCH_ASSOC);
    if (!password_verify($_POST["password"], $user["Password"])){
        $_SESSION["account_error"] = "wrong_password";
        $_SESSION["password_attempt"] = $_POST["password"];
        $_SESSION["new_password_attempt"] = $_POST["new_password"];
        $_SESSION["verify_password_attempt"] = $_POST["verify_password"];
        header("location: ../account.php");
        exit();
    }
} catch (PDOException $e) {
    echo "Database error";
}

// Update password
$hashed_password = password_hash($_POST["new_password"], PASSWORD_BCRYPT);

$query = "UPDATE User SET Password = :password WHERE Username = :username";
$statement = $database->prepare($query);
$statement->bindParam(":username", $_SESSION["username"], PDO::PARAM_STR);
$statement->bindParam(":password", $hashed_password, PDO::PARAM_STR);

try {
    $result = $statement->execute();
    if ($result) {
        $_SESSION["password_updated"] = TRUE;
        header("Location: ../account.php");
        exit();
    } else {
        echo "Query error";
    }
} catch (PDOException $e) {
    echo "Database error";
}
?>
