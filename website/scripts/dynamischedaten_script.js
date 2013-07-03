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
 *	Ändert die Klasse des Containers in der Navigationsleiste in
 *	"includes/Header.php" auf "active" (blau hinterlegt)
 *
 */
 
$(document).ready(function()
{
	document.getElementById("motor_header")		.setAttribute("class", "inactive");
	document.getElementById("fahrdyn_header")	.setAttribute("class", "inactive");
	document.getElementById("dyndata_header")	.setAttribute("class", "active");
	document.getElementById("akkudaten_header")	.setAttribute("class", "inactive"); 
	document.getElementById("allgdata_header")	.setAttribute("class", "inactive");
});

/**
 *
 * 	Darstellung der Drehzahlen an den Rädern,unter Nutzung
 *	des JavaScripte "justGage" und "raphael". (Lizenztyp: MIT)
 *
 */

var g0;					
var g1;
var g2;
var g3;			
		
$(document).ready(function()	// Initialisierung der Anzeigen			
{
	g0 = new JustGage({		
		id: "vornelinks",
		value: 0,
		min: 0,
		max: 2500,
		gaugeWidthScale:0.2,
		levelColors:["#447998"],
		title: "links",
		label:"rpm"
	});
	g1 = new JustGage({		
		id: "vornerechts",
		value: 0,
		min: 0,
		max: 2500,
		gaugeWidthScale:0.2,
		levelColors:["#447998"],
		title: "rechts",
		label:"rpm"
	});
	g2 = new JustGage({		
		id: "hintenlinks",
		value: 0,
		min: 0,
		max: 2500,
		gaugeWidthScale:0.2,
		levelColors:["#447998"],
		title: "links",
		label:"rpm"
	});
	g3 = new JustGage({		
		id: "hintenrechts",
		value: 0,
		min: 0,
		max: 2500,
		gaugeWidthScale:0.2,
		levelColors:["#447998"],
		title: "rechts",
		label:"rpm"
	});
});

/**
 *
 *	Die Funktion feder übernimmt die Eingabe (-180...180) und wandelt
 *	sie in eine grafische Repäsentation um.
 *
 *	@param: param (int) 
 *	data[24], als Position des Winkels, Bereich -180 bis 180°
 *
 */

function winkel(param)
{	
	temp=parseInt(parseInt(param)/2+90);
		for(j=0;j<181;j++){
			if($('#lenkwinkelid'+j).attr('class')=='fhz_lenkindica'){
				$('#lenkwinkelid'+j).removeClass("fhz_lenkindica");
				$('#lenkwinkelid'+j).addClass("fhz_lenkindica2");
			};
		};
		if(param<=180 && param>=-181){
			if($('#lenkwinkelid'+temp).attr('class')=='fhz_lenkindica2'){
				$('#lenkwinkelid'+temp).removeClass("fhz_lenkindica2");
				$('#lenkwinkelid'+temp).addClass("fhz_lenkindica");
			};
		}
	
};

/**
 *
 *	Die Funktion pedal übernimmt die Eingabe (-100...100) und wandelt
 *	sie in eine grafische Repäsentation um.
 *
 *	@param:param (int) 
 *	data[22] (gaseins) data[23] (gaszwei), data[17] (bremse), data[16] (bkraft) 
 *	als Position der jeweiligen Funktions-Einheit im Bereich -100 bis 100 % 
 *	
 *	data[15](+100), bdruck liegt ziwschen 0 und 200 bar
 *
 *	data[13] (wtemp1), data[14] (wtemp2), Temperaturen für Wasserim Bereich -100 bis 100 °C
 *
 *	@param:id (char)
 *	'gaseins','gaszwei','bremse','bkraft'
 *	'bdruck'
 *	'wtemp1'.'wtemp2'
 *
 *	@param:kind (int)
 *	1=blau,2=grün,3=rot
 *
 */

function bar_horizontal(param,id,kind)
{	
	if(param<=100 && param>=-100){
		var temp= parseInt(parseInt(param)/10+10);
		for(i=0;i<temp;i++){
			if($('#'+id+'id'+i).attr('class')=='fhz_pedalindica'){
				$('#'+id+'id'+i).removeClass('fhz_pedalindica');
				$('#'+id+'id'+i).addClass('fhz_pedalindica'+kind);
			}
		};
		for(j=temp;j<20;j++){
			if($('#'+id+'id'+j).attr('class')!='fhz_pedalindica'){
				$('#'+id+'id'+j).removeClass('fhz_pedalindica'+kind);
				$('#'+id+'id'+j).addClass('fhz_pedalindica');
			}
		};
	}
	else{
		for(i=0;i<20;i++){
			if($('#'+id+'id'+i).attr('class')!='fhz_pedalindica'){
				$('#'+id+'id'+i).removeClass('fhz_pedalindica'+kind);
				$('#'+id+'id'+i).addClass('fhz_pedalindica');
			}
		};
	}
};

/**
 *
 *	Die function "feder" zeigt an, wie viel Spielraum die Feder noch hat.
 *	Dabei stellt der weiße Balken die Strecke, die noch verfügbar ist dar und der
 * 	blaue, wie weit die Feder schon eingedrückt wurde.
 *	
 *	@param: param (int) 
 *	data[18] (vl), data[19] (vr), data[20] (hl), data[21] (hr) 
 *	als verbleibender Federweg zwischen 0 und 100
 *
 *	@param: id (char)
 *	'vl','vr','hl','hr' als ID für die entsprechenden Anzeigen
 */

function bar_vertical(param,id)		
{
	if(param<100 && param>= 0){
		var temp= parseInt(10-parseInt(param)/10); 	// bilde das Inverse
		for(i=0;i<temp;i++){			// markiere alle Zellen blau, die die Feder "eingedrückt" ist
			if($('#feder'+id+i).attr('class')=='fhz_federindi2'){
				$('#feder'+id+i).removeClass("fhz_federindi2");
				$('#feder'+id+i).addClass("fhz_federindi");
			}
		};
		for(j=temp+1;j<50;j++){			// markiere alle restlichen zellen weiß
			if($('#feder'+id+j).attr('class')!='fhz_federindi2'){
				$('#feder'+id+j).removeClass("fhz_federindi");
				$('#feder'+id+j).addClass("fhz_federindi2");
			}
		};
	}
	else{
		for(j=0;j<50;j++){			// markiere alle restlichen zellen weiß
			if($('#feder'+id+j).attr('class')!='fhz_federindi2'){
				$('#feder'+id+j).removeClass("fhz_federindi");
				$('#feder'+id+j).addClass("fhz_federindi2");
			}
		};
	}
};

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
 * 	Funktion, die nach Laden der Seite startetm und die sekündliche
 *	Aktualisierung startet
 *
 */
 
$(document).ready(function() 
	{setTimeout(executeQuery, 0);
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
	$.post('core/functions/dynamischedaten_sql.php',{permission:"true"},function(data)
	{
		$('#xGeschw')		.html(data[0]);			// Geschindigkeit(X)				
		$('#yGeschw')		.html(data[1]);			// Geschindigkeit(Y)
		$('#zGeschw')		.html(data[2]);			// Geschindigkeit(Z)
		$('#xBeschl')		.html(data[3]);			// Beschleunigung(X)
		$('#yBeschl')		.html(data[4]);			// Beschleunigung(Y)
		$('#zBeschl')		.html(data[5]);			// Beschleunigung(Z)
		$('#xGier')			.html(data[6]);			// Gier(X)
		$('#yGier')			.html(data[7]);			// Gier(Y)
		$('#zGier')			.html(data[8]);			// Gier(Z)
		g0.refresh(data[9]);					// Vorderrad links  (graphic)
		g1.refresh(data[10]);					// Vorderrad rechts (graphic)
		g2.refresh(data[11]);					// Hinterrad links  (graphic)
		g3.refresh(data[12]);					// Hinterrad rechts (graphic)			
		$('#wassertemp1')	.html(data[13]+" °C");			// Wassertemperatur 1		
		$('#wassertemp2')	.html(data[14]+" °C");			// Wassertemperatur 2		
		$('#bremsdruck')	.html(data[15]+" bar");			// Bremsdruck			
		$('#bremskraft')	.html(data[16]+" %");			// Bremskraft
		$('#bremsposition')	.html(data[17]+" %");			// Bremsposition
		bar_horizontal(data[13],'wtemp1',1);				// Wassertemperatur 1	(graphic)
		bar_horizontal(data[14],'wtemp2',1);				// Wassertemperatur 2	(graphic)
		bar_horizontal((data[15]-100),'bdruck',2)			// Wertkorrektur um , um Funktion bar_horizontal zu nutzen	
		bar_horizontal(data[16],'bkraft',2);				// Bremskraft	(graphic)
		bar_horizontal(data[17],'bremse',2);				// Bremsposition	(graphic)
		$('#federweg01')	.html(data[18]+" mm");			// Federweg vorne links
		$('#federweg02')	.html(data[19]+" mm");			// Federweg vorne rechts
		$('#federweg03')	.html(data[20]+" mm");			// Federweg hinten links
		$('#federweg04')	.html(data[21]+" mm");			// Federweg hinten rechts
		bar_vertical(data[18],'vl');						// Federweg vorne links (graphic)
		bar_vertical(data[19],'vr');						// Federweg vorne rechts (graphic)
		bar_vertical(data[21],'hr');						// Federweg hinten rechts(graphic)
		bar_vertical(data[20],'hl');						// Federweg hinten links (graphic)
		$('#gaspedal1')	.html(data[22]+" %");				// Gaspedal1
		$('#gaspedal2')	.html(data[23]+" %");				// Gaspedal2
		bar_horizontal(data[22],'gaseins',1);				// Gaspedal1	graphic
		bar_horizontal(data[23],'gaszwei',1);				// Gaspedal2 	graphic				
		$('#lenkwinkel')	.html(data[24]+" °");			// Lenkwinkel 
		winkel(data[24]);									// Lenkwinkel	graphic		
		age(data[25]);										// Zeitausgabe
	/*	$('#fehlerfeld')   	.html(data[26]);				// Fehlerfeld (ungenutzt) */
	},"JSON");
			
	setTimeout(executeQuery,1000);
};



