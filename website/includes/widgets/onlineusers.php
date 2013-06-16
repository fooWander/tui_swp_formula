<?php 
/**
 * Stellt als Widget f�r die Seite, die aktuell eingeloggten Nutzer dar.
 */

	if (!defined('ACCESS')) { die("Sie haben nicht die n�tigen Befugnisse diese Seite darstellen zu lassen."); }
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
					 
				$sql = "SELECT DISTINCT vorname,nachname, zeitpunkt 
						FROM `$user`, `$online`
						WHERE `$user`.id=`$online`.id";

				// F�hre die DB Operation aus
				$query= mysqli_query($con,$sql);			

				// Fehlerbehandlung
				if (!$query) 								
				{	
					echo 'Konnte Abfrage nicht ausf�hren: ' . mysqli_error($con);
					exit;
				}	
				
				// Ausgabe der Nutzer als Tabelle
				while($data = mysqli_fetch_array($query, MYSQLI_ASSOC)) {
					$zeit = (empty($data['zeitpunkt'])) ? "-" : round((time() - $data['zeitpunkt']) / 60) . " Minute(n)";
					printf ("	<tr>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n</tr>\n",$data['vorname'],$data['nachname'],$zeit);
				}
			mysqli_close($con);
			?>
		</table>				
	</div>