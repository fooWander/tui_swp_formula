<<<<<<< HEAD
	<header>
		<div><img src="logo.png" class="tsc-02e"></div>
		<?php 
		
		if(logged_in()) {
		?>		
		<nav>
			<ul>
				<li><a id="logout" href="logout.php">Ausloggen</a></li>
				<li><a id="test2" href="#" class="active">Motor und Umrichter</a></li>
				<li><a id="test2" href="#">Fahrdynamik</a></li>
				<li><a id="test2" href="#">Dynamische Daten</a></li>
				<li><a id="test1" href="#">Akkudaten</a></li>
				<li><a id="test2" href="#">Allgemeine Fahrzeugdaten</a></li>
			</ul>
		</nav>
		<?php
		} else {
		?>
		
		<?php 
		}
		?>		
	</header>
=======

<header>
	<div>
		<div><a href="index.php"><img src="logo.png" class="tsc-02e"></a></div>		
		<div class="nav-a"><a id="logout" href="#" class="nav_logout">Ausloggen</a></div>
		<div class="nav-a"><a id="motor_header" href="motorundumrichter.php" class="nav_inactive">Motor und Umrichter</a></div>
		<div class="nav-a"><a id="fahrdyn_header" href="fahrdynamik.php" class="nav_inactive">Fahrdynamik</a></div>
		<div class="nav-a"><a id="dyndata_header" href="dynamischedaten.php" class="nav_inactive">Dynamische Daten</a></div>
		<div class="nav-a"><a id="akkudaten_header" href="akkudaten.php" class="nav_inactive">Akkudaten</a></div>			
		<div class="nav-a"><a id="allgdata_header" href="allgemeinefahrzeugdaten.php" class="nav_inactive">Allgemeine Fahrzeugdaten</a></div>		
	</div>
</header>
>>>>>>> origin/webseite_david
