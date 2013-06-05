<?php 

include 'includes/config.php';

/**
 * Gibt auf Eingabe einer User-ID den zugehörigen Datensatz, wie Vor- und Nachname, Email, etc. aus. Diese können nach Belieben ausgewählt werden und müssen lediglich bei den Parametern ergänzt werden. (Siehe 'init.php')
 * @param unknown $user_id
 */
function user_data($user_id) {
	global $connect, $user, $dbname_ud;
	$data = array();
	$user_id = (int)$user_id;
	
	$func_num_args = func_num_args();
	$func_get_args = func_get_args();
	
	if ($func_num_args > 1) {
		unset($func_get_args[0]);
		$fields = '`' . implode('`, `', $func_get_args) . '`';
		mysqli_select_db($connect,$dbname_ud);
		$data = mysqli_fetch_assoc(mysqli_query($connect,"SELECT $fields FROM `" . $user . "` WHERE id = '" . $user_id . "'"));
		return $data;
	}
}

/**
 * Gibt zurück, ob Nutzer eingeloggt ist oder nicht.
 * @return boolean
 */
function logged_in() {
	return (isset($_SESSION['user_id'])) ? true : false;
}

/**
 * Gibt zurück, ob Nutzer im System existiert oder nicht.
 * @param string $mail
 * @return boolean
 */
function user_exists($mail) {
	global $connect, $user, $dbname_ud;
	$mail = sanitize($mail);
	mysqli_select_db($connect,$dbname_ud);
	$query = "SELECT `id` FROM `" . $user . "` WHERE email = '" . $mail . "'";
	$result = mysqli_query($connect,$query);
	
	return (mysqli_num_rows($result) == 1) ? true : false;	
}

/**
 * Gibt Status des zur Email-Adresse gehörigen Accounts zurück.
 * @param string $mail
 * @return boolean
 */
function user_active($mail) {
	global $connect, $user, $dbname_ud;
	$mail = sanitize($mail);
	mysqli_select_db($connect,$dbname_ud);
	$query = mysqli_query($connect,"SELECT `id` FROM `" . $user . "` WHERE email = '" . $mail . "' AND status = 1");

	return (mysqli_num_rows($query) == 1) ? true : false;
}

// ermitteln der id aus der zum login benutzten emailadresse
/**
 * 
 * @param String $mail
 * @return number
 */
function user_id_from_mail($mail) {
	global $connect, $user, $dbname_ud;
	$mail = sanitize($mail);
	mysqli_select_db($connect,$dbname_ud);
	$query = mysqli_query($connect,"SELECT `id` FROM `" . $user . "` WHERE email = '" . $mail . "'");
	$result = mysqli_fetch_array($query, MYSQLI_ASSOC);
	
	return $result["id"];
}

/**
 * Bekommt Email-Adresse und Passwort übegeben und vergleicht diese Daten mit denen aus der Nutzertabelle. Gibt bei Erfolg die Nutzer-ID und bei Misserfolg 'false' respektive '0' zurück.
 * @param String $mail
 * @param String $password
 * @return Ambigous <boolean, number>
 */
function login($mail, $password) {
	global $connect, $user;
	$user_id = user_id_from_mail($mail);
	$mail = sanitize($mail);
	$password = md5($password); // lieber password_hash() verwenden !!!
	$query = mysqli_query($connect,"SELECT `id` FROM `" . $user . "` WHERE email = '" . $mail . "' AND passwort = '" . $password . "'");
	
	return (mysqli_num_rows($query) == 1) ? $user_id : false ;
}

?>