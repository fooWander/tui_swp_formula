<?php 

include 'includes/config.php';

/**
 * Arbeitet �hnlich wie protect_page(), verhindert dass angemeldete Benutzer auf Seiten zugreifen, deren Zugriff f�r einen bereits registrierten Nutzer keinen Sinn ergibt. (z.B. die Registrierungsseite)
 */
function logged_in_redirect() {
	if (logged_in() == true) {
		header('Location: index.php');
		exit();		
	}
}

/**
 * Pr�ft beim Aufruf der Funktion ob der Benutzer eingeloggt ist und leitet ihn, falls dies nicht der Fall ist, auf die Startseite um.
 */
function protect_page() {
	if (logged_in() == false) {
		header('Location: index.php?denied');
		exit();
	}
}

/**
 * Bereitet ein Array von Strings auf, umd SQL-Injections vorzubeugen.
 * @param array $item
 */
function array_sanitize(&$item) {
	global $connect;
	$item = mysqli_real_escape_string($connect,$item);
}

/**
 * Bereitet einen String auf, um vor SQL-Injections zu sch�tzen.
 * @param string $data
 * @return string
 */
function sanitize($data) {
	global $connect;
	return mysqli_real_escape_string($connect,$data);
}

/**
 * Gibt gesammelte und �bergebene Fehler in geordneter Weise aus.
 * @param array $errors
 * @return string
 */
function output_errors($errors) {
	$output = array();
	foreach ($errors as $error) {
		$output[] = '<li><p class="fehlermeldung">' . $error . '</p></li>';
	}
	return '<ul class="error">' . implode('', $output) . '</ul>';
}

?>