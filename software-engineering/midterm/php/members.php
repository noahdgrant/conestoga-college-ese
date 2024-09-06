<?php
session_start();

if(!isset($_SESSION['username'])){
  header('location: authenticate.php');
}
?>

<!DOCTYPE html>
<html lang="en">
  <body>
    <div id="page" class="container">
      <div id="content">
        <p>Members only</p>
        <p>Exclusive content</p>
        <a href="logout.php">Logout</a></li>
      </div>
    </div>
  </body>
</html>
