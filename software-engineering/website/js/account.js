
'use strict'

const MIN_LENGTH = 7;

const forms = document.querySelectorAll('.needs-validation')
var password = document.getElementById("password");
var password_feedback = document.getElementById("passwordFeedback");

var new_password = document.getElementById("new_password");
var new_password_feedback = document.getElementById("newPasswordFeedback");

var verify_password = document.getElementById("verify_password");
var verify_password_feedback = document.getElementById("verifyPasswordFeedback");

new_password.addEventListener("keyup", validate_new_password, false);
verify_password.addEventListener("keyup", validate_verify_password, false);

// Loop over form and prevent submission
Array.from(forms).forEach(form => {
    form.addEventListener('submit', event => {
        let error = validate_new_password();
        error |= validate_verify_password();

        if (error == true) {
            event.preventDefault();
            event.stopPropagation();
        }

    }, false)
})

function password_error(password_attempt, new_password_attempt, verify_password_attempt) {
    password_feedback.innerHTML = "Wrong password.";
    password.value = password_attempt;
    password.classList.remove("is-valid");
    password.classList.add("is-invalid");

    new_password.value = new_password_attempt;
    verify_password.value = verify_password_attempt;

    validate_new_password();
    validate_verify_password();
}

function validate_new_password() {
    let error = false;
    let contains_num = false;

    new_password_feedback.innerHTML = "";

    if (new_password.value.length < MIN_LENGTH) {
        new_password_feedback.innerHTML += "Must be at least " + MIN_LENGTH + " characters long.<br>";
        error = true;
    }

    if (new_password.value === new_password.value.toLowerCase()) {
        new_password_feedback.innerHTML += "Must contain an uppercase letter.<br>";
        error = true;
    }

    for (let i = 0; i < new_password.value.length; i++) {
        let character = new_password.value.charAt(i)
        if (!isNaN(character * 1)) {
            contains_num = true;
            break;
        }
    }
    if (contains_num == false) {
        new_password_feedback.innerHTML += "Must contain a number.<br>";
        error = true;
    }

    if (new_password.value === password.value) {
        new_password_feedback.innerHTML += "New password matches old password<br>";
        error = true;
    }

    if (error == false) {
        new_password.classList.remove("is-invalid");
        new_password.classList.add("is-valid");
    } else {
        new_password.classList.remove("is-valid");
        new_password.classList.add("is-invalid");
    }

    return error;
}

function validate_verify_password() {
    let error = false;

    verify_password_feedback.innerHTML = "";
    
    if (verify_password.value !== new_password.value) {
        verify_password_feedback.innerHTML += "Doesn't match new password";
        error = true;
    }

    if (error) {
        verify_password.classList.remove("is-valid");
        verify_password.classList.add("is-invalid");
    } else {
        verify_password.classList.remove("is-invalid");
        verify_password.classList.add("is-valid");
    }

    return error;
}
