<?php
session_start();
?>

<!DOCTYPE html>
<html lang="en">
  <body>
    <div id="page" class="container">
      <div id="content">
        <a href="../login.html">Login</a></li>
      </div>
    </div>
  </body>
</html>

<?php
session_unset();
session_destroy();
?>
