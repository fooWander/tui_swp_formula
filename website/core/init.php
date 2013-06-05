<?php 

	session_start();
	error_reporting(E_ALL);
	
	include 'includes/config.php';
	
	$connect = mysqli_connect("$dbhost", "$dbuname", "$dbpass") or die("Verbindung zur Datenbank konnte nicht hergestellt werden.");	
	
	require 'functions/general.php';
	require 'functions/users.php';
	
	if (logged_in() == true) {
		$session_user_id = $_SESSION['user_id'];
		$user_data = user_data($session_user_id, 'id', 'passwort', 'vorname', 'nachname', 'email');
		
		if (user_active($user_data['email']) == false) {
			session_destroy();
			header('Location: index.php');
			exit();
		}
		
	}
	
	$errors = array();
	
?>