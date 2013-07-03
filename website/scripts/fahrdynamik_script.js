/**
 *	"includes/Header.php" class="active" für aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header")		.setAttribute("class", "inactive");
document.getElementById("fahrdyn_header")	.setAttribute("class", "active");
document.getElementById("dyndata_header")	.setAttribute("class", "inactive");
document.getElementById("akkudaten_header")	.setAttribute("class", "inactive"); 
document.getElementById("allgdata_header")	.setAttribute("class", "inactive");
});

/**
 * 	Funktion, die nach Laden der Seite startetm und die sekündliche
 *	Aktualisierung startet
 */

$(document).ready(function() 
	{setTimeout(executeQuery, 0);
});

/**
 *
 *	Berechne die letzte Aktualisierung. date() übergibt UNIX Zeit in millisekunden und wird daher durch 1000 geteilt
 *	und auf Sekunden normiert. Die Differenz von time() und param wird in Tage, Minuten, Stunden und Sekunden
 *	umgerechnet. Die Ausgabe erfolgt selektiv. Ab dem größten verfügbaren Wert wird angezeigt. Ist "$days" größer als
 *	0 werden alle Werte angezeit. Sind nur Sekunden verfügbar, dann werden nur Sekunden angezeigt. Wenn der der Sekunden-
 *	wert als einziges verfügbar ist, und dieser kleiner als 15 ist, wird nichts angezeigt 
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
	$.post('core/functions/fahrdynamik_sql.php',{permission:"true"},function(data)
	{
		$('#antrieb')	.html(data[0]);			// Antriebsschlupfregelung				
		$('#tvec')		.html(data[1]);			// Torque Vectoring 1		
		age(data[2]);
	/*	$('#fehlerfeld').html(data[3]);			// Fehlerfeld (ungenutzt) */
	},"JSON");
	$.post('core/functions/dynamischedaten_sql.php',{permission:"true"},function(data)
	{
		$('#lenkwinkel').html(data[24]+" °");	// Lenkwinkel			
	},"JSON");
	

	
setTimeout(executeQuery,1000);

};