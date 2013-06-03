<?php 

include 'includes/config.php';

function sanitize($data) {
	global $connect;
	return mysqli_real_escape_string($connect,$data);
}

function output_errors($errors) {
	$output = array();
	foreach ($errors as $error) {
		$output[] = '<li>' . $error . '</li>';
	}
	return '<ul class="error">' . implode('', $output) . '</ul>';
}

?>