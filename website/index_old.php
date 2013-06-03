<?php
	include 'core/init.php';	
	include 'includes/overall/header.php';	
?>

	<!-- Laden der Akkudatentabelle (noch: CD-Tabelle) -->
	<script type="text/javascript">
    function executeQuery() {
     	$.ajax({
     	url: 'core/functions/accu_data.php',
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

	<!-- Contentbereich ANFANG -->
	<div class="content">
		<div class="item">		
		<div id="table"></div>
		
		<!-- Eine weitere Testdatenbank -->
		<div class="item">
		<button>Verstecken</button>
		<table border="1" class="click">
		<tr>
			<td>Kundenname</td>
			<td>Nachname des Kontaktes</td>
			<td>Vorname des Kontaktes</td>
			<td>Ort</td></tr>
		<?php 	
			$connection = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"4\">Verbindung zur Datenbank konnte nicht hergestellt werde</td></tr>");
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
	
<?php include 'includes/overall/footer.php';?>