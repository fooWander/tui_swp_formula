/**
 *	"includes/Header.php" class="active" f�r aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header")		.setAttribute("class", "inactive");
document.getElementById("fahrdyn_header")	.setAttribute("class", "inactive");
document.getElementById("dyndata_header")	.setAttribute("class", "inactive");
document.getElementById("akkudaten_header")	.setAttribute("class", "active"); 
document.getElementById("allgdata_header")	.setAttribute("class", "inactive");
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
 * 	Funktion, die nach Laden der Seite startetm und die sek�ndliche
 *	Aktualisierung startet
 */

$(document).ready(function() 
	{setTimeout(executeQuery, 1000);
});

/**
 * 	Funktion die durch die erste Funktion aufgerufen wird.
 *	realisiert sek�ndliche Anfrage an die Datenbank und
 *	�berschreibt die Werte auf der PHP Seite
 */

function executeQuery()
{
	$.getJSON('core/functions/akkudaten_sql.php',function(data)
		{
		
		/**
		 *	Im folgenden werden 144 Zellspannungen aus dem JSON-Array (data) geholt und dann
		 *  sofort an die entsprechende ID geschrieben.
		 */
			
			for(i=0;i<144;i++)
			{
			$('#zelle'+i) .html(data[i]+" V");		// Zellspannung
			}
			
		/**
		 *	Folgende Block bekommt einen String (aus Folge von 0 und 1) aus dem JSON-Array (data).
		 *	Dieser String mit split aufgeteilt,so dass wieder ein Array (balancing) entsteht.
		 *	Danach wird das Array durchlaufen der Wert aus dem Array in "Integer" gewandelt.
		 *  Nun folgt die Fallunterscheidung, ob Balancing aktiviert wurde oder nicht.
		 */
		 
		balancing=data[147].split("");
		for(i=0;i<144;i++)					
			{	
				temp=parseInt(balancing[i]);
				if(temp==1)
				{
					$('#balance'+i).removeClass("status_aus");
					$('#balance'+i).addClass("status_an");
					$('#balance'+i).html("AN");		
				}
				else
				{					
					$('#balance'+i).removeClass("status_an");
					$('#balance'+i).addClass("status_aus");
					$('#balance'+i).html("AUS");							
				}
			}
		});
			
	setTimeout(executeQuery,1000);
};
