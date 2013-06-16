/**
 *
 *	Autor: 			David Kudlek
 *	Zweck: 			Softwareprojekt an der TU Ilmenau
 *	Thema: 			Service Interface f�r ein Formula Student Fahrzeug
 *	Auftraggeber: 	TeamStarcraft e.V.
 *
 */

/**
 *	"includes/Header.php" class="active" f�r aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header")		.setAttribute("class", "active");
document.getElementById("fahrdyn_header")	.setAttribute("class", "inactive");
document.getElementById("dyndata_header")	.setAttribute("class", "inactive");
document.getElementById("akkudaten_header")	.setAttribute("class", "inactive"); 
document.getElementById("allgdata_header")	.setAttribute("class", "inactive");
});

/**
 * 	Funktion, die nach Laden der Seite startetm und die sek�ndliche
 *	Aktualisierung startet
 */

$(document).ready(function() 
{
	setTimeout(executeQuery, 1000);
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
 * 	Funktion die durch die erste Funktion aufgerufen wird.
 *	realisiert sek�ndliche Anfrage an die Datenbank und
 *	�berschreibt die Werte auf der PHP Seite
 */
 
function executeQuery()
{
	$.getJSON('core/functions/motorundumrichter_sql.php',function(data)
	{
		$('#dcstrom')			.html(data[0]+" Ampere"); 	// DC Strom				
		$('#dcspannung')		.html(data[1]+" Volt");	// DC Spannung
		$('#motortemp01')		.html(data[2]+" �C");	// Motortemperatur 1
		$('#motortemp02')		.html(data[3]+" �C");	// Motortemperatur 2
		$('#motortemp03')		.html(data[4]+" �C");	// Motortemperatur 3
		$('#motortemp04')		.html(data[5]+" �C");	// Motortemperatur 4
		$('#motortemp05')		.html(data[6]+" �C");	// Motortemperatur 5
		$('#motortemp06')		.html(data[7]+" �C");	// Motortemperatur 6
		$('#motortemp07')		.html(data[8]+" �C");	// Motortemperatur 7
		$('#motortemp08')		.html(data[9]+" �C");	// Motortemperatur 8
		$('#stromgrenze')		.html(data[10]);		// Stromgrenze
		$('#maximalleistung')	.html(data[11]);		// Maximalleistung
		$('#l�fterdrehzahl')	.html(data[12]+" rpm");	// L�fterdrehzahl
		$('#l�fter')			.html(data[13]);		// L�fter
		$('#pumpe')				.html(data[14]);		// Pumpe
		$('#wassertemp')		.html(data[15]+" �C");	// Wassertemperatur
		age(data[16]);
	/*	$('#fehlerfeld')		.html(data[17]);		// Fehlerfeld (ungenutzt) */	
	});
			
	setTimeout(executeQuery,1000);
};