<header>
	<div><img src="logo.png" class="tsc-02e"></div>
	<?php 
	/**
	 * Falls eingeloggt, Einblenden des Auswahlmenüs, andernfalls Ausblenden. 
	 */
	if(logged_in()) {
	refresh();
	?>
	<nav>
		<ul>
			<li><a id="logout" href="logout.php">Ausloggen</a></li>
			<li><a id="motor_header" href="motorundumrichter.php" class="inactive">Motor und Umrichter</a></li>
			<li><a id="fahrdyn_header" href="fahrdynamik.php" class="inactive">Fahrdynamik</a></li>
			<li><a id="dyndata_header" href="dynamischedaten.php" class="inactive">Dynamische Daten</a></li>
			<li><a id="akkudaten_header" href="akkudaten.php" class="inactive">Akkudaten</a></li>	
			<li><a id="allgdata_header" href="allgemeinefahrzeugdaten.php" class="inactive">Allgemeine Fahrzeugdaten</a></li>
		</ul>
	</nav>
	<?php
		} else {
	?>
	<!-- Menü -->
	<?php 
	}
	?>	
</header>
<?php
if (logged_in()) {
	include 'includes/widgets/loggedin.php';
}
?>