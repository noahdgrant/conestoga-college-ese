<?php
session_start();
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
        <title>Login</title>
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
                <form class="needs-validation" id="login" action="./php/sign_in.php" method="get">
                    <fieldset>
                        <legend>Log In</legend>
                        <div class="mb-3">
                            <label for="username" class="form-label">Username</label>
                            <input type="text" class="form-control" id="username" name="username" required>
                            <div class="invalid-feedback" id="usernameFeedback">
                            </div>
                        </div>
                        <div class="mb-5" >
                            <label for="password" class="form-label">Password</label>
                            <input type="password" class="form-control" id="password" name="password" required>
                            <div class="invalid-feedback" id="passwordFeedback">
                            </div>
                        </div>
                        <button type="submit" class="btn btn-primary position-absolute bottom-0 end-0" id="login_btn">Log In</button>
                    </fieldset>
                </form>
            </div>
        </main>
        <footer>
        </footer>
        <script src="./js/login.js"></script>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
    </body>
</html>
