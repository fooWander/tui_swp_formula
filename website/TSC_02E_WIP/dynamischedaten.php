<?php include 'includes/overall/header.php'; ?>
	
<!-- Laden aus der SQL DB -->	
<script src="scripts/dynamischedaten_script.js"></script>

<!-- Contentbereich ANFANG -->
	
	
		
<div class="content">
	<div class="item">
		<table border="1" class="click">
			<tr>
				<td>  </td>
				<td> X </td>
				<td> Y </td>
				<td> Z </td>
			</tr>
			<tr>
				<td> Geschwindigkeit (in km/h) </td>
				<td id="xGeschw">X Wert </td>
				<td id="yGeschw">Y Wert </td>
				<td id="zGeschw">Z Wert </td>
			</tr>
			<tr>
				<td> Beschleunigung (in m/s&sup2) </td>
				<td id="xBeschl">X Wert </td>
				<td id="yBeschl">Y Wert </td>
				<td id="zBeschl">Z Wert </td>
			</tr>
			<tr>
				<td> Gierrate (in °/s) </td>
				<td id="xGier">X Wert </td>
				<td id="yGier">Y Wert </td>
				<td id="zGier">Z Wert </td>
			</tr>
		</table>
	</div>
	
	<div class="item">
		<div id="zeitp">Zeitpunkt</div>
	</div>
	
	<div class="item">
		<table border="1" class="click">
			<tr>
				<th colspan="4">Drehzahl</th>
			</tr>
			<tr>
				<td> Vorderrad links </td>
				<td> <div id="vrl">VRL </td>
				<td> <div id="vrr">VRR </td>
				<td> Vorderrad rechts </td>
			</tr>
			<tr>
				<td> Hinterrad links </td>
				<td id="hrl">HRL </td>
				<td id="hrr">HRR </td>
				<td> Hinterrad rechts </td>
			</tr>
		</table>
	</div>
	
	<div class="item">
		<table border="1" class="click" >
			<tr>
				<th colspan="2">Übersicht</th>
			</tr>
			<tr>
				<td> Lenkwinkel</td>
				<td id="lenkwinkel">Stellung</td>
			</tr>
			<tr>
				<td> Gaspedal</td>
				<td id="gaspedal">Stellung</td>
			</tr>
			<tr>
				<td> Bremsposition</td>
				<td id="bremsposition">Position</td>
			</tr>
			<tr>
				<td> Bremskraft</td>
				<td id="bremskraft">Kraft</td>
			</tr>
			<tr>
				<td> Bremsdruck</td>
				<td id="bremsdruck">Druck</td>
			</tr>
			<tr>
				<td> Federweg</td>
				<td id="federweg">Weg</td>
			</tr>
			<tr>
				<td> Wassertemperatur 1</td>
				<td id="wassertemp01">Temp</td>
			</tr>
			<tr>
				<td> Wassertemperatur 2</td>
				<td id="wassertemp02">Temp</td>
			</tr>
		</table>
	</div>
		
		
</div>
	
		
	
	
<?php include 'includes/overall/footer.php';?>