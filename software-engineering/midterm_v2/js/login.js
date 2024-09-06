'use strict'

const DATABASE_URL = "http://localhost/json/users.json";

const forms = document.querySelectorAll('.needs-validation')
var username = document.getElementById("username");
var username_feedback = document.getElementById("usernameFeedback");
var password = document.getElementById("password");
var password_feedback = document.getElementById("passwordFeedback");

// Loop over form and prevent submission
Array.from(forms).forEach(form => {
    form.addEventListener('submit', async event => {
        let login_error = true;

        event.preventDefault();
        login_error = await validate_login();

        if (login_error == true) {
            event.stopPropagation();
        } else {
            form.submit();
        }

    }, false)
})

async function validate_login() {
    let login_error = false;

    try {
        const response = await fetch(DATABASE_URL);
        const data = await response.json();
        const users = data.users;

        // Check if username exists
        const user = users.find(user => user.username === username.value);
        if (user) {
            username.classList.remove("is-invalid");
            username.classList.add("is-valid");

            login_error = validate_password(user.password);
        } else {
            username.classList.remove("is-valid");
            username.classList.add("is-invalid");

            username_feedback.innerHTML = "Username does not exist.";
            login_error = true;
        }
    } catch (error) {
        console.error('Error:', error);
        login_error = true;
    }

    return login_error;
}

function validate_password(user_password) {
    let error = false;

    if (user_password === password.value) {
        error = false;
    } else {
        password_feedback.innerHTML = "Wrong password.";
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
