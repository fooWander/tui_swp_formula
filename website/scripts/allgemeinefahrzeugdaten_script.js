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
	document.getElementById("motor_header")		.setAttribute("class", "inactive");
	document.getElementById("fahrdyn_header")	.setAttribute("class", "inactive");
	document.getElementById("dyndata_header")	.setAttribute("class", "inactive");
	document.getElementById("akkudaten_header")	.setAttribute("class", "inactive"); 
	document.getElementById("allgdata_header")	.setAttribute("class", "active");
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
 *	Berechne die letzte Aktualisierung. date() übergibt UNIX Zeit in millisekunden und wird daher durch 1000 geteilt
 *	und auf Sekunden normiert. Param ist in Nanosekunden und wird deshalb durch 1.000.000.000 dividiert und so auf Sekunden
 *	normiert. Die Differenz von time() und param wird in Tage, Minuten, Stunden und Sekunden umgerechnet. Die Ausgabe erfolgt 
 *	selektiv. Ab dem größten verfügbaren Wert wird angezeigt. Ist "$days" größer als 0 werden alle Werte angezeit. Sind nur 
 *	Sekunden verfügbar, dann werden nur Sekunden angezeigt. Wenn der der Sekundenwert als einziges verfügbar ist, und dieser 
 *	kleiner als 15 ist, wird nichts angezeigt 
 *
 *	@param: param (int)
 *	data[9] (Zeitpunkt), als wert in Nanosekunden 
 *
 */

 function age(param){
	$d=new Date();
	$days=0;
	$hours=0;
	$minutes=0;
	$seconds=parseInt($d.getTime()/1000)-parseInt(param/1000);
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
 *	Folgende Block bekommt einen String (aus Folge von 0 und 1) aus dem JSON-Array (data).
 *	Dieser String mit split aufgeteilt,so dass wieder ein Array (statNotaus) entsteht.
 *	Danach wird das Array durchlaufen der Wert aus dem Array in "Integer" gewandelt.
 *  Nun folgt die Fallunterscheidung, ob Notaus aktiviert wurde oder nicht.
 * 
 *	@param:param (char)
 *	Sting aus 0 und 1 wird übergeben, der die Notaus-Schalter kodiert
 *
 */

function toggle_notaus(param){
	statNotaus=param.split("");
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
} 

/**
 *
 * 	Funktion, die nach Laden der Seite startetm und die sekündliche
 *	Aktualisierung startet.
 *
 */

$(document).ready(function() 
{ 
	setTimeout(executeQuery, 0);	
});

/**
 *	
 * 	Funktion die durch die erste Funktion aufgerufen wird.
 *	realisiert sekündliche Anfrage an die Datenbank und
 *	überschreibt die Werte auf der PHP Seite
 *  
 *	permission wird als Wert im associativen Array $_POST
 *	übergeben, um die unerlaubten direkten Zugriff auf die
 *	Daten zu verhindern
 *
 */
 
function executeQuery()
{
	$.post('core/functions/allgemeinefahrzeugdaten_sql.php',{permission:"true"},function(data)
	{
		toggle_notaus(data[0]);						// Notausschalte AN/AUS			
		$('#temp01')	.html(data[1]+" °C");		// Temperatur 1
		$('#temp02')	.html(data[2]+" °C");		// Temperatur 2
		$('#temp03')    .html(data[3]+" °C");		// Temperatur 3
		g.refresh(data[4]);							// Geschwindigkeit				
		$('#gas01') 	.html(data[5]+" %");		// Gas 1
		$('#gas02') 	.html(data[6]+" %");		// Gas 2
		$('#akku')  	.html(data[7]+" V");		// Akkuspannung
		$('#lzeit') 	.html(data[8]+" s");		// Laufzeit
		age(data[9]);								// Verzögerung der Aktualisierung
	/*	$('#fehlerfeld').html(data[10]);			// Fehlerfeld (ungenutzt) 	*/		
	},"JSON");
			
	setTimeout(executeQuery,1000);
};