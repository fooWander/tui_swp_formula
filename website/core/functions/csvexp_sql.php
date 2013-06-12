<?php 

session_start();
error_reporting(E_ALL);

include '../../includes/config.php';

/**
 *
 * 	Baue Verbindung zur Datenbank auf und wähle die richtige Datenbank aus.
 *  Danach führe Datenbankoperation aus und speichere Ergebnis in JSON-Format
 *
 */

if (empty($_POST) == false) {
	$connect = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("<tr><td colspan=\"3\">Verbindung zur Datenbank konnte nicht hergestellt werden.</td></tr>");
	$use = mysqli_select_db($connect,"$dbname_fd");
	
	//print_r $_POST;

	if(array_key_exists('alledaten',$_POST))
	{
		$sql = "SELECT  *
		FROM `$general_data`
		NATURAL JOIN `$accu_data`
		NATURAL JOIN `$dynamic_data`
		NATURAL JOIN `$driving_data`
		NATURAL JOIN `$engine_data`";
	}
	else
	{
		$val=array();
		if(array_key_exists('choice1',$_POST)){$val=array_merge($val,[$general_data]);};
		if(array_key_exists('choice1',$_POST)){$val=array_merge($val,[$accu_data]);};
		if(array_key_exists('choice1',$_POST)){$val=array_merge($val,[$dynamic_data]);};
		if(array_key_exists('choice1',$_POST)){$val=array_merge($val,[$driving_data]);};
		if(array_key_exists('choice1',$_POST)){$val=array_merge($val,[$engine_data]);};
		$sql = "SELECT  *  FROM	`".implode("` NATURAL JOIN `",$val);
	}
		
	$query= mysqli_query($connect,$sql);			// Führe die DB Operation aus

	if (!$query) 								// Fehlerbehandlung
	{
		echo 'Konnte Abfrage nicht ausführen: ' . mysqli_error($connect);
		exit;
	}
	mysqli_close($connect);


	$csvString = "";
	$csvcolumns= "";
	$count=0;
	while($ret=$query->fetch_row())
	{
		for($k=0;$k<count($ret);$k++)
		{
			$query->field_seek($k);
			$finfo = $query->fetch_field();		// Tabellenüberschriften sammeln
			if($k==0)
			{
				$csvString.="$ret[$k]";		// beschreibe die erst Stelle, sonst leer (alles um eins nach rechts verschoben)
			}
			else
			{
				$csvString.=";\"".$ret[$k]."\"";			// bearbeite Werte so, dass sie CSV konform sind
			}
			if(!$count) $csvcolumns.=($csvcolumns?";":"").$finfo->name;		// trenne Daten richtig
		}
		$csvString.="\n";
		$count++;
	}
	$csvdata= str_replace(["\n","."],["\n",","],$csvcolumns."\n".$csvString);	// ersetze "." durch "," Floatwerte sonst als Datum angezeigt

	header("Content-type: text/csv");
	header("Cache-Control: no-store, no-cache");
	header('Content-Disposition: attachment; filename="tsc02e.csv"');
	 
	$outstream = fopen("php://output",'w');

	echo $csvdata;
	 
	fclose($outstream);
}
?>