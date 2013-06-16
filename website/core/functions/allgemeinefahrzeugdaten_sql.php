<?php 
/**
 *
 *	Importieren der Konfigurationsdatei mit allen 
 *  wichtigen Datenbankinformationen und Zugangsdaten 
 *
 */

include '../../includes/config.php';  

/**
 *
 * 	Baue Verbindung zur Datenbank auf und wähle die richtige Datenbank aus.
 *  Danach führe Datenbankoperation aus und speichere Ergebnis in JSON-Format
 *	
 *	Die If-Klausel realisiert eine einfach Zugriffssperre, da ohne Wert in $_POST
 *	die Anfrage nicht ausgeführt wird
 *
 */
 
if(array_key_exists('permission',$_POST)) 
{
	$con = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"3\">Verbindung zur Datenbank konnte nicht hergestellt werden.</td></tr>");
	$use=mysqli_select_db($con,"$dbname_fd"); 
		 
	$sql = "SELECT * 
			FROM `$general_data`
			WHERE Zeitpunkt=(SELECT max(Zeitpunkt) FROM `$general_data`)"; 	// selektiere nur die aktualleste Zeile
	$query= mysqli_query($con,$sql);			// Führe die DB Operation aus

	if (!$query) 								// Fehlerbehandlung
	{	
		echo 'Konnte Abfrage nicht ausführen: ' . mysqli_error($con);
		exit;
	}	
	$data=mysqli_fetch_row($query);          	// Speichere Zeile aus Ergebnis
	mysqli_close($con);
	echo json_encode($data);					// Formatiere in JSON
}

?>	
	
		