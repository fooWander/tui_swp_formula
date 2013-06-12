<?php
/**
 * Testumgebung um Funktionen mit vorhandenem Layout auszuprobieren
 */
	include 'core/init.php';
	include 'includes/overall/header.php';	
?>
	<div class="content">
		<div class="single">
			<h2>Sandbox</h2>
			<form action="" method="post">
				<input type="text" name="text">
				<input type="submit" value="abschicken"><br><br>Ausgabe: 
				<?php
					if(isset($_POST['text'])) {
						echo htmlspecialchars($_POST['text'], ENT_QUOTES);
						echo "<br>";
						echo crypt($_POST['text'], 'tuilmenaufakia');
					}
				?>
			</form>
		</div>
	</div>
<?php	
include 'includes/overall/footer.php';
?>