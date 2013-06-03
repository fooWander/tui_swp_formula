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
				<td><div id="lzeit">Laufzeit</div></td>
			</tr>
			<tr>
				<td> Akku Spannung </td>
				<td><div id="akku">Akku Spannung</div></td>
			</tr>
			<tr>
				<td> Status Notaus </td>
				<td><div id="statN">Status Notaus</div></td>
			</tr>
		</table>
	</div>
	
	<div class="item">	
		<table border='1' class='click'>
			<tr>
				<th colspan='2'> Temperatur und Gas </th>
			<tr>
				<td> Temperatur 1</td>
				<td><div id="temp01">Temperatur 01</div></td>
			</tr>
			<tr>
				<td> Temperatur 2</td>
				<td><div id="temp02">Temperatur 02</div></td>
			</tr>
			<tr>
				<td> Temperatur 3</td>
				<td><div id="temp03">Temperatur 03</div></td>
			</tr>
			<tr>
				<td> Gas 1</td>
				<td><div id="gas01">Gas 01</div></td>
			</tr>
			<tr>
				<td> Gas 2</td>
				<td><div id="gas02">Gas 02</div></td>
			</tr>	
		</table>
	</div>
</div>
	
	
<?php include 'includes/overall/footer.php';?>