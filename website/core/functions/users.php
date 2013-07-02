<?php 

include 'includes/config.php';

/**
 * Setzt das bestehende Passwort zurück und erzeugt ein zufälliges neues Passwort, welches dem Nutzer per Mail zugeschickt wird.
 * @param string $mail
 */
function recover($mail) {
	sanitize($mail);
	
	$user_data = user_data(user_id_from_mail($mail), 'id');
	$new_password = generateRandomString();
	change_password($user_data['id'], $new_password);	
	
	require 'includes/phpmailer/class.phpmailer.php';
	
	$email = new PHPMailer;
	
	// E-Mail-Verbindungsaufbau und -Versenden
	$email->IsSMTP();                                      // Set mailer to use SMTP
	$email->Host = 's16929463.onlinehome-server.info';  // Specify main and backup server
	$email->SMTPAuth = true;                               // Enable SMTP authentication
	$email->Username = 'Telemetrie@s16929463.onlinehome-server.info';                            // SMTP username
	$email->Password = 'e]jm&fNJz9';                           // SMTP password
	$email->SMTPSecure = 'tls';                            // Enable encryption, 'ssl' also accepted
	
	$email->From = 'noreply@teamstarcraft.de';
	$email->FromName = 'Team Starcraft e. V.';
	$email->AddAddress($mail);  // Add a recipient
	
	$email->WordWrap = 50;                                 // Set word wrap to 50 characters
	$email->IsHTML(true);                                  // Set email format to HTML
	
	$email->Subject = 'Ihr neues Passwort';
	$email->Body    = 'Sehr geehrter Nutzer,<br><br>Ihr Passwort wurde erfolgreich zurückgesetzt. Das neue Passwort lautet <b>' . $new_password  .  '</b>. Bitte ändern Sie dieses nach Ihrem Login schnellstmöglich wieder!<br> Vielen Dank!<br>Team Starcraft e. V.';
	$email->AltBody = "Sehr geehrter Nutzer,\n\nIhr Passwort wurde erfolgreich zurückgesetzt. Das neue Passwort lautet " . $new_password  .  ". Bitte ändern Sie dieses nach Ihrem Login schnellstmöglich wieder! Vielen Dank! \n Team Starcraft e. V.";
	
	if(!$email->Send()) {
		echo "Mailer Error: " . $email->ErrorInfo;
	}
}

/**
 * Bekommt eine ID und einen String übergeben und ändert das zur ID gehörende Passwort in der Datenbank
 * @param int $user_id
 * @param string $password
 */
function change_password($user_id, $password) {
	global $connect, $user, $dbhost, $dbuname, $dbpass, $dbname_ud, $cryptsalt;
	$user_id = (int)$user_id;
	$password = crypt($password,$cryptsalt);
	
	$connect = mysqli_connect("$dbhost", "$dbuname", "$dbpass") or die("Verbindung zur Datenbank konnte nicht hergestellt werden.");
	mysqli_select_db($connect,$dbname_ud);
	$string = "UPDATE `" . $user . "` SET `passwort` = '" . $password ."' WHERE id = " . $user_id;
	mysqli_query($connect, $string);
	
}

/**
 * Legt in der Datenbank einen neuen (deaktivieren) Nutzer in der Datenbank an und zwar mitsamt allen angegeben Daten und verschlüsseltem Passwort.
 * @param array $register_data
 */
function register_user($register_data) {
	global $connect, $user, $dbname_ud, $cryptsalt;
	array_walk($register_data, 'array_sanitize');
	$register_data['passwort'] = crypt($register_data['passwort'],$cryptsalt);
	$fields = '`' . implode('`, `', array_keys($register_data)) . '`';
	$data = '\'' . implode('\', \'', $register_data) . '\'';
	
	mysqli_select_db($connect,$dbname_ud);
	mysqli_query($connect, "INSERT INTO `" . $user . "` ($fields) VALUES ($data)");
}

/**
 * Bestimmt die Anzahl der im System registrierten Nutzer. Betroffen sind hiervon lediglich aktivierte Accounts.
 */
function user_count() {
	global $connect, $dbname_ud, $user;
	mysqli_select_db($connect,$dbname_ud);
	return mysqli_num_rows(mysqli_query($connect, "SELECT `id` FROM `" . $user . "` WHERE status = 1"));
}

/**
 * Gibt auf Eingabe einer User-ID den zugehörigen Datensatz, wie Vor- und Nachname, Email, etc. aus. Diese können nach Belieben ausgewählt werden und müssen lediglich bei den Parametern ergänzt werden. (Siehe 'init.php')
 * @param int $user_id
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
 * Prüft ob es ich beim aktiven Nutzer um einen Nutzer der Rechtegruppe 'Vorstand' handelt.
 * @return boolean
 */
function isVorstand() {
	global $user_data;
	return ($user_data['rechte'] == 1) ? true : false ;
}

/**
* Prüft ob es ich beim aktiven Nutzer um einen Nutzer der Rechtegruppe 'Techniker' handelt.
* @return boolean
*/
function isTechniker() {
	global $user_data;
	return ($user_data['rechte'] == 3) ? true : false ;	
}

/**
* Prüft ob es ich beim aktiven Nutzer um einen Nutzer der Rechtegruppe 'Beobachter' handelt.
* @return boolean
*/
function isBeobachter() {
	global $user_data;
	return ($user_data['rechte'] == 2) ? true : false ;
}

/**
 * Überprüft ob der Zeitstempel in der SESSION-Variable 'time' älter als $time Minuten ist. In diesem Fall $time = 60 Minuten.
 * @return boolean
 */
function timeout() {
	$time = 60;
	return ((time() - $_SESSION['time']) < ($time*60)) ? true : false ;
}

/**
 * Gibt zurück, ob Nutzer eingeloggt ist oder nicht. Dies impliziert auch eine Überprüfung ob seine letzte Aktivität weiter als eine in der Funktion timeout() festgelegte Zeitspanne her ist.
 * Setzt beim Aufruf den 'time' Wert auf einen aktuellen Wert.
 * @return boolean
 */
function logged_in() {
	if (isset($_SESSION['user_id']) && timeout()) {
		$_SESSION['time'] = time();		
		return true;
	} else {
		return false;
	}
	return (isset($_SESSION['user_id'])) ? true : false;
}

/**
 * Diese Funktion aktualisiert den Zeitwert in der Tabelle der momentan sich online befindlichen Nutzer. Außerdem löscht sie alle Einträge, deren Timeout bereits abgelaufen ist. (Hier: 60 Minuten) 
 */
function refresh() {
	global $connect, $dbname_ud, $online;
	$time = 60;
	mysqli_select_db($connect,$dbname_ud);
	mysqli_query($connect, "UPDATE `" . $online . "` SET zeitpunkt = " . $_SESSION['time'] . " WHERE id = " . $_SESSION['user_id']);
	$tmpVar = time() - ($time*60);
	mysqli_query($connect, "DELETE FROM `" . $online . "` WHERE zeitpunkt < " . $tmpVar);
	mysqli_close($connect);	
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

/**
 * Ermittelt die ID des Nutzers, der zur übergebenen Emailadresse gehört.
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
	global $connect, $user, $cryptsalt;
	$user_id = user_id_from_mail($mail);
	$mail = sanitize($mail);
	$password = crypt($password, $cryptsalt); 
	$query = mysqli_query($connect,"SELECT `id` FROM `" . $user . "` WHERE email = '" . $mail . "' AND passwort = '" . $password . "'");
	
	return (mysqli_num_rows($query) == 1) ? $user_id : false ;
}

?>