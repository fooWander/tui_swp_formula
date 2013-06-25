<?php
/**
 * Widget für die Verwaltungsseite. Ausgabe aller im System registrierten Benutzer. Nur für den Vorstand vorgesehen.
 */
if (!defined('ACCESS')) { die("Sie haben nicht die nötigen Befugnisse diese Seite darstellen zu lassen."); }
?>
<div class="single">
	<h2>Benutzerliste</h2>
	<p>Hier werden sämtlich im System registrierten Benutzer angezeigt.</p>
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
			// Ausgabe der Tabelle mit allen Daten, ohne Passwörter
			$connection = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"7\">Verbindung zur Datenbank konnte nicht hergestellt werde</td></tr>");
			$query = "SELECT DISTINCT benutzerdaten.id, vorname, nachname, email, rechte, status, zeitpunkt FROM $user LEFT OUTER JOIN $online ON $user.id = $online.id ORDER BY benutzerdaten.id ASC";
			mysqli_select_db($connection,$dbname_ud) or die ("<tr><td colspan=\"7\">Die Datenbank konnte nicht ausgewählt werden</td></tr>");
			$result = mysqli_query($connection,$query);
			
			while($row = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
				$tmp = (empty($row['zeitpunkt'])) ? "offline" : "online";
				printf ("	<tr>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td><p class=\"$tmp\">%s</p></td>\n</tr>\n",$row['id'],$row['vorname'],$row['nachname'],$row['email'],$row['rechte'],$row['status'],$tmp);
			}
			
			mysqli_close($connection);
		?>
	</table>
	<br>
	<div style="width: 200px;"><b><u>Erklärungen:</u></b><br>
		<p style="float: right;"><b>Status</b>:<br>
		0 - Deaktiviert<br>
		1 - Aktiviert<br></p>
		<p><b>Rechte</b>:<br>
		1 - Vorstand<br>
		2 - Beobachter<br>
		3 - Techniker<br></p>
	</div>
</div>