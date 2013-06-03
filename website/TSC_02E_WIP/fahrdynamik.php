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
				<td id="antrieb">Schlupf</td>
			</tr>
			<tr>
				<td>Torque Vectoring 1</td>
				<td id="tvec1"> tvec1</td>
			</tr>
			<tr>
				<td>Torque Vectoring 2</td>
				<td id="tvec2"> tvec2</td>
			</tr>
			<tr>
				<td>Torque Vectoring 3</td>
				<td id="tvec3"> tvec3</td>
			</tr>
			<tr>
				<td>Lenkwinkel</td>
				<td id="lenkwinkel"> Winkel</td>
			</tr>
		</table>
	</div>
		
	<div class="item">
		<div id="Zeitp">Zeitpunkt</div>
	</div>
</div>
		
	
<?php include 'includes/overall/footer.php';?>