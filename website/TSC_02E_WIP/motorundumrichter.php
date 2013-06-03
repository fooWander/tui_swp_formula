<?php include 'includes/overall/header.php'; ?>
	
<!-- Laden der Daten aus der SQL DB -->
<script src="scripts/motorundumrichter_script.js"></script>

<!-- Contentbereich ANFANG -->
	
	
<div class="content">
	<div class="item">
		<table border="1" class="click">	
			<tr>
				<th colspan="2">Motor und Umrichter </th>
			</tr>
			<tr>
				<td>DCStrom</td>
				<td><div id="dcstrom">Strom<div></td>
			</tr>
			<tr>
				<td>DCSpannung</td>
				<td><div id="dcspannung">Spannung<div></td>
			</tr>
			<tr>
				<td>Motortemperatur 01</td>
				<td><div id="motortemp01">Temp 1<div></td>
			</tr>
			<tr>
				<td>Motortemperatur 02</td>
				<td><div id="motortemp02">Temp 2<div></td>
			</tr>
			<tr>
				<td>Motortemperatur 03</td>
				<td><div id="motortemp03">Temp 3<div></td>
			</tr>
			<tr>
				<td>Motortemperatur 04</td>
				<td><div id="motortemp04">Temp 4<div></td>
			</tr>
			<tr>
				<td>Motortemperatur 05</td>
				<td><div id="motortemp05">Temp 6<div></td>
			</tr>
			<tr>
				<td>Motortemperatur 06</td>
				<td><div id="motortemp06">Temp 6<div></td>
			</tr>
			<tr>
				<td>Motortemperatur 07</td>
				<td><div id="motortemp07">Temp 7<div></td>
			</tr>
			<tr>
				<td>Motortemperatur 08</td>
				<td><div id="motortemp08">Temp 8<div></td>
			</tr>
			<tr>
				<td>Stromgrenze</td>
				<td><div id="stromgrenze">Grenze<div></td>
			</tr>
			<tr>
				<td>Maximalleistung</td>
				<td><div id="maximalleistung">Leistung<div></td>
			</tr>
			<tr>
				<td>Lüfterdrehzahl</td>
				<td><div id="luefterdrehzahl">Drehzahl<div></td>
			</tr>
			<tr>
				<td>Lüfter</td>
				<td><div id="lüfter">Lüfter<div></td>
			</tr>
			<tr>
				<td>Pumpe</td>
				<td><div id="pumpe">Pumpe<div></td>
			</tr>
			<tr>
				<td>Wassertemperatur</td>
				<td><div id="wassertemp">Temperatur<div></td>
			</tr>
		</table>
	</div>
	
		
	<div class="item">
		<div id="zeitp">Zeitpunkt</div>
	</div>
</div>
	
	
<?php include 'includes/overall/footer.php';?>