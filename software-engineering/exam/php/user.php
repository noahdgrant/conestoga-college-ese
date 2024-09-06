<?php
require_once "guest.php";

class User extends Guest {
    public function get_password() {
        try {
            $password = $this->database->get_password($this->user);
            echo "<p> Password: " . $password["Password"] . "</p>";
        } catch (PDOException $e) {
            die("error: " . $e->getMessage());
        }
    }

    public function set_email(string $email) {
        try {
            $this->database->set_email($this->user, $email);
        } catch (PDOException $e) {
            die("error: " . $e->getMessage());
        }
    }

    public function set_password(string $password) {
        try {
            $hashed_password = password_hash($password, PASSWORD_BCRYPT);
            $credentials = $this->database->set_password($this->user, $hashed_password);
        } catch (PDOException $e) {
            die("error: " . $e->getMessage());
        }
    }

    public function insert_logbook_entry(string $entry) {
        try {
            $user = $this->database->get_user($this->user);
            $this->database->insert_logbook_entry($user["Id"], $entry);
        } catch (PDOException $e) {
            die("error: " . $e->getMessage());
        }

    }
}
?>
