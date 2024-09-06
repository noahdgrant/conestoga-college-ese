<?php
session_start();

if (isset($_SESSION["signup_error"])) {
    // This is so that I can update the bootstrap for fancier error messages
    echo '<script type="text/javascript">';
    echo 'document.addEventListener("DOMContentLoaded", function() {';
    echo 'username_error(' . json_encode($_SESSION["username_attempt"]) . ',' . json_encode($_SESSION["password_attempt"]) . ');';
    echo '});';
    echo '</script>';

    unset($_SESSION["signup_error"]);
    unset($_SESSION["username_attempt"]);
    unset($_SESSION["password_attempt"]);
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
        <title>Sign Up</title>
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
                        <ul class="navbar-nav ms-auto">
                            <li class="nav-item">
                                <a class="nav-link" aria-current="page" href="./signup.php">Sign Up</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link" href="./login.php">Log In</a>
                            </li>
                        </ul>
                    </div>
                </div>
            </nav>
        </header>
        <main id="page" class="container">
            <div class="w-50 position-absolute top-50 start-50 translate-middle">
                <form class="needs-validation" id="signup" action="./php/create_account.php" method="POST" novalidate>
                    <legend class="text-center pb-3 fs-3 fw-bold">Sign Up</legend>
                    <div class="row mb-3">
                        <label for="username" class="col-sm-2 col-form-label">Username</label>
                        <div class="col-sm-10">
                            <input type="text" class="form-control" id="username" name="username" required>
                            <div class="invalid-feedback" id="usernameFeedback">
                            </div>
                        </div>
                    </div>
                    <div class="row mb-3" >
                        <label for="password" class="col-sm-2 col-form-label">Password</label>
                        <div class="col-sm-10">
                            <input type="password" class="form-control" id="password" name="password" required>
                            <div class="invalid-feedback" id="passwordFeedback">
                            </div>
                        </div>
                    </div>
                    <div class="text-end">
                        <button type="submit" class="btn btn-primary" id="submit">Add me</button>
                    </div>
                </form>
                <p class="mt-3 position-absolute start-50 translate-middle warning">Username and password must be at least 7 characters</p>
            </div>
        </main>
        <footer>
        </footer>
        <script src="./js/signup.js"></script>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
    </body>
</html>
