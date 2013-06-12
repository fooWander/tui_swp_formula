<?php
protect_page();
?>	

<div class="content">
	<div class ="item">
		<h2>CSV Export</h2>
		<p class="alert_short">Hinweis: Die Datei muss im Programm ihrer Wahl importiert 
		werden um korrekt angezeigt zu werden!</p><br>
		<form id="login" action="core/functions/csvexp_sql.php" method="post" accept-charset="utf-8">
			<ul>
				<li>
					<p>alle Fahrzeugdaten</p> <input type="checkbox" name="alledaten" value="true">
				</li>
				<div class="fhz_divline"></div>
				<li>
					<p>Allgemeine Daten</p> <input type="checkbox" name="choice1" value="true">
				</li>
				<li>
					<p>Akkudaten</p> <input type="checkbox" name="choice2" value="true">
				</li>
				<li>
					<p>Dynamische Daten</p> <input type="checkbox" name="choice3" value="true">
				</li>								
				<li>
					<p>Fahrdynamik</p> <input type="checkbox" name="choice4" value="true">
				</li>
				<li>
					<p>Motor und Umrichter</p> <input type="checkbox" name="choice5" value="true">
				</li>				
				<li>
					<input type="submit" id="submitcsv" value="als .csv exportieren">
				</li>
			</ul>
		</form>
	</div>
