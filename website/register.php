<?php
	/**
	 * Durchf�hrung des Registriervorgangs, mit Entnehmen der Nutzerdaten und Eintragen der Werte in die Nutzer-Tabelle in der Datenbank.
	 */
	include 'core/init.php';
	include 'includes/overall/header.php';
	logged_in_redirect();
	
	/**
	 * �berpr�fung der Vollst�ndigkeit der eingegebenen Daten und gleichzeitige Validierung ebendieser
	 */
	if (empty($_POST) == false) {
		$datafields = array('vorname','nachname','email','passwort','passwort_wdh');
		
		foreach ($_POST as $key => $value) {
			if (empty($value) && in_array($key, $datafields) == true) {
				$errors[] = 'Es m�ssen alle Felder f�r die Registrierung ausgef�llt werden.';
				break 1;
			}
			
			if (empty($errors)) {
				
				if (user_exists($_POST['email'])) {
					$errors[] = 'Es existiert bereits ein Nutzer zu dieser E-Mail-Adresse.';
				}
				
				if (preg_match("/\\s/", $_POST['passwort']) == true ) {
					$errors[] = 'Ihr Passwort darf kein Leerzeichen enthalten.';
				}
				
				if (strlen($_POST['passwort']) < 6) {
					$errors[] = 'Ihr Passwort muss aus mindestens 6 Zeichen bestehen.';
				}
				
				if ($_POST['passwort'] != $_POST['passwort_wdh']) {
					$errors[] = 'Ihr Passwortwiederholung stimmt nicht mit dem zuerst angegebenen Passwort �berein.';
				}
				
				if (filter_var($_POST['email'], FILTER_VALIDATE_EMAIL) == false) {
					$errors[] = 'Bitte geben Sie eine g�ltige E-Mail-Adresse an.';
				}
				
			}
			
		}
		
	}
	
?>
	<div class="content">
		<div class="single">
			<h2>Registrierung</h2>
			<?php
			
			/**
			 * Benachrichtigung �ber erfolgreiche Registrierung.
			 */
			if (!isset($_GET['success'])) {
				echo '<p><center>Bitte f�llen Sie f�r den Registriervorgang die nachfolgenden Formularfelder vollst�ndig aus.</center></p>';
			}			
			
			/**
			 * Registrierung bereits verschickt?
			 */
			if (isset($_GET['success']) && empty($_GET['success'])) {
				echo '<p><center>Ihre Registrierung wurde verschickt. Nachdem die Daten �berpr�ft wurden, erhalten Sie Zugang zum Service Interface.</center></p>';
			} else {	
		
				/**
				 * Registrierung des Nutzers mit den angegeben Daten
				 */
				if (!empty($_POST) && empty($errors)) {
	
					$register_data = array(
							'vorname' 	=> $_POST['vorname'],
							'nachname' 	=> $_POST['nachname'],
							'email' 	=> $_POST['email'],
							'passwort' 	=> $_POST['passwort']
					);
					register_user($register_data);
					header('Location: register.php?success');
					exit();
					
				} else if (empty($errors) == false) {
			?>
			<p class="hinweis"><br><center><?php echo output_errors($errors); ?></center></p>
			<?php
				}
			?>
			<form action="" method="post">
				<ul id="login">
					<li>
						Vorname:<br>
						<input type="text" name="vorname">
					</li>
					<li>
						Nachname:<br>
						<input type="text" name="nachname">
					</li>
					<li>
						E-Mail-Adresse:<br>
						<input type="text" name="email">
					</li>								
					<li>
						Passwort:<br>
						<input type="password" name="passwort">
					</li>
					<li>
						Passwort (Wiederholung):<br>
						<input type="password" name="passwort_wdh">
					</li>				
					<li>
						<input type="submit" value="Registrierung abschicken">
					</li>
				</ul>
			</form>
		</div>
	</div>
<?php	
}
include 'includes/overall/footer.php';
?>