<?php 
/**
 * Stellt als Widget für die Seite, die aktuell eingeloggten Nutzer dar.
 */
?>

	<div class ="item">
		<h2>Benutzerstatus</h2>
		<table border="1" class="click">
			<tr>
				<td>Vorname</td>
				<td>Nachname</td>
				<td>zuletzt aktiv vor</td>
			</tr>
			<?php
				$con = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"3\">Verbindung zur Datenbank konnte nicht hergestellt werden.</td></tr>");
				$use = mysqli_select_db($con,"$dbname_ud"); 
					 
				$sql = "SELECT vorname,nachname, zeitpunkt 
						FROM `$user`, `$online`
						WHERE `$user`.id=`$online`.id";
						
				$query= mysqli_query($con,$sql);			// Führe die DB Operation aus

				if (!$query) 								// Fehlerbehandlung
				{	
					echo 'Konnte Abfrage nicht ausführen: ' . mysqli_error($con);
					exit;
				}	
	         	// Speichere Zeile aus Ergebnis
				
				// Formatiere in JSON
				while($data = mysqli_fetch_array($query, MYSQLI_ASSOC)) {
					$zeit = (empty($data['zeitpunkt'])) ? "-" : round((time() - $data['zeitpunkt']) / 60) . " Minute(n)";
					printf ("	<tr>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n</tr>\n",$data['vorname'],$data['nachname'],$zeit);
				}
			mysqli_close($con);
			?>
		</table>				
	</div>