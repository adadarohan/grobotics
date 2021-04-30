<!DOCTYPE html>
<html>
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title></title>
	<script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
	<script type="text/javascript"> 
	  google.charts.load('current', {'packages':['corechart']});
	  google.charts.setOnLoadCallback(drawChart);

	  function drawChart() {
	    var data = google.visualization.arrayToDataTable([ 
	    ['Time', 'Red', 'Green', 'Blue'],



	<?php

		$servername = "localhost";
		$username = "root";
		$password = "";
		$dbname = "gro";
		$id = $_GET['id'];
		date_default_timezone_set('Asia/Kolkata');

	                                                                                                                                                                       
		$conn = new mysqli($servername, $username, $password, $dbname);
		// Check connection
		if ($conn->connect_error) {
		    die("Connection failed: " . $conn->connect_error);
		}


		$sql = "SELECT time, red , green , blue FROM " . $id . "co ORDER BY time DESC" ;
		$result = $conn->query($sql);
	 
		if ($result->num_rows > 0) {
		    // output data of each row
		    while($row = $result->fetch_assoc()) {
		        echo "[ new Date('" . date('c', strtotime ($row["time"])). "') , " . $row["red"]. " , " . $row["green"]. " , " . $row["blue"]." ], " ;
		    }
		} else {
		    //echo "0 results";
		}

		$conn->close();
		
	?>
	]);

	       var options = {
	         title: 'Light Color',
	         curveType: 'function',
	         legend: { position: 'bottom' },
	         backgroundColor: '#f9f1f1',
	         animation:{
	           startup : 'true',
	           duration: 1000,
	           easing: 'out',
	         },
	         colors: ['red', 'green', 'blue']
	       };

	       var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));

	       chart.draw(data, options);
	     }
	   </script>
	   <style type="text/css">
		   	body{
		   		background-color: #f9f1f1;
		   	}

	   </style>
</head>
<body>
	<div id="curve_chart" style="width: 100vw; height: 100vh"></div>
</body>
</html>

