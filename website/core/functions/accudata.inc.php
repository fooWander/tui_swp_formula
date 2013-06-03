<?php include '../../includes/config.php'; // Importieren der Konfigurationsdatei mit allen wichtigen Datenbankinformationen und Zugangsdaten ?>

		<table class="data1">
		<tr>
			<td class="tit"><div>Titel</div></td>
			<td class="int"><div>Interpret</div></td>
			<td class="year"><div>Jahr</div></td></tr>
		<?php 	
			$connection = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"3\">Verbindung zur Datenbank konnte nicht hergestellt werden.</td></tr>");
			$query = "SELECT * FROM $data";
			mysqli_select_db($connection,"$dbname") or die ("<tr><td colspan=\"3\">Die Datenbank konnte nicht ausgewählt werden.</td></tr>");
			$result = mysqli_query($connection,$query);
		
			while($unter = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
				printf ("		<tr>\n			<td>%s\n			<td>%s</td>\n			<td>%s</td>\n		</tr>\n",$unter['titel'],$unter['interpret'],$unter['jahr']);
			}
			
			mysqli_close($connection);
		?>
		</table></div>