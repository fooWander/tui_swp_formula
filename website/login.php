<?php 

/**
 * Logik für den Einlogvorgang auf der Webseite 
 */

include 'core/init.php';
logged_in_redirect();

if (empty($_POST) == false) {
	$mail = $_POST['mail'];
	$password = $_POST['pw'];
	
	if (empty($mail) || empty($password)) {
		$errors[] = 'Bitte geben Sie eine E-Mail-Adresse und ein Passwort an.';
	} else if (user_exists($mail) == false) {
		$errors[] = 'Es existiert kein Benutzer zu dieser E-Mail-Adresse. Haben Sie sich bereits registriert?';
	} else if (user_active($mail) == false) {
		$errors[] = 'Ihr Account wurde noch nicht aktiviert. Bitte haben Sie etwas Geduld oder setzen Sie sich mit dem Vorstand in Verbindung.';
	} else {
		$login = login($mail,$password);
		
		if ($login == false) {
			$errors[] = 'Ihre Eingabe ist inkorrekt. Bitte überprüfen Sie Ihre Login-Daten und versuchen Sie es erneut.';
		} else {
			$_SESSION['user_id'] = $login;
			$_SESSION['time'] = time();
			mysqli_select_db($connect,$dbname_ud);
			mysqli_query($connect, "INSERT INTO `" . $online . "` (`id`,`zeitpunkt`) VALUES (" . $_SESSION['user_id'] . "," . $_SESSION['time'] . ")");
			header('Location: index.php');
			exit();
		}
		
	}
	
} else {
	$errors[] = 'Keine Daten empfangen.';
}

include 'includes/overall/header.php';

if (empty($errors) == false) {
?>

<div class="content">
	<div class="single">
	<h2>Anmeldung fehlgeschlagen</h2>
	<?php echo output_errors($errors)?> 
	<br>
	<p><a href="index.php">Zurück zum Login</a></p>
	</div>
</div>

<?php
}
include 'includes/overall/footer.php'; 
?>