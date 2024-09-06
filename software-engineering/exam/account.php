<?php
session_start();

if (!isset($_SESSION['username'])) {
    header('location: login.php');
    exit();
}

if (isset($_SESSION["password_updated"])) {
    echo '<script type="text/javascript">';
    echo 'document.addEventListener("DOMContentLoaded", function() {';
    echo 'alert("Password updated");';
    echo '});';
    echo '</script>';

    unset($_SESSION["password_updated"]);
}

if (isset($_SESSION["account_error"])) {
    echo '<script type="text/javascript">';
    echo 'document.addEventListener("DOMContentLoaded", function() {';
    echo 'password_error(' . json_encode($_SESSION["password_attempt"]) . ',' . json_encode($_SESSION["new_password_attempt"]) . ',' . json_encode($_SESSION["verify_password_attempt"]) .');';
    echo '});';
    echo '</script>';

    unset($_SESSION["account_error"]);
    unset($_SESSION["password_attempt"]);
    unset($_SESSION["new_password_attempt"]);
    unset($_SESSION["verify_password_attempt"]);
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    require "./php/user.php";
    $user = new User($_SESSION["username"]);
    $user->set_email($_POST["email"]);
}
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta name="author" content="Noah Grant">
        <meta name="description" content="Midterm">
        <meta name="robots" content="noindex">
        <meta http-equiz="pragma" content="no-cache">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
        <link href='css/style.css' rel='stylesheet'>
        <title>Account</title>
    </head>
    <body>
        <header>
            <nav class="navbar navbar-expand-lg bg-dark border-bottom border-body" data-bs-theme="dark">
                <div class="container-fluid">
                    <a class="navbar-brand" href="./index.php">Project Website</a>
                    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                        <span class="navbar-toggler-icon"></span>
                    </button>
                    <div class="collapse navbar-collapse" id="navbarNav">
                        <!-- Items on right side -->
                        <ul class="navbar-nav ms-auto">
                            <li class="nav-item">
                                <a class="nav-link" href="./account.php">Account</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link" href="./php/logout.php">Log Out</a>
                            </li>
                        </ul>
                    </div>
                </div>
            </nav>
        </header>
        <main id="page" class="container">
            <div class="w-50 position-absolute top-50 start-50 translate-middle">
                <div>
                    <h1>Profile</h1>
                    <?php
                    if ($_SESSION["auth"] == "user") {
                        require_once "./php/user.php";
                        $user = new User($_SESSION["username"]);
                        $user->get_credentials();
                        $user->get_password();
                    } else {
                        require "./php/guest.php";
                        $guest = new Guest($_SESSION["username"]);
                        $guest->get_credentials();
                    }
                    ?>
                </div>
                <?php
                if ($_SESSION["auth"] == "user") {
                echo '<h1>Account Settings</h1>';
                echo '<form class="needs-validation" id="change_password" action="./php/update_account.php" method="POST">';
                echo '<legend>Change Password</legend>';
                echo '<div class="row mb-3" >';
                echo '<label for="password" class="col-sm-3 col-form-label">Old Password</label>';
                echo '<div class="col-sm-9">';
                echo '<input type="password" class="form-control" id="password" name="password" required>';
                echo '<div class="invalid-feedback" id="passwordFeedback">';
                echo '</div>';
                echo '</div>';
                echo '</div>';
                echo '<div class="row mb-3" >';
                echo '<label for="new_password" class="col-sm-3 col-form-label">New Password</label>';
                echo '<div class="col-sm-9">';
                echo '<input type="password" class="form-control" id="new_password" name="new_password" required>';
                echo '<div class="invalid-feedback" id="newPasswordFeedback">';
                echo '</div>';
                echo '</div>';
                echo '</div>';
                echo '<div class="row mb-3" >';
                echo '<label for="verify_password" class="col-sm-3 col-form-label">Verify Password</label>';
                echo '<div class="col-sm-9">';
                echo '<input type="password" class="form-control" id="verify_password" name="verify_password" required>';
                echo '<div class="invalid-feedback" id="verifyPasswordFeedback">';
                echo '</div>';
                echo '</div>';
                echo '</div>';
                echo '<div class="text-end">';
                echo '<button type="submit" class="btn btn-primary" id="change_password_btn">Update</button>';
                echo '</div>';
                echo '</form>';
                echo '<form id="SetEmail" action="./account.php" method="POST">';
                echo '<legend>Update Email</legend>';
                echo '<div class="row mb-3" >';
                echo '<label for="email" class="col-sm-3 col-form-label">New Email</label>';
                echo '<div class="col-sm-9">';
                echo '<input type="email" class="form-control" id="email" name="email" required>';
                echo '</div>';
                echo '</div>';
                echo '<div class="text-end">';
                echo '<button type="submit" class="btn btn-primary" id="change_email_btn">Update</button>';
                echo '</div>';
                echo '</form>';
                }
                ?>
            </div>
        </main>
        <footer>
        </footer>
        <script src="./js/account.js"></script>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
    </body>
</html>
