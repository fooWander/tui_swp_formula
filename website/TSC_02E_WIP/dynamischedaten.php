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
				<td> Geschwindigkeit </td>
				<td> <div id="xGeschw">X Wert</div> </td>
				<td> <div id="yGeschw">Y Wert</div> </td>
				<td> <div id="zGeschw">Z Wert</div> </td>
			</tr>
			<tr>
				<td> Beschleunigung  </td>
				<td> <div id="xBeschl">X Wert</div> </td>
				<td> <div id="yBeschl">Y Wert</div> </td>
				<td> <div id="zBeschl">Z Wert</div> </td>
			</tr>
			<tr>
				<td> Gierrate </td>
				<td> <div id="xGier">X Wert</div> </td>
				<td> <div id="yGier">Y Wert</div> </td>
				<td> <div id="zGier">Z Wert</div> </td>
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
				<td> <div id="vrl">VRL</div> </td>
				<td> <div id="vrr">VRR</div> </td>
				<td> Vorderrad rechts </td>
			</tr>
			<tr>
				<td> Hinterrad links </td>
				<td> <div id="hrl">HRL</div> </td>
				<td> <div id="hrr">HRR</div> </td>
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
				<td> <div id="lenkwinkel">Stellung</div></td>
			</tr>
			<tr>
				<td> Gaspedal</td>
				<td> <div id="gaspedal">Stellung</div></td>
			</tr>
			<tr>
				<td> Bremsposition</td>
				<td> <div id="bremsposition">Position</div></td>
			</tr>
			<tr>
				<td> Bremskraft</td>
				<td> <div id="bremskraft">Kraft</div></td>
			</tr>
			<tr>
				<td> Bremsdruck</td>
				<td> <div id="bremsdruck">Druck</div></td>
			</tr>
			<tr>
				<td> Federweg</td>
				<td> <div id="federweg">Weg</div></td>
			</tr>
			<tr>
				<td> Wassertemperatur 1</td>
				<td> <div id="wassertemp01">Temp</div></td>
			</tr>
			<tr>
				<td> Wassertemperatur 2</td>
				<td> <div id="wassertemp02">Temp</div></td>
			</tr>
		</table>
	</div>
		
		
</div>
	
		
	
	
<?php include 'includes/overall/footer.php';?>