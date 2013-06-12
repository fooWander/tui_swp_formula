<?php 

	/**
	 * Starten der Sitzung und Deaktivieren der Fehlermeldungen
	 */
	session_start();
	error_reporting(E_ALL);
	
	/**
	 * Einbinden der Konfigurationsdatei für Datenbankzugriffe, etc. und verbinden mit der Datenbank
	 */
	include 'includes/config.php';
	
	$connect = mysqli_connect("$dbhost", "$dbuname", "$dbpass") or die("Verbindung zur Datenbank konnte nicht hergestellt werden.");	
	
	require 'functions/general.php';
	require 'functions/users.php';
	
	/**
	 * Zwischenspeichern der Userdaten für die aktuelle Sitzung und anlegen eines Fehlerfeldes zum Sammeln sämtlicher Fehlermeldungen
	 * beim Aufruf der Seite(n)
	 */
	if (logged_in() == true) {
		$session_user_id = $_SESSION['user_id'];
		$user_data = user_data($session_user_id, 'id', 'passwort', 'vorname', 'nachname', 'email', 'rechte');
		
		if (user_active($user_data['email']) == false) {
			session_destroy();
			header('Location: index.php');
			exit();
		}
		
	}
	
	$errors = array();
	
?>