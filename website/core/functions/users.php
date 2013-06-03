<?php 

include 'includes/config.php';

function logged_in() {
	return (isset($_SESSION['user_id'])) ? 1 : 0;
}

function user_exists($mail) {
	global $connect, $user, $dbname_ud;
	$mail = sanitize($mail);
	mysqli_select_db($connect,$dbname_ud);
	$query = "SELECT `id` FROM `" . $user . "` WHERE email = '" . $mail . "'";
	$result = mysqli_query($connect,$query);
	
	return (mysqli_num_rows($result) == 1) ? 1 : 0;	
}

function user_active($mail) {
	global $connect, $user, $dbname_ud;
	$mail = sanitize($mail);
	mysqli_select_db($connect,$dbname_ud);
	$query = mysqli_query($connect,"SELECT `id` FROM `" . $user . "` WHERE email = '" . $mail . "' AND status = 1");

	return (mysqli_num_rows($query) == 1) ? 1 : 0;
}

function user_id_from_mail($mail) {
	global $connect, $user, $dbname_ud;
	$mail = sanitize($mail);
	mysqli_select_db($connect,$dbname_ud);
	$query = mysqli_query($connect,"SELECT `id` FROM `" . $user . "` WHERE email = '" . $mail . "'");
	$result = mysqli_fetch_array($query, MYSQLI_ASSOC);
	
	return $result["id"];
}

function login($mail, $password) {
	global $connect, $user;
	$user_id = user_id_from_mail($mail);
	$mail = sanitize($mail);
	$password = md5($password); // lieber password_hash() verwenden !!!
	$query = mysqli_query($connect,"SELECT `id` FROM `" . $user . "` WHERE email = '" . $mail . "' AND passwort = '" . $password . "'");
	
	return (mysqli_num_rows($query) == 1) ? $user_id : 0 ;
}

?>