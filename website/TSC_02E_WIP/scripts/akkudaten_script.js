/**
 *	"includes/Header.php" class="active" für aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header").setAttribute("class", "inactive");
document.getElementById("fahrdyn_header").setAttribute("class", "inactive");
document.getElementById("dyndata_header").setAttribute("class", "inactive");
document.getElementById("akkudaten_header").setAttribute("class", "active"); 
document.getElementById("allgdata_header").setAttribute("class", "inactive");
});

/**
 *
 *
 
function tab()
	{
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
					
	};

*/

/**
 * 	Funktion, die nach Laden der Seite startetm und die sekündliche
 *	Aktualisierung startet
 */

$(document).ready(function() 
	{setTimeout(executeQuery, 1000);
});

/**
 * 	Funktion die durch die erste Funktion aufgerufen wird.
 *	realisiert sekündliche Anfrage an die Datenbank und
 *	überschreibt die Werte auf der PHP Seite
 */

function executeQuery()
{
	$.getJSON('core/functions/akkudaten_sql.php',function(data)
		{
			for(i=0;i<144;i++)
			{
			$('#Zelle'+i) .html(data[i]);		// Status Notaus
			}
		/*	$('#Zelle1').html(data[1]);		// Temperatur 1
			$('#Zelle2').html(data[2]);		// Temperatur 2
			$('#Zelle3').html(data[3]);		// Temperatur 3
			$('#Zelle4') .html(data[4]);		// Geschwindigkeit				
			$('#Zelle5') .html(data[5]);		// Gas 1
			$('#Zelle6') .html(data[6]);		// Gas 2
			$('#Akku')  .html(data[7]);		
			$('#Lzeit') .html(data[8]);
			$('#Zeitp') .html(data[9]);*/
			
		});
			
	setTimeout(executeQuery,1000);
};

