<?php 
/**
 * Widget zur Darstellung eines Benutzerbalkens, der Informationen �ber den aktuellen Account
 * ausgibt, sowie Links zur Verf�gung stellt, die nichts mit dem Fahrzeug zu tun haben.
 */
?>
<div class="verwaltung">
	Sie sind eingeloggt, als <?php echo $user_data['vorname'] . " " . $user_data['nachname'] ?>!
	<div><a href="index.php">Benutzerverwaltung</a></div>
	<div>|</div>
	<div><a href="changepassword.php">Passwort �ndern</a></div>
</div>