<?php 

/* Diese Datei dient der Initialisierung des Systems von Seiten des
 * Webservers. Bitte l�schen Sie diese Datei im Anschluss an die erst-
 * malige Einrichtung des Webservers um ungewolltes Verhalten der Soft-
 * ware zu vermeiden.
 */

include 'core/init.php';
include 'includes/overall/header.php';
include 'includes/config.php';
?>
	
	<div class="content">
		<div class="single">		

		<?php 
		
		/**
		 * �berpr�fung der Vollst�ndigkeit der eingegebenen Daten und gleichzeitige Validierung ebendieser
		 * f�r die Erstellung des Admin-Accounts
		 */
		if (empty($_POST) == false) {
			$datafields = array('vorname','nachname','email','passwort','passwort_wdh');
			
			foreach ($_POST as $key => $value) {
				if (empty($value) && in_array($key, $datafields) == true) {
					$errors[] = 'Es m�ssen alle Felder f�r die Registrierung ausgef�llt werden.';
					break 1;
				}
				
				if (empty($errors)) {
					
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
		
		?>
		<br>
		Sollte die Installierung fehlerfrei abgelaufen sein, k�nnen Sie die Datei 'install.php' nun vom Server l�schen und die Seite �ber die Datei 'index.php' aufrufen.

<?php
		}
?>

			<h2>Einrichtung des Vorstand-Accounts</h2>
			<?php			

			/**
			 * Registrierung des Nutzers mit den angegeben Daten
			 */
			if (!empty($_POST) && empty($errors)) {

				$register_data = array(
						'email' 	=> $_POST['email'],
						'vorname' 	=> $_POST['vorname'],
						'nachname' 	=> $_POST['nachname'],
						'passwort' 	=> $_POST['passwort']
				);
				install_system($register_data);
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
						<input type="submit" value="Einrichtung ausf�hren">
					</li>
				</ul>
			</form>
		</div>
	</div>
<?php include 'includes/overall/footer.php'; ?>