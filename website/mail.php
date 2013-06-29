<?php
require 'includes/phpmailer/class.phpmailer.php';

$email = new PHPMailer;

$email->IsSMTP();                                      	// Set mailer to use SMTP
$email->Host = 's16929463.onlinehome-server.info'; 		// Specify main and backup server
//$email->Host = 'mail.gmx.net'; 						// Specify main and backup server
$email->SMTPAuth = true;                               	// Enable SMTP authentication
$email->Username = 'Telemetrie@s16929463.onlinehome-server.info';                            // SMTP username
$email->Password = 'e]jm&fNJz9';                        // SMTP password
//$email->Username = 'golda@gmx.net';                            // SMTP username
//$email->Password = 'win91ter';                        // SMTP password
$email->SMTPSecure = 'tls';                            	// Enable encryption, 'ssl' also accepted

$email->From = 'noreply@teamstarcraft.de';
$email->FromName = 'Team Starcraft e. V.';
$email->AddAddress($mail);  							// Add a recipient

$email->WordWrap = 50;                                 	// Set word wrap to 50 characters
$email->IsHTML(true);                                  	// Set email format to HTML

$email->Subject = 'Neue Registrierung im Service Interface';
$email->Body    = "Sehr geehrter Team Starcraft Vorstand,<br><br>ein neuer Benutzer <b>(" . $register_data['email'] . ")</b> hat sich im System registriert. Bitte loggen Sie sich im Service Interface ein und überprüfen Sie ob es sich um eine berechtigte Registrierung handelt. Dort können Sie ihn auch freischalten. Bitte kontaktieren Sie den Benutzer anschließend per Mail und weisen ihn ggf. auf die Freischaltung seines Accounts hin.<br><br>Besten Dank!<br><br>(Diese E-Mail wurde automatisch generiert.)";
$email->AltBody = "Sehr geehrter Vorstand,\n\nein neuer Benutzer (" . $register_data['email'] . ") hat sich im System registriert. Bitte loggen Sie sich im Service Interface ein und überprüfen Sie ob es sich um eine berechtigte Registrierung handelt. Dort können Sie ihn auch freischalten. Bitte kontaktieren Sie den Benutzer anschließend per Mail und weisen ihn ggf. auf die Freischaltung seines Accounts hin.\n\nBesten Dank!\n\n(Diese E-Mail wurde automatisch generiert.)";

if(!$email->Send()) {
	echo "Mailer Error: " . $email->ErrorInfo;
}
?>