/**
 *
 *	Autor: 			David Kudlek
 *	Zweck: 			Softwareprojekt an der TU Ilmenau
 *	Thema: 			Service Interface für ein Formula Student Fahrzeug
 *	Auftraggeber: 	TeamStarcraft e.V.
 *
 */

/**
 *
 *	"includes/Header.php" class="active" für aufgerufene Seite
 *
 */

$(document).ready(function()
{
document.getElementById("motor_header")		.setAttribute("class", "nav_inactive");
document.getElementById("fahrdyn_header")	.setAttribute("class", "nav_inactive");
document.getElementById("dyndata_header")	.setAttribute("class", "nav_inactive");
document.getElementById("akkudaten_header")	.setAttribute("class", "nav_inactive"); 
document.getElementById("allgdata_header")	.setAttribute("class", "nav_active");
});

/**
 *
 *	Grafische Anzeige für die Geschwindigkeit. Benötigt globale Variable g, um durch
 *	"refreshg()" aktualisiert werden zu können und um die aktuellen Daten aus dem JSON 
 *	Paket zu bekommen.
 *	
 *	@param: int Geschwindigkeit, zwischen 0 und 250
 *
 */

var g;					
function refresh_gesw(param)
{ 
	g.refresh(param); 
};

$(document).ready(function()
{
	g = new JustGage({		
		id: "geschwindigkeit",
		value: 0,
		min: 0,
		max: 250,
		gaugeWidthScale:0.2,
		levelColors:["#447998"],
		title: "Geschwindigkeit",
		label:"km/h"
	}); 
});


/**
 *
 * 	Funktion, die nach Laden der Seite startetm und die sekündliche
 *	Aktualisierung startet.
 *
 */

$(document).ready(function() 
{
	$('#single').masonry({
		  itemSelector: '.top',
		  columnWidth: 160
		});  
	setTimeout(executeQuery, 1000);	
});

/**
 *
 * 	Funktion die durch die erste Funktion aufgerufen wird.
 *	realisiert sekündliche Anfrage an die Datenbank und
 *	überschreibt die Werte auf der PHP Seite.
 *
 */
 
function executeQuery()
{
	$.getJSON('core/functions/allgemeinefahrzeugdaten_sql.php',function(data)
	{
		/**
		 *
		 *	Folgende Block bekommt einen String (aus Folge von 0 und 1) aus dem JSON-Array (data).
		 *	Dieser String mit split aufgeteilt,so dass wieder ein Array (statNotaus) entsteht.
		 *	Danach wird das Array durchlaufen der Wert aus dem Array in "Integer" gewandelt.
		 *  Nun folgt die Fallunterscheidung, ob Notaus aktiviert wurde oder nicht.
		 * 
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
		 *
		 *	Im folgenden werden alle anderen Daten aus dem JSON-Array (data) ausgelesen und
		 *	an die richtige ID geschrieben.
		 *
		 */
		
		$('#temp01')	.html(data[1]+" °C");		// Temperatur 1
		$('#temp02')	.html(data[2]+" °C");		// Temperatur 2
		$('#temp03')    .html(data[3]+" °C");		// Temperatur 3
		refresh_gesw(data[4]);						// Geschwindigkeit				
		$('#gas01') 	.html(data[5]+" %");		// Gas 1
		$('#gas02') 	.html(data[6]+" %");		// Gas 2
		$('#akku')  	.html(data[7]+" V");		// Akkuspannung
		$('#lzeit') 	.html(data[8]+" s");		// Laufzeit
		$('#zeitp') 	.html(data[9]+" s");		// Zeitpunkt
	/*	$('#fehlerfeld').html(data[10]);			// Fehlerfeld (ungenutzt) 	*/
	
		
	});
			
	setTimeout(executeQuery,1000);
};