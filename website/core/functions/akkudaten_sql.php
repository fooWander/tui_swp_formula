<?php 
/**
 *	Importieren der Konfigurationsdatei mit allen 
 *  wichtigen Datenbankinformationen und Zugangsdaten 
 */

include '../../includes/config.php';  

/**
 * 	Baue Verbindung zur Datenbank auf und w�hle die richtige Datenbank aus.
 *  Danach f�hre Datenbankoperation aus und speichere Ergebnis in JSON-Format
 */



$con = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"3\">Verbindung zur Datenbank konnte nicht hergestellt werden.</td></tr>");
$use=mysqli_select_db($con,"$dbname_fd"); 
	 
$sql = "SELECT * 
		FROM `$accu_data`
		WHERE Zeitpunkt=(SELECT max(Zeitpunkt) FROM `$accu_data`)"; 		// selektiere nur die aktualleste Zeile ("accent grave" am Anfang und Ende ist wichtig!)
$query= mysqli_query($con,$sql);			// F�hre die DB Operation aus

if (!$query) 								// Fehlerbehandlung
{	
    echo 'Konnte Abfrage nicht ausf�hren: ' . mysqli_error($con);
    exit;
}	
$data=mysqli_fetch_row($query);          	// Speichere Zeile aus Ergebnis
mysqli_close($con);
echo json_encode($data);					// Formatiere in JSON

?>	
	
		