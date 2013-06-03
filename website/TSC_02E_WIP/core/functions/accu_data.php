<?php include '../../includes/config.php'; // Importieren der Konfigurationsdatei mit allen wichtigen Datenbankinformationen und Zugangsdaten ?>

	    
	<div class="content">
		<div class=item >
		<table border="1" class="click">
		<tr>
			<td class="tit"><div>Titel</div></td>
			<td class="int"><div>Interpret</div></td>
			<td class="year"><div>Jahr</div></td></tr>
		<?php 	
			$connection = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"3\">Verbindung zur Datenbank konnte nicht hergestellt werden.</td></tr>");
			$query = "SELECT * FROM cds";
			mysqli_select_db($connection,"$dbname") or die ("<tr><td colspan=\"3\">Die Datenbank konnte nicht ausgewählt werden.</td></tr>");
			$result = mysqli_query($connection,$query);
		
			while($unter = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
				printf ("	<tr>\n	<td>%s</td>\n	<td>%s</td>\n	<td>%s</td>\n </tr>\n",$unter['titel'],$unter['interpret'],$unter['jahr']);
			}
			
			mysqli_close($connection);
		?>
		</table></div>
		
		<div class="item">
		
		<table border="1" class="click">
		<tr>
			<td>Kundenname</td>
			<td>Nachname des Kontaktes</td>
			<td>Vorname des Kontaktes</td>
			<td>Ort</td></tr>
		<?php 	
			$connection = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"4\">Verbindung zur Datenbank konnte nicht hergestellt werde</td></tr> ");
			$query = "SELECT customerName, contactLastName, contactFirstName, city FROM customers";
			mysqli_select_db($connection,"classicmodels") or die ("<tr><td colspan=\"4\">Die Datenbank konnte nicht ausgewählt werden</td></tr>");
			$result = mysqli_query($connection,$query);
		
			while($unter = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
				printf ("	<tr>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n</tr>\n",$unter['customerName'],$unter['contactLastName'],$unter['contactFirstName'],$unter['city']);
			}
			
			mysqli_close($connection);
		?>
		</table>
		
		<br>
		</div>
	</div>
		
		
		