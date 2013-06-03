	<header>
		<div><img src="logo.png" class="tsc-02e"></div>
		<?php 
		
		if(logged_in()) {		
			echo "<nav>\n
					<ul>\n
						<li><a id=\"logout\" href=\"logout.php\">Ausloggen</a></li>\n
						<li><a id=\"test2\" href=\"#\" class=\"active\">Motor und Umrichter</a></li>\n
						<li><a id=\"test2\" href=\"#\">Fahrdynamik</a></li>\n
						<li><a id=\"test2\" href=\"#\">Dynamische Daten</a></li>\n
						<li><a id=\"test1\" href=\"#\">Akkudaten</a></li>\n	
						<li><a id=\"test2\" href=\"#\">Allgemeine Fahrzeugdaten</a></li>\n
					</ul>\n
				</nav>\n";
		}
		
		?>		
	</header>