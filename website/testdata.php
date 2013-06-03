<?php

	/* Datenbankzugriff - Zugangsdatens */
	$dbhost = "localhost";					// Das kann so stehen bleiben.
	$dbuname = "root";  					// Hier den Datenbanknutzernamen eingeben.
	$dbpass = "stdvj";   					// Hier das Datenbankpasswort eintragen.
	
	$dbname = "swp";						// Datenbanknamen festlegen
	
	$data = "prototyp";	 					// Tabelle: Fahrzeugdaten
	$user = "";								// Tabelle: Benutzerdaten

?>

		<table class="data1">
		<tr>
			<td class="tit"><div>ID</div></td>
			<td class="int"><div>Text</div></td>
		<?php 	
			$connection = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"3\">Verbindung zur Datenbank konnte nicht hergestellt werden.</td></tr>");
			$query = "SELECT * FROM $data";
			mysqli_select_db($connection,"$dbname") or die ("<tr><td colspan=\"3\">Die Datenbank konnte nicht ausgewählt werden.</td></tr>");
			$result = mysqli_query($connection,$query);
		
			while($unter = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
				printf ("		<tr>\n			<td>%s\n			<td>%s</td>\n			</tr>\n",$unter['id'],$unter['text']);
			}
			
			mysqli_close($connection);
		?>
		</table></div>