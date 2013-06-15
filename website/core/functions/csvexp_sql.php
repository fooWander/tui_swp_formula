<?php 

include '../../includes/config.php';

header("Content-type: text/csv");
header("Content-Disposition: attachment; filename=file.csv");
header("Pragma: no-cache");
header("Expires: 0");

if (empty($_POST) == false) {

	$connect = mysqli_connect("$dbhost", "$dbuname", "$dbpass") or die("Verbindung zur Datenbank konnte nicht hergestellt werden.\n<br>\n");
	mysqli_select_db($connect,"$dbname_fd");
	
	
	if(array_key_exists('alledaten',$_POST))
	{
		$sql = "SELECT  * FROM `" . $general_data . "` NATURAL JOIN `" . $accu_data	. "` NATURAL JOIN `" . $dynamic_data . "` NATURAL JOIN `" . $driving_data . "` NATURAL JOIN `" . $engine_data . "`";
	}
	else
	{
		$val=array();
		if(array_key_exists('choice1',$_POST)){$val[] = $general_data;}
		if(array_key_exists('choice2',$_POST)){$val[] = $accu_data;}
		if(array_key_exists('choice3',$_POST)){$val[] = $dynamic_data;}
		if(array_key_exists('choice4',$_POST)){$val[] = $driving_data;}
		if(array_key_exists('choice5',$_POST)){$val[] = $engine_data;}
		$sql = "SELECT  *  FROM	`" . implode("` NATURAL JOIN `",$val);
	}
	
	// Führe die DB Operation aus
	$query = mysqli_query($connect,$sql);			

	// Fehlerbehandlung
	if (!$query) 								
	{
		echo 'Konnte Abfrage nicht ausführen: ' . mysqli_error($connect);
		exit;
	}
	mysqli_close($connect);

	// Hilfsboolean, damit erste Schleife für Kopf nur einmal ausgeführt wird
	$bool = true;
	
	// Für jede Zeile der Tabelle die einzelnen Felder ausgeben
	while($unter = mysqli_fetch_array($query, MYSQLI_ASSOC)) {
		if ($bool == true) {
			$tmp = array_keys($unter);
			
			for($i = 0; $i < count($tmp); $i++) {		
				if ($i == count($unter) - 1) {
					echo $tmp[$i] . "\n";
				} else {
					echo $tmp[$i] . ", ";
				}
			}
			
			$bool = false;
		}
		$unter = array_values($unter);
		$bla = count($unter);
		for($i = 0; $i < count($unter); $i++) {
			
			if ($i == count($unter) - 1) {
				echo $unter[$i] . "\n";
			} else {
				echo $unter[$i] . ", ";
			}
			
		}
	}
}
?>