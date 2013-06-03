<?php 
include 'core/init.php';

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
			header('Location: index.php');
			exit();
		}
		
	}
	
} else {
	$errors[] = 'Keine Daten empfangen.';
}

include 'includes/overall/header.php';

?>

<div class="content">
	<div class="item">
	<?php echo output_errors($errors)?> 
	</div>
</div>

<?php
include 'includes/overall/footer.php'; 
?>