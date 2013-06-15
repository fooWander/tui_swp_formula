<?php
 include 'core/init.php';
 include 'includes/overall/header.php';
 protect_page();
?>	

<!-- Laden aus der SQL DB -->
<script src="scripts/allgemeinefahrzeugdaten_script.js"></script>

<!-- Contentbereich ANFANG -->
	
		
<div class="content">

	<div class="single">
		<div class="fhz_div">
			<div class="top akkubig" id="lzeit">N/A</div> 
			<div class="top akkusmall" >Laufzeit</div> 
		</div>
		<div class="akku_divline"></div>
		<div class="fhz_div">
			<div class="top akkubig" id="akku">N/A</div>	
			<div class="top akkusmall" >Akku Spannung</div>	
		</div>				
		<div class="akku_divline"></div>
		<div class="fhz_div">	
			<div class="top akkubig" id="gas01">N/A</div>	
			<div class="top akkusmall" >Gas 1</div> 
		</div>
		<div class="akku_divline"></div>			
		<div class="fhz_div">
			<div class="top akkubig" id="gas02">N/A</div>
			<div class="top akkusmall" >Gas 2</div>
		</div>
	</div>
	<div class="single">
		<div class="fhz_div2">
			<div class="top akkubig" id="temp01">N/A</div>
			<div class="top akkusmall" >Temperatur 1</div>
		</div>
		<div class="akku_divline"></div>			
		<div class="fhz_div2">
			<div class="top akkubig" id="temp02">N/A</div>
			<div class="top akkusmall" >Temperatur 2</div>
		</div>
		<div class="akku_divline"></div>			
		<div class="fhz_div2">
			<div class="top akkubig" id="temp03">N/A</div>
			<div class="top akkusmall" >Temperatur 3</div>
		</div>
	</div>

	<div class="allitem" >		
		<div id="geschwindigkeit" class="gauge1"></div>
	</div>	
	
	<div class="allitem">
		<table border='1' class='click'>
			<colgroup>
				<col>
				<col class="notaus">
			 </colgroup>
			<tr>
				<th colspan="2"> Status Notaus </th>
			</tr>		
			<tr>
				<td>Notaus 1</td>
				<td id="statN0" class='status_aus'>N/A</td>
			</tr>		
			<tr>
				<td>Notaus 2</td>
				<td id="statN1" class='status_aus'>N/A</td>
			</tr>		
			<tr>
				<td>Notaus 3</td>
				<td id="statN2" class="status_aus">N/A</td>
			</tr>		
			<tr>
				<td>Notaus 4</td>
				<td id="statN3" class="status_aus">N/A</td>
			</tr>		
			<tr>
				<td>Notaus 5</td>
				<td id="statN4" class="status_aus">N/A</td>
			</tr>		
			<tr>
				<td>Notaus 6</td>
				<td id="statN5" class="status_aus">N/A</td>
			</tr>		
			<tr>
				<td>Notaus 7</td>
				<td id="statN6" class="status_aus">N/A</td>
			</tr>		
			<tr>
				<td>Notaus 8</td>
				<td id="statN7" class="status_aus">N/A</td>
			</tr>		
			<tr>
				<td>Notaus 9</td>
				<td id="statN8" class="status_aus">N/A</td>
			</tr>		
			<tr>
				<td>Notaus 10</td>
				<td id="statN9" class="status_aus">N/A</td>
			</tr>
		
		</table>
	</div>
	
	
	
</div>
	
	
<?php include 'includes/overall/footer.php';?>