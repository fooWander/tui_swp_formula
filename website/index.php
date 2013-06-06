<?php
	include 'core/init.php';
	include 'includes/overall/header.php';
	
	if(!logged_in()) {
?>
	<div class="content">
		<div class="item">
			<h1>Service Interface Login</h1>
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
	}
	
include 'includes/overall/footer.php';
?>