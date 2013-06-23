<?php
require 'includes/phpmailer/class.phpmailer.php';

$mail = new PHPMailer;

$mail->IsSMTP();                                      // Set mailer to use SMTP
$mail->Host = 's16929463.onlinehome-server.info';  // Specify main and backup server
$mail->SMTPAuth = true;                               // Enable SMTP authentication
$mail->Username = 'Telemetrie@s16929463.onlinehome-server.info';                            // SMTP username
$mail->Password = 'e]jm&fNJz9';                           // SMTP password
$mail->SMTPSecure = 'tls';                            // Enable encryption, 'ssl' also accepted

$mail->From = 'noreply@teamstarcraft.de';
$mail->FromName = 'Team Starcraft e. V.';
$mail->AddAddress('thomas.golda@tu-ilmenau.de');  // Add a recipient
$mail->AddCC('thomas.golda@tu-ilmenau.de');

$mail->WordWrap = 50;                                 // Set word wrap to 50 characters
$mail->IsHTML(true);                                  // Set email format to HTML

$mail->Subject = 'Neue Registrierung im Service Interface';
$mail->Body    = 'Sehr geehrter Vorstand,<br><br>ein neuer Benutzer hat sich im System registriert. Bitte loggen Sie sich im Service Interface ein und überprüfen Sie seine Berechtigungen. Dort können Sie ihn auch freischalten.<br><br>Besten Dank!<br><br>(Diese E-Mail wurde automatisch generiert.)';
$mail->AltBody = 'Sehr geehrter Vorstand, ein neuer Benutzer hat sich im System registriert. Bitte loggen Sie sich im Service Interface ein und überprüfen Sie seine Berechtigungen. Dort können Sie ihn auch freischalten. Besten Dank! (Diese E-Mail wurde automatisch generiert.)';
?>