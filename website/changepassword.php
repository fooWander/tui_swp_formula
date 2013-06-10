<?php 
	include 'core/init.php';
	protect_page();
	include 'includes/overall/header.php';
	
	if (empty($_POST) == false) {
		$datafields = array('altes_passwort','passwort','passwort_wdh');
	}
	
	foreach ($_POST as $key => $value) {
		if (empty($value) && in_array($key, $datafields) == true) {
			$errors[] = 'Es müssen alle Felder für die Registrierung ausgefüllt werden.';
			break 1;
		}
	}
	
	if (md5($_POST['passwort']) == $user_data['passwort']) {
		if (trim($_POST['passwort']) == trim($_POST['passwort_wdh'])) {
			
		}
	} else {
		$errors = 'Das eingegebene Passwort ist inkorrekt.';
	}
	
?>
	<div class="content">
		<div class="single">
		<h2>Passwort ändern</h1>
			<form action="" method="post">
				<ul>
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
						<input type="submit" value="Passwort ändern">
					</li>
				</ul>
			</form>
		</div>
	</div>
<?php include 'includes/overall/footer.php';?>