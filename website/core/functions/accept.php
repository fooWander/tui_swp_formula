<?php

/**
 * Bekommt die Übergebenen Parameter für die Nutzeränderungen und tut die Änderungen durchführen. 
 */

	session_start();
	error_reporting(E_ALL);
	
	include '../../includes/config.php';
	
	$formdata = array();
	$errors = array();
	
	if(array_key_exists('userid',$_POST)) {
		$formdata['userid'] = (int)$_POST['userid'];
		if (empty($formdata['userid'])) {
			$errors[] = "Die User-ID ist leer.";
			header('Location: ../../index.php?notaccepted');
			exit();
		}
		if ($formdata['userid'] == $_SESSION['user_id']) {
			$errors[] = "Sie können nicht ihren eigenen Account löschen!";
			header('Location: ../../index.php?notaccepted');
			exit();
		}
	}
	
	if (array_key_exists('manage',$_POST)) {
		$formdata['manage'] = $_POST['manage'];
	} else {
		header('Location: ../../index.php?notaccepted');
		exit();
	}
	
	$formdata['rights'] = $_POST['rights'];
	
	if ($formdata['rights'] == 'vorstand') {
		$formdata['rights'] = 1;
	}
	
	if ($formdata['rights'] == 'beobachter') {
		$formdata['rights'] = 2;
	}
	
	if ($formdata['rights'] == 'techniker') {
		$formdata['rights'] = 3;
	}
	
	// Aktivieren bzw. löschen des Nutzers
	if ($formdata['manage'] == 'activate' ) {
		$sql = "UPDATE `" . $user . "` SET `status` = 1, `rechte` = " . $formdata['rights'] . " WHERE id = " . $formdata['userid']; // Aktivieren
	} else {
		$sql = "DELETE FROM " . $user . " WHERE id = " . $formdata['userid']; // Löschen
	}
	
	// Verbindung zur Datenbank und Ausführen des Querys
	$connection = mysqli_connect("$dbhost", "$dbuname", "$dbpass");
	mysqli_select_db($connection,$dbname_ud);
	mysqli_query($connection,$sql);
	mysqli_close($connection);
	
	header('Location: ../../index.php?accepted');
	exit();

?>