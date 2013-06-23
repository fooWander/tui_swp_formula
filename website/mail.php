<?php
require 'includes/phpmailer/class.phpmailer.php';

$mail = 'thomas.golda@tu-ilmenau.de';

$email = new PHPMailer;

$email->IsSMTP();                                      	// Set mailer to use SMTP
$email->Host = 's16929463.onlinehome-server.info'; 		// Specify main and backup server
$email->SMTPAuth = true;                               	// Enable SMTP authentication
$email->Username = 'Telemetrie@s16929463.onlinehome-server.info';                            // SMTP username
$email->Password = 'e]jm&fNJz9';                        // SMTP password
$email->SMTPSecure = 'tls';                            	// Enable encryption, 'ssl' also accepted

$email->From = 'noreply@teamstarcraft.de';
$email->FromName = 'Team Starcraft e. V.';
$email->AddAddress($mail);  							// Add a recipient
//$email->AddBCC('thomas.golda@tu-ilmenau.de');

$email->WordWrap = 50;                                 	// Set word wrap to 50 characters
$email->IsHTML(true);                                  	// Set email format to HTML

$email->Subject = 'Neue Registrierung im Service Interface';
$email->Body    = "Sehr geehrter Vorstand,<br><br>ein neuer Benutzer hat sich im System registriert. Bitte loggen Sie sich im Service Interface ein und überprüfen Sie seine Berechtigungen. Dort können Sie ihn auch freischalten.<br><br>Besten Dank!<br><br>(Diese E-Mail wurde automatisch generiert.)";
$email->AltBody = "Sehr geehrter Vorstand,\n\nein neuer Benutzer hat sich im System registriert. Bitte loggen Sie sich im Service Interface ein und überprüfen Sie seine Berechtigungen. Dort können Sie ihn auch freischalten.\n\nBesten Dank! (Diese E-Mail wurde automatisch generiert.)";

if(!$email->Send()) {
	echo "Mailer Error: " . $email->ErrorInfo;
}
?>