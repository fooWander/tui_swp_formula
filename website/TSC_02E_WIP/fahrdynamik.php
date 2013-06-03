<?php include 'includes/overall/header.php'; ?>
	
<!-- Laden der Daten aus der SQL DB -->
<script src="scripts/fahrdynamik_script.js"></script>

<!-- Contentbereich ANFANG -->
	
	
	
<div class="content">
	<div class="item">
		<table border="1" class="click">
			<tr>
			<th colspan="2"> Fahrdynamik </th>
			</tr>
			<tr>
				<td>Antriebsschlupfregelung</td>
				<td><div id="antrieb">Schlupf</div></td>
			</tr>
			<tr>
				<td>Torque Vectoring 1</td>
				<td><div id="tvec1"> tvec1</div></td>
			</tr>
			<tr>
				<td>Torque Vectoring 2</td>
				<td><div id="tvec2"> tvec2</div></td>
			</tr>
			<tr>
				<td>Torque Vectoring 3</td>
				<td><div id="tvec3"> tvec3</div></td>
			</tr>
			<tr>
				<td>Lenkwinkel</td>
				<td><div id="lenkwinkel"> Winkel</div></td>
			</tr>
		</table>
	</div>
		
	<div class="item">
		<div id="Zeitp">Zeitpunkt</div>
	</div>
</div>
		
	
<?php include 'includes/overall/footer.php';?>