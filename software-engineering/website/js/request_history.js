fetch("../php/database_crud.php?function=show_request_history")
    .then(response => response.text())
    .then(data => {
        document.getElementById("tableContainer").innerHTML = data;
    });
