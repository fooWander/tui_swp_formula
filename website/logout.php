<?php 
	/**
	 * Beenden der Sitzung und Umleiten auf die Startseite
	 */
	include 'core/init.php';
	mysqli_select_db($connect,$dbname_ud);
	mysqli_query($connect, "DELETE FROM `" . $online . "` WHERE id = " . $_SESSION['user_id']);	
	session_destroy();
	header('Location: index.php');
	exit();
?>