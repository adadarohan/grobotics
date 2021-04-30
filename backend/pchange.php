<?php  
	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "gro";
	$id = $_GET['id'];
	$plant = $_GET['p'];

	//Sample GET request - localhost/gro/pchange.php?id=1&p='cotton'
	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
	    die("Connection failed: " . $conn->connect_error);
	}

	$sql = "DELETE FROM idp WHERE id=" . $id;

	if ($conn->query($sql) === TRUE) {
	    echo "Record deleted successfully";
	} else {
	    echo "Error deleting record: " . $conn->error;
	}

	$sql = "INSERT INTO idp (id, plant)
	VALUES ($id, $plant)";

	if ($conn->query($sql) === TRUE) {
	    echo "New record created successfully";
	} else {
	    echo "Error: " . $sql . "<br>" . $conn->error;
	}

	$conn->close();

?>