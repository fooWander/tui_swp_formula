<head>
    <meta charset="utf-8" />   
    <title>Fahrzeug Service Interface</title>
    <link rel="stylesheet" media="screen" href="css/style.css" />
    <link href='http://fonts.googleapis.com/css?family=Roboto+Condensed:400,300italic' rel='stylesheet' type='text/css' />
    <link href='http://fonts.googleapis.com/css?family=Archivo+Narrow:400,400italic' rel='stylesheet' type='text/css'>
    <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
    <script src="scripts/jquery-1.9.1.js"></script>
    <script src="scripts/code.js"></script>
    <script src="scripts/jquery.masonry.min.js"></script>
    
<?php

	/* Datenbankzugriff - Zugangsdatens */
	$dbhost = "localhost";					// Das kann so stehen bleiben.
	$dbuname = "root";  					// Hier den Datenbanknutzernamen eingeben.
	$dbpass = "stdvj";   					// Hier das Datenbankpasswort eintragen.
	
	$dbname = "swp";						// Datenbanknamen festlegen
	
	$data = "prototyp";	 					// Tabelle: Fahrzeugdaten
	$user = "";								// Tabelle: Benutzerdaten

?>
	    
</head>
<body>
	<!-- Laden der Akkudatentabelle (noch: CD-Tabelle) -->
	<script type="text/javascript">
	    function executeQuery() {
	     	$.ajax({
	     	url: 'testdata.php',
	     	success: function(data) {
	     		$("#table").html(data);
	     	}
	     	});
	     	setTimeout(executeQuery, 1000); 
	    }
	     
	    $(document).ready(function() {
	    		setTimeout(executeQuery, 1000);
	    });
	</script>
	
	<div class="content">
		<div class="item">		
			<div id="table"></div>
		</div>
	</div>
</body>