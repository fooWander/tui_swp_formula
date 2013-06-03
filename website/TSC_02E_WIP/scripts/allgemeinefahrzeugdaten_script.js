/**
 *	"includes/Header.php" class="active" für aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header")		.setAttribute("class", "inactive");
document.getElementById("fahrdyn_header")	.setAttribute("class", "inactive");
document.getElementById("dyndata_header")	.setAttribute("class", "inactive");
document.getElementById("akkudaten_header")	.setAttribute("class", "inactive"); 
document.getElementById("allgdata_header")	.setAttribute("class", "active");
});

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
	$.getJSON('core/functions/allgemeinefahrzeugdaten_sql.php',function(data)
	{
		/**
		 *	Folgende Block bekommt einen String (aus Folge von 0 und 1) aus dem JSON-Array (data).
		 *	Dieser String mit split aufgeteilt,so dass wieder ein Array (statNotaus) entsteht.
		 *	Danach wird das Array durchlaufen der Wert aus dem Array in "Integer" gewandelt.
		 *  Nun folgt die Fallunterscheidung, ob Notaus aktiviert wurde oder nicht.
		 */
		 
		statNotaus=data[0].split("");
		for(i=0;i<10;i++)					
			{	
				temp=parseInt(statNotaus[i]);
				if(temp==1)
				{
					$('#statN'+i).removeClass("status_aus");
					$('#statN'+i).addClass("status_an");
					$('#statN'+i).html("AN");		
				}
				else
				{					
					$('#statN'+i).removeClass("status_an");
					$('#statN'+i).addClass("status_aus");
					$('#statN'+i).html("AUS");							
				}
			}
			
		/**
		 *	Im folgenden werden alle anderen Daten aus dem JSON-Array (data) ausgelesen und
		 *	an die richtige ID geschrieben.
		 */
		
		$('#temp01')	.html(data[1]+" °C");		// Temperatur 1
		$('#temp02')	.html(data[2]+" °C");		// Temperatur 2
		$('#temp03')    .html(data[3]+" °C");		// Temperatur 3
		$('#geschw')	.html(data[4]+" km/h");		// Geschwindigkeit				
		$('#gas01') 	.html(data[5]+" %");		// Gas 1
		$('#gas02') 	.html(data[6]+" %");		// Gas 2
		$('#akku')  	.html(data[7]+" V");		// Akkuspannung
		$('#lzeit') 	.html(data[8]+" s");		// Laufzeit
		$('#zeitp') 	.html(data[9]+" s");		// Zeitpunkt
	/*	$('#fehlerfeld').html(data[10]);			// Fehlerfeld (ungenutzt) 	*/
	
		
	});
			
	setTimeout(executeQuery,1000);
};