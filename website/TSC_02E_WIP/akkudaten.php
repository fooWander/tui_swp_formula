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
				document.write("<div class='item'><table border='1' class='click'>");
				document.write("<tr><th colspan='2'> Akkublock "+(j+1)+" </th> </tr>");
				for(i=(0+j*12);i<(12+j*12);i++)
					{	
					
						document.write(
						"<tr>"+
						"<td> Zellspannung "+(i+1)+" </td>"+
						"<td><div id=Zelle"+i+">"+"</div> </td>"+
						"</tr>");
					};
					document.write("</table></div>");
			} 
			</script> 
	

	
	
	
	
		
		
	
</div>
	
	
		
	
	
<?php include 'includes/overall/footer.php';?>