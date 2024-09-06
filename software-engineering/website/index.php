<?php
session_start();

if (!isset($_SESSION['username'])) {
    header('location: login.php');
    exit();
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
                        <!-- Items on left side -->
                        <ul class="navbar-nav mr-auto">
                            <li class="nav-item">
                                <a class="nav-link" href="./request_history.php">Request History</a>
                            </li>
                        </ul>
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
                <form action="./php/database_crud.php" id="changeRequestHistory" method="POST">
                    <legend>Edit Request History</legend>
                    <div class="row mb-3">
                        <label for="Id" class="col-sm-2 col-form-label">Id</label>
                        <div class="col-sm-10">
                            <input type="text" class="form-control" id="Id" name="Id">
                        </div>
                    </div>
                    <div class="row mb-3" >
                        <label for="Method" class="col-sm-2 col-form-label">Method</label>
                        <div class="col-sm-10">
                            <select class="form-select" id="Method" name="Method">
                                <option selected>Select request method</option>
                                <option value="FloorOneController">Floor One Controller</option>
                                <option value="FloorTwoController">Floor Two Controller</option>
                                <option value="FloorThreeController">Floor Three Controller</option>
                                <option value="CarController">Car Controller</option>
                                <option value="Website">Website</option>
                                <option value="Voice">Voice</option>
                            </select>
                        </div>
                    </div>
                    <div class="row mb-3" >
                        <label for="Floor" class="col-sm-2 col-form-label">Floor</label>
                        <div class="col-sm-10">
                            <select class="form-select" id="Floor" name="Floor">
                                <option selected>Select floor number</option>
                                <option value="1">One</option>
                                <option value="2">Two</option>
                                <option value="3">Three</option>
                            </select>
                        </div>
                    </div>
                    <button type="submit" class="btn btn-primary" id="UPDATE" name="update">Update</button>
                    <button type="submit" class="btn btn-primary" id="INSERT" name="insert">Insert</button>
                    <button type="submit" class="btn btn-primary" id="DELETE" name="delete">Delete</button>
                </form>
            </div>
        </main>
        <footer>
        </footer>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
    </body>
</html>
