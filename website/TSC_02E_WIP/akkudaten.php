<?php include 'includes/overall/header.php'; ?>
	
<!-- Laden der Daten aus der SQL DB -->
<script src="scripts/akkudaten_script.js"></script>

<!-- Contentbereich ANFANG -->
	
	
<div class="content">
	
	<div class="item">
		<div id="zeitp">Zeitpunkt</div>
	</div>
	<!--		<button type=="button" onclick="tab()">Klick mich</button>	-->	
			<script>
			
			for(j=0;j<12;j++)
			{
				document.write
				(
				"<div class='item'>"+
				"<table border='1' class='click'>"+
				"<tr>"+
					"<th colspan='3'> Akkublock "+(j+1)+" </th>"+
				"</tr>"+
				"<tr>"+
					"<td> Zellnummer </td>"+
					"<td> Spannung </td>"+
					"<td> Balancing</td>"+
				"</tr>"
				);
				for(i=(0+j*12);i<(12+j*12);i++)
					{	
					
						document.write(
						"<tr>"+
						"<td> Nr. "+(i+1)+" </td>"+
						"<td id=zelle"+i+"> Spannung "+i+" </td>"+
						"<td id=balance"+i+" class='status_aus'> offline </tr> "+
						"</tr>");
					};
					document.write("</table></div>");
			} 
			</script> 
	

	
	
	
	
		
		
	
</div>
	
	
		
	
	
<?php include 'includes/overall/footer.php';?>