<?php
	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "gro";
	$id = $_GET['id'];

	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
	    die("Connection failed: " . $conn->connect_error);
	}
	$sql = "SELECT id, plant FROM idp WHERE id ='" . $id . "'"  ;
	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
	    // output data of each row
	    while($row = $result->fetch_assoc()) {
	    	//echo "Plant being grown :" . "<br>";
	        $plant = $row["plant"];
	        echo $plant . " " ;
	    }
	} 
 	
 	
	$sql = "SELECT humidity, temperature, red , blue, green FROM " . $id . "co ORDER BY time DESC LIMIT 1" ;
	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
	    // output data of each row
	    while($row = $result->fetch_assoc()) {
	        echo $row["humidity"]. " " . $row["temperature"]. " " . $row["red"]. " " . $row["green"]. " " .$row["blue"]. " " ;
	    }
	} else {
	    //echo "0 results";
	}
	/*
	$sql = "SELECT plant, humidity, temperature, red, green, blue FROM plc WHERE plant ='" . $plant . "'"  ;
	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
	    // output data of each row
	    while($row = $result->fetch_assoc()) {
	        $humidity = $row["humidity"];
	        $temperature = $row["temperature"];
	        $red = $row["red"];
	        $green = $row["green"];
	        $blue = $row["blue"];
	        echo $humidity . " " ;
	        echo $temperature . " " ;
	        echo $red . " " ;
	        echo $green . " " ;
	        echo $blue  ;
	    }
	} else {
	    //echo "0 results";
	}
	*/
	$conn->close();

?>