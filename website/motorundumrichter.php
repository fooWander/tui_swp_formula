<?php
 include 'core/init.php';
 include 'includes/overall/header.php';
 protect_page();
?>	
<!-- Laden der Daten aus der SQL DB -->
<script src="scripts/motorundumrichter_script.js"></script>

<!-- Contentbereich ANFANG -->
	
	
<div class="content">

	<div class="single">
		<div class="moto_div">
			<div class="top akkubig" id="dcstrom">N/A</div> 
			<div class="top akkusmall" >DC Strom</div> 
		</div>
		<div class="akku_divline"></div>
		<div class="moto_div">
			<div class="top akkubig" id="dcspannung">N/A</div>	
			<div class="top akkusmall" >DC Spannung</div>	
		</div>				
		<div class="akku_divline"></div>
		<div class="moto_div">	
			<div class="top akkubig" id="stromgrenze">N/A</div>	
			<div class="top akkusmall" >Stromgrenze</div> 
		</div>
		<div class="akku_divline"></div>			
		<div class="moto_div">
			<div class="top akkubig" id="maximalleistung">N/A</div>
			<div class="top akkusmall" >Maximalleistung</div>
		</div>
	</div>
	
	<div class="single">
		<div class="moto_div">
			<div class="top akkubig" id="lüfter">N/A</div>	
			<div class="top akkusmall" >Lüfter</div>	
		</div>				
		<div class="akku_divline"></div>
		<div class="moto_div">
			<div class="top akkubig" id="lüfterdrehzahl">N/A</div> 
			<div class="top akkusmall" >Lüfterdrehzahl</div> 
		</div>
		<div class="akku_divline"></div>
		<div class="moto_div">	
			<div class="top akkubig" id="pumpe">N/A</div>	
			<div class="top akkusmall" >Pumpe</div> 
		</div>
		<div class="akku_divline"></div>			
		<div class="moto_div">
			<div class="top akkubig" id="wassertemp">N/A</div>
			<div class="top akkusmall" >Wassertemperatur</div>
		</div>
	</div>

	
	<div class="akkuitem">
		<table border="1" class="click">
			<colgroup>
				<col class="moto_temp">
				<col class="moto_temp">
				<col class="moto_temp">
				<col class="moto_temp">
				<col class="moto_temp">
				<col class="moto_temp">
				<col class="moto_temp">
				<col class="moto_temp">
			<colgroup>
			<tr>
				<th colspan="8"> Motortemperatur</th>
			</tr>
			<tr>
				<td>#01</td>
				<td>#02</td>
				<td>#03</td>
				<td>#04</td>
				<td>#05</td>
				<td>#06</td>
				<td>#07</td>
				<td>#08</td>

			</tr>
			<tr>
				<td><div id="motortemp01">N/A<div></td>
				<td><div id="motortemp02">N/A<div></td>
				<td><div id="motortemp03">N/A<div></td>
				<td><div id="motortemp04">N/A<div></td>
				<td><div id="motortemp05">N/A<div></td>
				<td><div id="motortemp06">N/A<div></td>
				<td><div id="motortemp07">N/A<div></td>
				<td><div id="motortemp08">N/A<div></td>
			</tr>
		</table>
	</div>
</div>
	
	
<?php include 'includes/overall/footer.php';?>