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