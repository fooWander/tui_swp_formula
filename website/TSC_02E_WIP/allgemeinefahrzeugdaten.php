<?php include 'includes/overall/header.php'; ?>

<!-- Laden aus der SQL DB -->
<script src="scripts/allgemeinefahrzeugdaten_script.js"></script>

<!-- Contentbereich ANFANG -->
	
		
<div class="content">
		
	<div class="item">
		Geschwindigkeit:
		<div id="geschw">Geschwindigkeit</div>
	</div>
	<div class="item">
		<div id="zeitp" >Zeitpunkt</div>
	</div>
	<div class="item">	
		<table border='1' class='click'>
			<tr>
				<th colspan='2'> Allgemein </th> 
			</tr>
			<tr>
				<td> Laufzeit </td>
				<td id="lzeit">Laufzeit</td>
			</tr>
			<tr>
				<td> Akku Spannung </td>
				<td id="akku">Akku Spannung</td>
			</tr>
		</table>	
		<table border='1' class='click'>	
			<tr>
				<th colspan='2'> Status Notaus </th>
			</tr>		
			<tr>
				<td>Notaus 1</td>
				<td id="statN0" class='status_aus'>offline</td>
			</tr>		
			<tr>
				<td>Notaus 2</td>
				<td id="statN1" class='status_aus'>offline</td>
			</tr>		
			<tr>
				<td>Notaus 3</td>
				<td id="statN2" class="status_aus">offline</td>
			</tr>		
			<tr>
				<td>Notaus 4</td>
				<td id="statN3" class="status_aus">offline</td>
			</tr>		
			<tr>
				<td>Notaus 5</td>
				<td id="statN4" class="status_aus">offline</td>
			</tr>		
			<tr>
				<td>Notaus 6</td>
				<td id="statN5" class="status_aus">offline</td>
			</tr>		
			<tr>
				<td>Notaus 7</td>
				<td id="statN6" class="status_aus">offline</td>
			</tr>		
			<tr>
				<td>Notaus 8</td>
				<td id="statN7" class="status_aus">offline</td>
			</tr>		
			<tr>
				<td>Notaus 9</td>
				<td id="statN8" class="status_aus">offline</td>
			</tr>		
			<tr>
				<td>Notaus 10</td>
				<td id="statN9" class="status_aus">offline</td>
			</tr>

		
		</table>
	</div>
	
	<div class="item">	
		<table border='1' class='click'>
			<tr>
				<th colspan='2'> Temperatur und Gas </th>
			<tr>
				<td> Temperatur 1</td>
				<td id="temp01">Temperatur 01</td>
			</tr>
			<tr>
				<td> Temperatur 2</td>
				<td id="temp02">Temperatur 02</td>
			</tr>
			<tr>
				<td> Temperatur 3</td>
				<td id="temp03">Temperatur 03</td>
			</tr>
			<tr>
				<td> Gas 1</td>
				<td id="gas01">Gas 01</td>
			</tr>
			<tr>
				<td> Gas 2</td>
				<td id="gas02">Gas 02</td>
			</tr>	
		</table>
	</div>
</div>
	
	
<?php include 'includes/overall/footer.php';?>