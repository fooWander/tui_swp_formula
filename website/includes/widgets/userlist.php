<?php
/**
 * Widget f�r die Verwaltungsseite. Ausgabe aller im System registrierten Benutzer. Nur f�r den Vorstand vorgesehen.
 */
?>
<div class="single">
	<h2>Benutzerliste</h2>
	<p>Hier werden s�mtlich im System registrierten Benutzer angezeigt.</p>
	<br>
	<table border="1" class="click">
		<tr>
			<td>ID</td>
			<td>Vorname</td>
			<td>Nachname</td>
			<td>E-Mail</td>
			<td>Rechte</td>
			<td>Status</td>
			<td>Online?</td>
		</tr>
		<?php 	
			// Ausgabe der Tabelle mit allen Daten, ohne Passw�rter
			$connection = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"7\">Verbindung zur Datenbank konnte nicht hergestellt werde</td></tr>");
			$query = "SELECT DISTINCT benutzerdaten.id, vorname, nachname, email, rechte, status, zeitpunkt FROM $user LEFT OUTER JOIN $online ON $user.id = $online.id";
			mysqli_select_db($connection,$dbname_ud) or die ("<tr><td colspan=\"7\">Die Datenbank konnte nicht ausgew�hlt werden</td></tr>");
			$result = mysqli_query($connection,$query);
			
			while($row = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
				$tmp = (empty($row['zeitpunkt'])) ? "offline" : "online";
				printf ("	<tr>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td><p class=\"$tmp\">%s</p></td>\n</tr>\n",$row['id'],$row['vorname'],$row['nachname'],$row['email'],$row['rechte'],$row['status'],$tmp);
			}
			
			mysqli_close($connection);
		?>
	</table>
	<br><p><b>Erkl�rungen:</b><br>
	<b>Status</b>:<br>
	0 - Deaktiviert<br>
	1 - Aktiviert<br>
	<b>Rechte</b>:<br>
	1 - Vorstand<br>
	2 - Beobachter<br>
	3 - Techniker<br></p>
</div>