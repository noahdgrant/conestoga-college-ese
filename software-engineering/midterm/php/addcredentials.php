<?php
session_start();
$file_path = '../json/users.json';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $contents = file_get_contents($file_path);
    $php_array=json_decode($contents, true);
    foreach($php_array['users'] as $user){
        echo "User: " . $user["name"] . ", ID: " . $user["id"] . "<br>";
    }
}


if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if(!file_exists($file_path) || !is_writeable("../json/users.json")){
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
?>

<!DOCTYPE html>
<html lang="en">
    <body>
        <div id="page" class="container">
            <div id="content">
                <p>Account created</p>
                <a href="../login.html">Login</a></li>
            </div>
        </div>
    </body>
</html>

