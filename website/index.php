<?php
	include 'core/init.php';
	include 'includes/overall/header.php';
	
	if(!logged_in()) {
?>
	<div class="content">
		<div class="single">
			<h1>Service Interface Login</h1>
			<?php 
			if (isset($_GET['denied']) && empty($_GET['denied'])) { ?>
				<p class="alert">Sie haben keine Berechtigung diese Seite anzeigen zu lassen. Bitte loggen Sie sich ein oder registrieren Sie sich.</p>
			<?php
			}
			?>
			<form action="login.php" method="post">
				<ul id="login">
					<li>
						E-Mail-Adresse:<br>
						<input type="text" name="mail">
					</li>
					<li>
						Passwort:<br>
						<input type="password" name="pw">
					</li>
					<li>
						<input type="submit" value="Einloggen">
					</li>
					<li>Jetzt <a href="register.php">registrieren</a>!</li>
					<li><a href="passwordforgotten.php">Passwort vergessen</a>?</li>
				</ul>
			</form>
		</div>
	</div>
<?php
	} else {
?>
	<div class="content">
		<?php
		// Einbinden der unterschiedlichen Widgets wie Online-Nutzerliste oder CSV-Export und setzen einer globalen Konstante zum Schutz der Widgets vor unbefugtem äußeren Zugriff
		define('ACCESS',"Pickachu");
		if(isVorstand()) {include 'includes/widgets/userlist.php';}
		include 'includes/widgets/csvexp.php';
		include 'includes/widgets/onlineusers.php';
		if(isVorstand()) {include 'includes/widgets/manageusers.php';}
		?>
	</div>
<?php
	}
include 'includes/overall/footer.php';
?>