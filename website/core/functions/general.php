<?php 

include 'includes/config.php';

/**
 * Bereitet einen String auf, um vor SQL-Injections zu schützen.
 * @param string $data
 * @return string
 */
function sanitize($data) {
	global $connect;
	return mysqli_real_escape_string($connect,$data);
}

/**
 * Gibt gesammelte und übergebene Fehler in geordneter Weise aus.
 * @param array $errors
 * @return string
 */
function output_errors($errors) {
	$output = array();
	foreach ($errors as $error) {
		$output[] = '<li>' . $error . '</li>';
	}
	return '<ul class="error">' . implode('', $output) . '</ul>';
}

?>