<?php
	include 'core/init.php';
	include 'includes/overall/header.php';
	
	if (empty($_POST) == false) {
		// echo "<p>Ihre Registrierung wurde verschickt. Nachdem die Daten überprüft wurden erhalten Sie Zugang zum Service Interface.</p>";
		$datafields = array('vorname','nachname','mail','passwort','passwort_wdh');
		
		foreach ($_POST as $key => $value) {
			if (empty($value) && in_array($key, $datafields) == true) {
				$errors[] = 'Es müssen alle Felder für die Registrierung ausgefüllt werden.';
				break 1;
			}
			
			if (empty($errors)) {
				if (user_exists($_POST['mail'])) {
					$errors[] = 'Es existiert bereits ein Nutzer mit diesen Zugangsdaten.';
				}
				
				if (preg_match("/\\s/", $_POST['passwort']) == true ) {
					$errors[] = 'Ihr Passwort darf kein Leerzeichen enthalten.';
				}
				
				if (strlen($_POST['passwort']) < 6) {
					$errors[] = 'Ihr Passwort muss aus mindestens 6 Zeichen bestehen.';
				}
				
				if ($_POST['passwort'] != $_POST['passwort_wdh']) {
					$errors[] = 'Ihr Passwortwiederholung stimmt nicht mit dem zuerst angegebenen Passwort überein.';
				}
				
			}
			
		}
		
	}
	
?>
	<div class="content">
		<div class="item">
			<h2>Registrierung</h2>
			<p>Bitte füllen Sie für den Registriervorgang die nachfolgenden Formularfelder vollständig aus.</p>
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
						<input type="text" name="mail">
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
			<p class="hinweis"><?php if (!empty($errors)) { echo "<br>\n<p><strong>Achtung:</strong></p>\n" . output_errors($errors); } ?></p>
		</div>
	</div>
<?php	
include 'includes/overall/footer.php';
?>