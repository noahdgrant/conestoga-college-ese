'use strict'

var username = document.getElementById("username");
var username_feedback = document.getElementById("usernameFeedback");
var password = document.getElementById("password");
var password_feedback = document.getElementById("passwordFeedback");

function username_error(username_attempt, password_attempt) {
    username_feedback.innerHTML = "Username does not exist.";
    username.value = username_attempt;
    username.classList.remove("is-valid");
    username.classList.add("is-invalid");

    password.value = password_attempt;
}

function password_error(username_attempt, password_attempt) {
    password_feedback.innerHTML = "Wrong password.";
    password.value = password_attempt;
    password.classList.remove("is-valid");
    password.classList.add("is-invalid");

    // We know the username is valid if this function runs
    username.value = username_attempt;
    username.classList.remove("is-invalid");
    username.classList.add("is-valid");
}
