<?php
 include 'core/init.php';
 include 'includes/overall/header.php';
 protect_page();
?>	

	
<!-- Laden der Daten aus der SQL DB -->
<script src="scripts/akkudaten_script.js"></script>

<!-- Contentbereich ANFANG -->


	
<div class="content">
	
	<div class="single">
		
		<div class="akku_div">
			<div class="top akkubig" id="min_spg" >N/A</div> 
			<div class="top akkusmall" >Minimale Zellspannung</div> 
		</div>
		<div class="akku_divline"></div>
		<div class="akku_div">
			<div class="top akkubig" id="max_spg">N/A</div>	
			<div class="top akkusmall" >Maximale Zellspannung</div>	
		</div>				
		<div class="akku_divline"></div>
		<div class="akku_div">	
			<div class="top akkubig" id="ges_spg">N/A</div>	
			<div class="top akkusmall" >Gesamtspannung</div> 
		</div>
		<div class="akku_divline"></div>			
		<div class="akku_div">
			<div class="top akkubig" id="lade_strom">N/A</div>
			<div class="top akkusmall" >Strom Ladegerät</div>
		</div>
		<div class="akku_divline"></div>		
		<div class="akku_div">		
			<div class="top akkubig" id="lade_spg">N/A</div>
			<div class="top akkusmall" >Spannung Ladegerät</div>
		</div>
	</div>
	

	<div class="akkuitem">
		<table border='1' class='click'>
			<tr>
				<th colspan='7'> Akkublöcke </th>
			</tr>
			<tr>
				<td ></td>
				<td> Zellblock  </td>
				<td> Zellnummer </td>
				<td> minimale Spannung</td>
				<td> maximale Spannung</td>
				<td> Balancing </td>
				<td> Temperatur</td>
			</tr>
			
				<script>
					for(j=0,k=0;j<12;j++)
					{
						document.write
						(
							"<tr>"+
								"<td  class='akkubutton' id='akku"+j+"'>"+
									"<img id='arrow"+j+"' class='akkubutton2' src='pfeil.svg' height='10' width='15' >"+
								"</td>"+
								"<td >#"+(j+1)+"</td>"+
								"<td></td>"+
								"<td id='minSpg"+j+"'>N/A</td>"+
								"<td id='maxSpg"+j+"'>N/A</td>"+
								"<td class='balance' id='bal"+j+"' >N/A</td>"+
								"<td></td>"+								
							"</tr>"	
						);
						for(i=(0+j*12);i<(12+j*12);i++)
						{						
							document.write(
							"<tr id='tr"+i+"'>"+
							"<td id='row"+i+"'></td>"+
							"<td id='block"+i+"'>#"+(j+1)+"</td>"+
							"<td id='nr"+i+"'> #"+(i+1)+" </td>"+
							"<td id=zelle"+i+" colspan='2'> N/A </td>"+
							"<td id=balance"+i+"> N/A </td> "
							);
							
							if(i % 3 == 0 )
							{
								
								document.write("<td id='temperatur"+(k)+"' rowspan='3'>N/A</td>");
								k++;
							}
							document.write("</tr>");
						}; 
					};				
				</script>			
		</table>
	</div>
	
	<div class="akkuitem2">
		<div class="akku_akku" >				
				<script>
					for(i=0;i<10;i++ )
				{
					document.write("<div id='akkuide"+i+"' class='akku_indica'></div>");
				};
				</script>
		</div>
		<div id="akku_ges" class="akku_big">N/A</div>
		<div class="akku_small">Aktuelle Restkapazität des Akkus</div>
		
		
	</div>
		
	
	
	
</div>
	
	
		
	
	
<?php include 'includes/overall/footer.php';?>