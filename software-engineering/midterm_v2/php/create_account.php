<?php
session_start();
$file_path = "../json/users.json";

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if(!file_exists($file_path) || !is_writeable($file_path)){
        die("Error: User not added, database not accessible <br>");
    }

    $contents = file_get_contents($file_path);
    $php_array=json_decode($contents, true);

    $new_user = array(
        'username' => $_POST['username'],
        'password' => $_POST['password']
    );

    foreach ($php_array['users'] as $user) {
        if ($user['username'] === $new_user['username']) {
            die('Error: A user with the same ID already exists.');
        }
    }

    $php_array['users'][] = $new_user;

    $JSON_string = json_encode($php_array, JSON_PRETTY_PRINT);

    file_put_contents($file_path, $JSON_string);
}

header('location: ../login.php');
?>
