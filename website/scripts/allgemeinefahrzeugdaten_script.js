/**
 *
 *	Autor: 			David Kudlek
 *	Zweck: 			Softwareprojekt an der TU Ilmenau
 *	Thema: 			Service Interface f�r ein Formula Student Fahrzeug
 *	Auftraggeber: 	TeamStarcraft e.V.
 *
 */

/**
 *
 *	"includes/Header.php" class="active" f�r aufgerufene Seite
 *
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
 *
 *	Grafische Anzeige f�r die Geschwindigkeit. Ben�tigt globale Variable g, um durch
 *	"refreshg()" aktualisiert werden zu k�nnen und um die aktuellen Daten aus dem JSON 
 *	Paket zu bekommen.
 *	
 *	@param: int Geschwindigkeit, zwischen 0 und 250
 *
 */

var g;					


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
 *	Berechne die letzte Aktualisierung. date() �bergibt UNIX Zeit in millisekunden und wird daher durch 1000 geteilt
 *	und auf Sekunden normiert. Die Differenz von time() und param wird in Tage, Minuten, Stunden und Sekunden
 *	umgerechnet. Die Ausgabe erfolgt selektiv. Ab dem gr��ten verf�gbaren Wert wird angezeigt. Ist "$days" gr��er als
 *	0 werden alle Werte angezeit. Sind nur Sekunden verf�gbar, dann werden nur Sekunden angezeigt. Wenn der der Sekunden-
 *	wert als einziges verf�gbar ist, und dieser kleiner als 15 ist, wird nichts angezeigt 
 *
 *	@param: param (int)
 *	data[25] (Zeitpunkt), als wert in Sekunden 
 *
 */

 function age(param){
	$d=new Date();
	$days=0;
	$hours=0;
	$minutes=0;
	$seconds=parseInt(($d.getTime()/1000)-param);
	if($seconds>=86400){							// Tage: werden nicht angezeigt
		$days=parseInt($seconds/86400);
		$seconds=$seconds-$days*86400;
	}
	if($seconds>=3600){								// Stunden 
		$hours=parseInt($seconds/3600);
		$seconds=$seconds-$hours*3600;
	}
	if($seconds>=60){								// Minuten
		$minutes=parseInt($seconds/60);
		$seconds=$seconds-$minutes*60;
	}

	if($hours>0){$('#zeitpunkt')	.html("Letzte Aktualisierung vor: "+$hours+" Stunden "+$minutes+" Minuten "+$seconds+" Sekunden " );}
	else{
		if($minutes>0){$('#zeitpunkt')	.html("Letzte Aktualisierung vor: "+$minutes+" Minuten "+$seconds+" Sekunden " );}
		else{	
			if($seconds>15){$('#zeitpunkt')	.html("Letzte Aktualisierung vor: "+$seconds+" Sekunden " );}
			else { {$('#zeitpunkt')	.html(" " );}
			}
		}
	}
}

/**
 *
 * 	Funktion, die nach Laden der Seite startetm und die sek�ndliche
 *	Aktualisierung startet.
 *
 */

$(document).ready(function() 
{ 
	setTimeout(executeQuery, 1000);	
});

/**
 *
 * 	Funktion die durch die erste Funktion aufgerufen wird.
 *	realisiert sek�ndliche Anfrage an die Datenbank und
 *	�berschreibt die Werte auf der PHP Seite.
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
		
		$('#temp01')	.html(data[1]+" �C");		// Temperatur 1
		$('#temp02')	.html(data[2]+" �C");		// Temperatur 2
		$('#temp03')    .html(data[3]+" �C");		// Temperatur 3
		g.refresh(data[4]);						// Geschwindigkeit				
		$('#gas01') 	.html(data[5]+" %");		// Gas 1
		$('#gas02') 	.html(data[6]+" %");		// Gas 2
		$('#akku')  	.html(data[7]+" V");		// Akkuspannung
		$('#lzeit') 	.html(data[8]+" s");		// Laufzeit
		age(data[9]);
	/*	$('#fehlerfeld').html(data[10]);			// Fehlerfeld (ungenutzt) 	*/		
	});
			
	setTimeout(executeQuery,1000);
};