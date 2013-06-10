<<<<<<< HEAD
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
				</ul>
			</form>
		</div>
	</div>
<?php
	} else {
?>
<!-- Hier ELSE-Inhalt -->
<?php
	}
	
include 'includes/overall/footer.php';
?>
=======
<?php include 'includes/overall/header.php'; ?>
	
	
	
	<!-- Laden der Akkudatentabelle (noch: CD-Tabelle) -->


	<!-- Contentbereich ANFANG -->
	
	
	
	<div class="content">	
		<div class="item">
			Index Motherfucker, do you read it?
		</div>
		
	</div>
	
		
	
	
<?php include 'includes/overall/footer.php';?>
>>>>>>> origin/webseite_david
