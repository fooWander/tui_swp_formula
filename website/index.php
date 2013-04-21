<?php include 'includes/overall/header.php'; ?>

	<button>Klick mich</button>
	
	<table class="data">
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
			printf ("<tr>\n    <td>%s\n    <td>%s</td>\n    <td>%s</td>\n</tr>\n",$unter['titel'],$unter['interpret'],$unter['jahr']);
		}
		
		mysqli_close($connection);
	?>
	</table>
	
	<br><br>
	
	<!-- Eine weitere Testdatenbank -->
	<b class="click">Verstecken</b>
	<table border="1">
	<tr>
		<td>Kundennam</td>
		<td>Nachname des Kontaktes</td>
		<td>Vorname des Kontaktes</td>
		<td>Ort</td></tr>
	<?php 	
		$connection = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"4\">Verbindung zur Datenbank konnte nicht hergestellt werde</td></tr>");
		$query = "SELECT customerName, contactLastName, contactFirstName, city FROM customers";
		mysqli_select_db($connection,"classicmodels") or die ("<tr><td colspan=\"4\">Die Datenbank konnte nicht ausgewählt werden</td></tr>");
		$result = mysqli_query($connection,$query);
	
		while($unter = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
			printf ("<tr>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n</tr>\n",$unter['customerName'],$unter['contactLastName'],$unter['contactFirstName'],$unter['city']);
		}
		
		mysqli_close($connection);
	?>
	</table>
	
	<br>
	
	<?php
		echo "<b>\"Thomas\" als SHA512-Hash:</b><br>\n";
		echo "<p>" . hash("sha512", "Thomas") . "</p>"; 
	?>
	
<?php include 'includes/overall/footer.php';?>