<?php 

	session_start();
	error_reporting(E_ALL);
	
	include 'includes/config.php';
	
	$connect = mysqli_connect("$dbhost", "$dbuname", "$dbpass") or die("Verbindung zur Datenbank konnte nicht hergestellt werden.");	
	
	require 'functions/general.php';
	require 'functions/users.php';
	
	$errors = array();
	
?>