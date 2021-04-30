<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "gro";
$error = "hey";
date_default_timezone_set("Asia/Kolkata");
$date = date("Y-m-d");
$id = $_GET['id'];
$ct = $_GET['t'];
$ch = $_GET['h'];
$cr = $_GET['r'];
$cg = $_GET['g'];
$cb = $_GET['b'];
// SAMPLE GET REQUEST - localhost/gro/node.php?id=1&t=20&h=30&r=255&g=244&b=233"

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

//Get the plant based on ID
$sql = "SELECT id, plant FROM idp WHERE id ='" . $id . "'"  ;
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
    	//echo "Plant being grown :" . "<br>";
        $plant = $row["plant"];
        //echo $plant . "<br>" ;
        //echo "<br>";
    }
} else {
    echo "0 results";
}

//Get the plant conditions based on plant
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
        echo $humidity . "t" ;
        echo $temperature . "r" ;
        echo $red . "g" ;
        echo $green . "b" ;
        echo $blue . "f" ;
    }
} else {
    echo "0 results";
}

//Insert Conditions in table
/*
echo "<br>";
echo "current conditions :" . "<br>";
echo "$ch" . "<br>";
echo "$ct" . "<br>";
echo "$cr" . "<br>";
echo "$cg" . "<br>";
echo "$cb" . "<br>";
*/
$sql = "INSERT INTO ". $id ."co (humidity, temperature, red, green, blue)
VALUES ( $ch, $ct, $cr, $cg, $cb)";

if ($conn->query($sql) === TRUE) {

} else {
	$error = $sql . $conn->error;
    echo $error;
}


$conn->close();
?>