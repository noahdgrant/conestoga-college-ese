<?php
session_start();

if (!isset($_SESSION['username'])) {
    header('location: login.php');
    exit();
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    require "./php/user.php";
    $user = new User($_SESSION["username"]);
    $user->insert_logbook_entry($_POST["entry"]);
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
        <title>Home</title>
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
                <?php
                if ($_SESSION["auth"] == "user") {
                    echo '<form id="logbook_entry" action="./index.php" method="POST">';
                    echo '<legend class="text-center pb-3 fs-3 fw-bold">Logbook</legend>';
                    echo '<div class="row mb-3">';
                    echo '<label for="entry" class="col-sm-2 col-form-label">New Entry:</label>';
                    echo '<div class="col-sm-10">';
                    echo '<input type="text" class="form-control" id="entry" name="entry" required>';
                    echo '</div>';
                    echo '</div>';
                    echo '<div class="text-end">';
                    echo '<button type="submit" class="btn btn-primary" id="submit">Add</button>';
                    echo '</div>';
                    echo '</form>';
                }
                echo "<h1> Logbook Entries </h1>";
                require_once "./php/guest.php";
                $guest = new Guest($_SESSION["username"]);
                $guest->get_logbook_entries();
               ?>
            </div>
        </main>
        <footer>
        </footer>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
    </body>
</html>
