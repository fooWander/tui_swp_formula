<?php 
include '../../includes/config.php';
$con_ud = mysqli_connect("$dbhost", "$dbuname" , "$dbpass") or die("Verbindung zur Datenbank konnte nicht hergestellt werden.<br>\n");
mysqli_select_db($con_ud,"$dbname_ud") or die ("Die Datenbank konnte nicht ausgewählt werden.<br>\n");
?>