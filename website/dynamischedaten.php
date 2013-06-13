<?php
 include 'core/init.php';
 include 'includes/overall/header.php';
 protect_page();
?>	
<!-- Laden aus der SQL DB -->	
<script src="scripts/dynamischedaten_script.js"></script>

<!-- Contentbereich ANFANG -->
	
	
		
<div class="content">
	
	<div class="item">
		<div class="text_center">Lenkwinkel</div>
		<div id="lenkwinkel" class="text_center" >N/A</div>
		<div class="fhz_lenkwinkel" >				
			<script>
				for(i=0;i<181;i++ )
				{
					document.write("<div id='lenkwinkelid"+i+"' class='fhz_lenkindica2'></div>");
				};
			</script>
		</div>
		
		<div class="fhz_divline"></div>
		
		<div class="fhz_gaugediv">
			<div class="text_center">Drehzahl Vorderräder</div>
			<div id="vornelinks" class="gaugerpm"></div>
			<div id="vornerechts" class="gaugerpm"></div>
			<div class="text_center">Drehzahl Hinterräder</div>
			<div id="hintenlinks" class="gaugerpm"></div>
			<div id="hintenrechts" class="gaugerpm"></div>
		</div>	
		
		
		<div class="fhz_divline"></div>
		<div>
				
			<div class="text_center fhz_pedalround">Gaspedal 01</div>						
			<div class="fhz_pedal">				
				<script>
					for(i=0;i<20;i++ )
				{
					document.write("<div id='gaseinsid"+i+"' class='fhz_pedalindica'></div>");
				};
				</script>
			</div>
			<div id="gaspedal1" class="text_center fhz_pedalround2" >N/A</div>
		</div>
		
		<div>
			<div class="text_center fhz_pedalround">Gaspedal 02</div>			
			<div class="fhz_pedal" >				
				<script>
					for(i=0;i<20;i++ )
				{
					document.write("<div id='gaszweiid"+i+"' class='fhz_pedalindica'></div>");
				};
				</script>
			</div>
			<div id="gaspedal2" class="text_center fhz_pedalround2" >N/A</div>
		</div>
		<div>
			<div class="text_center fhz_pedalround">Bremsposition</div>			
			<div class="fhz_pedal" >				
				<script>
					for(i=0;i<20;i++ )
				{
					document.write("<div id='bremseid"+i+"' class='fhz_pedalindica'></div>");
				};
				</script>
			</div>
			<div id="bremsposition" class="text_center fhz_pedalround2" >N/A</div>
		</div>
		<div>
			<div class="text_center fhz_pedalround">Bremskraft</div>			
			<div class="fhz_pedal" >				
				<script>
					for(i=0;i<20;i++ )
				{
					document.write("<div id='bkraftid"+i+"' class='fhz_pedalindica'></div>");
				};
				</script>
			</div>
			<div id="bremskraft" class="text_center fhz_pedalround2" >N/A</div>
		</div>
		<div>
			<div class="text_center fhz_pedalround">Bremsdruck</div>			
			<div class="fhz_pedal" >				
				<script>
					for(i=0;i<20;i++ )
				{
					document.write("<div id='bdruckid"+i+"' class='fhz_pedalindica'></div>");
				};
				</script>
			</div>
			<div id="bremsdruck" class="text_center fhz_pedalround2" >N/A</div>
		</div>
		<div>
			<div class="text_center fhz_pedalround">Wassertemp. 1</div>			
			<div class="fhz_pedal" >				
				<script>
					for(i=0;i<20;i++ )
				{
					document.write("<div id='wtemp1id"+i+"' class='fhz_pedalindica'></div>");
				};
				</script>
			</div>
			<div id="wassertemp1" class="text_center fhz_pedalround2" >N/A</div>
		</div>
		<div>
			<div class="text_center fhz_pedalround">Wassertemp. 2</div>			
			<div class="fhz_pedal" >				
				<script>
					for(i=0;i<20;i++ )
				{
					document.write("<div id='wtemp2id"+i+"' class='fhz_pedalindica'></div>");
				};
				</script>
			</div>
			<div id="wassertemp2" class="text_center fhz_pedalround2" >N/A</div>
		</div>
		
	</div>
	
	<div class="item">
		<table border="1" class="click">
			<colgroup>
				<col>
				<col class="ddata">
				<col class="ddata">
				<col class="ddata">
			 </colgroup>
			<tr>
				<td>  </td>
				<td > X </td>
				<td > Y </td>
				<td > Z </td>
			</tr>
			<tr>
				<td> Geschwindigkeit (in km/h) </td>
				<td id="xGeschw">N/A </td>
				<td id="yGeschw">N/A </td>
				<td id="zGeschw">N/A </td>
			</tr>
			<tr>
				<td> Beschleunigung (in m/s&sup2) </td>
				<td id="xBeschl">N/A </td>
				<td id="yBeschl">N/A </td>
				<td id="zBeschl">N/A </td>
			</tr>
			<tr>
				<td> Gierrate (in °/s) </td>
				<td id="xGier">N/A </td>
				<td id="yGier">N/A </td>
				<td id="zGier">N/A </td>
			</tr>
		</table>
	</div>
	
	
	
	
	
	


	<div class="item">
		<div class="text_center">Federweg Vorderachse</div>
		<div id="federweg01" class="fhz_federmenu">N/A</div>
		<div class="fhz_feder">
			<script>
				for(i=9;i>=0;i--)
				{
					document.write("<div id='federvl"+i+"' class='fhz_federindi2' ></div>");
				};
			</script>
		</div>
		<div class="fhz_federmenu">links</div>
		<div class="fhz_federmenu">rechts</div>
		<div class="fhz_feder">
			<script>
				for(i=9;i>=0;i--)
				{
					document.write("<div id='federvr"+i+"' class='fhz_federindi2' ></div>");
				};
			</script>
		</div>
		<div id="federweg02" class="fhz_federmenu">N/A</div>	
		
		
		
		<div class="text_center">Federweg Hinterachse</div>
		<div id="federweg03" class="fhz_federmenu">N/A</div>
		<div class="fhz_feder">
			<script>
				for(i=9;i>=0;i--)
				{
					document.write("<div id='federhl"+i+"' class='fhz_federindi2' ></div>");
				};
			</script>
		</div>
		
		<div class="fhz_federmenu">links</div>
		<div class="fhz_federmenu">rechts</div>
			
		<div class="fhz_feder">
			<script>
				for(i=9;i>=0;i--)
				{
					document.write("<div id='federhr"+i+"' class='fhz_federindi2' ></div>");
				};
			</script>
		</div>
		<div id="federweg04" class="fhz_federmenu">N/A</div>
	<div>
	
	
	
	
</div>
	
		
	
	
<?php include 'includes/overall/footer.php';?>