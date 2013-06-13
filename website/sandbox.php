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
					$timestamp = 1371052734;
					if(isset($_POST['text'])) {
						echo strlen($_POST['text']);
						echo "<br>";
						echo uniqid();
						//echo crypt($_POST['text'], 'tuilmenaufakia');
					}
					echo "<br>";
					//if ((time() - $timestamp) < (7	*60)) {
					//	echo "Alles im Grünen bereich: " . (time() - $timestamp);
					//} else {
					//	echo "Timout, Zeitstempel veraltet. (d.h. mehr als sieben Minuten verstrichen): " . (time() - $timestamp) . " " . time();
					//}
					

					$Password = $_POST['text'];
					
					$HashedPassword = crypt($Password, $cryptsalt);
					echo "<br>Hash: " . $HashedPassword . "\n";
				?>
			</form>
		</div>
	</div>
<?php	
include 'includes/overall/footer.php';
?>