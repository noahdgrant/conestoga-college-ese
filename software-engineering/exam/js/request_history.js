fetch("../php/database.php?function=get_request_history")
    .then(response => response.text())
    .then(data => {
        document.getElementById("tableContainer").innerHTML = data;
    });
