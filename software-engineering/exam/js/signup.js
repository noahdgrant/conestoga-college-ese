'use strict'

const MIN_LENGTH = 7;

const forms = document.querySelectorAll('.needs-validation')
var username = document.getElementById("username");
var username_feedback = document.getElementById("usernameFeedback");
var password = document.getElementById("password");
var password_feedback = document.getElementById("passwordFeedback");
var email = document.getElementById("email");
var email_feedback = document.getElementById("emailFeedback");

username.addEventListener("keyup", validate_username, false);
password.addEventListener("keyup", validate_password, false);

// Loop over form and prevent submission
Array.from(forms).forEach(form => {
    form.addEventListener('submit', event => {
        let error = validate_username();
        error |= validate_password();

        if (error == true) {
            event.preventDefault();
            event.stopPropagation();
        }

    }, false)
})

function username_error(username_attempt, password_attempt, email_attempt) {
    username_feedback.innerHTML = "Username already exists";
    username.value = username_attempt;
    username.classList.remove("is-valid");
    username.classList.add("is-invalid");

    password.value = password_attempt;
    password.classList.remove("is-invalid");
    password.classList.add("is-valid");

    email.value = email_attempt;
}

function validate_username() {
    let error = false;

    username_feedback.innerHTML = "";

    if (username.value.length < MIN_LENGTH) {
        username_feedback.innerHTML += "Must be at least 7 characters long.";
        error = true;
    }

    if (error == false) {
        username.classList.remove("is-invalid");
        username.classList.add("is-valid");
    } else {
        username.classList.remove("is-valid");
        username.classList.add("is-invalid");
    }

    return error;
}

function validate_password() {
    let error = false;
    let contains_num = false;

    password_feedback.innerHTML = "";

    if (password.value.length < MIN_LENGTH) {
        password_feedback.innerHTML += "Must be at least " + MIN_LENGTH + " characters long.<br>";
        error = true;
    }

    if (password.value === password.value.toLowerCase()) {
        password_feedback.innerHTML += "Must contain an uppercase letter.<br>";
        error = true;
    }

    for (let i = 0; i < password.value.length; i++) {
        let character = password.value.charAt(i)
        if (!isNaN(character * 1)) {
            contains_num = true;
            break;
        }
    }
    if (contains_num == false) {
        password_feedback.innerHTML += "Must contain a number.<br>";
        error = true;
    }

    if (error == false) {
        password.classList.remove("is-invalid");
        password.classList.add("is-valid");
    } else {
        password.classList.remove("is-valid");
        password.classList.add("is-invalid");
    }

    return error;
}
