<?php
	include 'core/init.php';
	include 'includes/overall/header.php';

	if(!logged_in()) {
	echo "<div class=\"content\">
		<form action=\"login.php\" method=\"post\">
			<ul id=\"login\">
				<li>
					E-Mail-Adresse:<br>
					<input type=\"text\" name=\"mail\">
				</li>
				<li>
					Passwort:<br>
					<input type=\"password\" name=\"pw\">
				</li>
				<li>
					<input type=\"submit\" value=\"Einloggen\">
				</li>
				<li>Jetzt <a href=\"register.php\">registrieren</a>!</li>
			</ul>
		</form>
	</div>";
	}
	
include 'includes/overall/footer.php';
?>