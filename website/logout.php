<?php 
	/**
	 * Beenden der Sitzung und Umleiten auf die Startseite
	 */
	include 'core/init.php';
	session_destroy();
	header('Location: index.php');
	exit();
?>