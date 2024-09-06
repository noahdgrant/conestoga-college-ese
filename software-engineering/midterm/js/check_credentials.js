const MIN_LENGTH = 7;

var form = document.getElementById("request_access");
var username = document.getElementById("username");
var password = document.getElementById("password");

form.addEventListener("submit", function(e) {validate_information(e);}, false);
username.addEventListener("blur", function(e) {validate_username(e);}, false);
password.addEventListener("blur", function(e) {validate_password(e);}, false);

function validate_username(e) {
    let error = false;
    let error_msg = "7 character minimum";
    document.getElementById("user_errror_msg").innerHTML ="";
    let contains_uppercase = false;
    let contains_num = false;

    // Check length
    if (username.value.length < MIN_LENGTH) {
        error = true;
    }

    // Print error
    if (error) {
        document.getElementById("user_errror_msg").innerHTML = error_msg;
        if(e.submitter.id == "submit"){
            e.preventDefault();
        }
    }
}

function validate_password(e) {
  let error = false;
  let error_msg = "";
  document.getElementById("pswd_errror_msg").innerHTML = "";
  let contains_num = false;

  // Check length
  if (password.value.length < MIN_LENGTH) {
    error = true;
    error_msg = "7 character minimum";
  } else {
    // Check uppercase
    if (password.value === password.value.toLowerCase()) {
      error_msg = "Password must have at least one uppercase letter and one number";
      error = true;
    }

    // Check number
    for (i = 0; i < password.value.length; i++) {
      character = password.value.charAt(i)
      if (!isNaN(character * 1)) {
        contains_num = true;
        break;
      }
    }
    if (contains_num == false) {
      error_msg = "Password must have at least one uppercase letter and one number";
      error = true;
    }
  }

  if (error) {
    document.getElementById("pswd_errror_msg").innerHTML = error_msg;
    if(e.submitter.id == "submit"){
      e.preventDefault();
    }
  }
}

function validate_information(e) {
    validate_username(e);
    validate_password(e);
}
