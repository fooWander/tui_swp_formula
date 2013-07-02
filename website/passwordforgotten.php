<?php 
include 'core/init.php';
logged_in_redirect();
include 'includes/overall/header.php';
?>

<div class="content">
	<div class="single">
		<h1>Passwort Recovery</h1>
		
		<?php
		if (isset($_GET['success']) && empty($_GET['success'])) {
			?><p class="alert">Vorgang abgeschlossen. Bitte �berpr�fen Sie Ihr Mail-Postfach. Bitte �berpr�fen Sie auch Ihr Spampostfach.<br><a href="index.php">Zur�ck zum Login</a>!</p><?php
		} else {
		
			if (isset($_POST['email']) == true && empty($_POST['email']) == false) {
				if (user_exists($_POST['email'])) {
					recover($_POST['email']);
					header('Location: passwordforgotten.php?success');
					exit();
				} else {
					echo 'Es ist ein Fehler aufgetreten. Bitte �berpr�fen Sie Ihre Eingabe und versuchen es erneut.';
				}
			}	
			?>
			
			<form action="" method="post">
				<ul id="login">
					<li>
						Bitte geben Sie Ihre E-Mail-Adresse an:<br>
						<input type="text" name="email">
					</li>
					<li>
						<input type="submit" value="Passwort zur�cksetzen">
					</li>
				</ul>
			</form>
		<?php 
		}
		?>
	</div>
</div>

<?php include 'includes/overall/footer.php';?>