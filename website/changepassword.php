<?php 
	/**
	 * Logik zum �ndern des eigenen Passworts
	 */
	include 'core/init.php';
	protect_page();
	include 'includes/overall/header.php';
	
	/**
	 * Zwischenspeichern der Formularfeld-Inhalte und �berpr�fen auf Validit�t und Vollst�ndigkeit, sowie Korrektheit des zu �ndernden Passwortes
	 */
	if (empty($_POST) == false) {
		$datafields = array('altes_passwort','passwort','passwort_wdh');
	
	foreach ($_POST as $key => $value) {
		if (empty($value) && in_array($key, $datafields) == true) {
			$errors[] = 'Es m�ssen alle Felder f�r die Registrierung ausgef�llt werden.';
			break 1;
		}
	}
	
	if (md5($_POST['altes_passwort']) == $user_data['passwort']) {
		if (trim($_POST['passwort']) != trim($_POST['passwort_wdh'])) {
			$errors[] = 'Ihr neues Passwort und dessen Wiederholung stimmen nicht �berein.';
		} else if (strlen($_POST['passwort']) < 6) {
			$errors[] = 'Ihr neues Passwort muss aus mindestens 6 Zeichen bestehen.';
		}
	} else {
		$errors[] = 'Das eingegebene Passwort ist inkorrekt.';
	}
	}	
?>
	<div class="content">
		<div class="single">
		<h2>Passwort �ndern</h2>
		
		<?php 
			/**
			 * Benachrichtigung �ber erfolgreiche Registrierung.
			 */
			if (isset($_GET['success'])) {
				echo '<p><center>Ihr Passwort wurde erfolgreich ge�ndert.</center></p>';
			} else {			
			
				/**
				 * Nach korrekter �bermittlung der Daten, Ausgabe einer Feedbackmeldung
				 */
				if (!empty($_POST) && empty($errors)) {
					change_password($session_user_id, $_POST['passwort']);
					header('Location: changepassword.php?success');
				} else if (!empty($errors)) {
					echo output_errors($errors);
				}
		?>
		
			<form action="" method="post">
				<ul id="login">
					<li>
						Altes Passwort:<br>
						<input type="password" name="altes_passwort">
					</li>
					<li>
						Neues Passwort:<br>
						<input type="password" name="passwort">		
					</li>
					<li>
						Neues Passwort (Wiederholung):<br>
						<input type="password" name="passwort_wdh">		
					</li>
					<li>
						<input type="submit" value="Passwort �ndern" class="submit">
					</li>
				</ul>
			</form>
		</div>
	</div>
<?php
	}
	include 'includes/overall/footer.php';
?>