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
document.getElementById("motor_header")		.setAttribute("class", "nav_inactive");
document.getElementById("fahrdyn_header")	.setAttribute("class", "nav_inactive");
document.getElementById("dyndata_header")	.setAttribute("class", "nav_active");
document.getElementById("akkudaten_header")	.setAttribute("class", "nav_inactive"); 
document.getElementById("allgdata_header")	.setAttribute("class", "nav_inactive");
});

/**
 *
 * 	Darstellung der Drehzahlen an den Rädern,unter Nutzung
 *	des JavaScripte "justGage" und "raphael". (Lizenztyp: MIT)
 *
 *	@param: param 	= int $vrl, $vrr, $hrl, $hrr  als Drehzahl zwischen 0 und 2000
 *	@param: auswahl	= var $g0, $g1, $g2, $g3 als Zielanzeige
 *
 */

// globale Variablen 
var g0;					
var g1;
var g2;
var g3;			
		
function refresh_rpm(param,auswahl){ auswahl.refresh(param); };  // Akutalisierungsfunktion
 
 
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
 *	@param: int $lenwinkel, als Position des Winkels, Bereich -180 bis 180°
 *
 */

function winkel(param)
{	
	temp=parseInt(param)/2+90;
	for(j=0;j<181;j++)
	{
		if($('#lenkwinkelid'+j).attr('class')=='fhz_lenkindica'){
			$('#lenkwinkelid'+j).removeClass("fhz_lenkindica");
			$('#lenkwinkelid'+j).addClass("fhz_lenkindica2");
		};
	};
	if($('#lenkwinkelid'+temp).attr('class')=='fhz_lenkindica2'){
		$('#lenkwinkelid'+temp).removeClass("fhz_lenkindica2");
		$('#lenkwinkelid'+temp).addClass("fhz_lenkindica");
	};
};

/**
 *
 *	Die Funktion pedal übernimmt die Eingabe (-100...100) und wandelt
 *	sie in eine grafische Repäsentation um.
 *
 *	@param: int $Gaspedal01, $Gaspedal02, $Bremsposition, $Bremskraft als
 *	Position der jeweiligen Funktions-Einheit im Bereich -100 bis 100 %
 *	@param: int $bremsdruck(+100), Bremsdruck liegt ziwschen 0 und 200 bar
 *	@param: int $wassertemp1, $wassertemp2, Temperaturen für Wasser
 *	im Bereich -100 bis 100 °C
 *
 */

function pedal(param,id,kind)
{	
	var temp= parseInt(param)/10+10; 
	for(i=0;i<temp;i++)
	{
		if($('#'+id+'id'+i).attr('class')=='fhz_pedalindica')
		{
			$('#'+id+'id'+i).removeClass('fhz_pedalindica');
			$('#'+id+'id'+i).addClass('fhz_pedalindica'+kind);
		}
	};
	for(j=temp;j<20;j++)
	{
		if($('#'+id+'id'+i).attr('class')!='fhz_pedalindica')
		{
			$('#'+id+'id'+i).removeClass('fhz_pedalindica'+kind);
			$('#'+id+'id'+i).addClass('fhz_pedalindica');
		}
	};
};

/**
 *
 *	Die function "feder" zeigt an, wie viel Spielraum die Feder noch hat.
 *	Dabei stellt der weiße Balken die Strecke, die noch verfügbar ist dar und der
 * 	blaue, wie weit die Feder schon eingedrückt wurde.
 *	
 *	@param: int $federweg01, $federweg02, $federweg03, $federweg04 als 
 *	verbleibender Federweg
 *
 */

function feder(param,type)		
{
	var temp= 10-parseInt(param)/10; 	// bilde das Inverse
	for(i=0;i<temp;i++)				// markiere alle Zellen blau, die die Feder "eingedrückt" ist
	{
		if($('#feder'+type+i).attr('class')=='fhz_federindi2')
		{
			$('#feder'+type+i).removeClass("fhz_federindi2");
			$('#feder'+type+i).addClass("fhz_federindi");
		}
	};
	for(j=temp+1;j<50;j++)			// markiere alle restlichen zellen weiß
	{
		if($('#feder'+type+i).attr('class')!='fhz_federindi2')
		{
		$('#feder'+type+i).removeClass("fhz_federindi");
		$('#feder'+type+i).addClass("fhz_federindi2");
		}
	};
};

/**
 *
 * 	Funktion, die nach Laden der Seite startetm und die sekündliche
 *	Aktualisierung startet
 *
 */
 
$(document).ready(function() 
	{setTimeout(executeQuery, 1000);
});

/**
 *
 * 	Funktion, die nach fertigstellen der HTML-Seite aufgerufen wird.
 *	realisiert sekündliche Anfrage an die Datenbank und
 *	überschreibt die Werte auf der HTML Seite
 *
 */

function executeQuery()
{
	$.getJSON('core/functions/dynamischedaten_sql.php',function(data)
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
		refresh_rpm(data[9],g0);					// Vorderrad links  (graphic)
		refresh_rpm(data[10],g1);					// Vorderrad rechts (graphic)
		refresh_rpm(data[11],g2);					// Hinterrad links  (graphic)
		refresh_rpm(data[12],g3);					// Hinterrad rechts (graphic)			
		$('#wassertemp1')	.html(data[13]+" °C");	// Wassertemperatur 1
		pedal(data[13],'wtemp1',1);					// Wassertemperatur 1	(graphic)
		$('#wassertemp2')	.html(data[14]+" °C");	// Wassertemperatur 2
		pedal(data[14],'wtemp2',1);					// Wassertemperatur 2	(graphic)
		$('#bremsdruck')	.html(data[15]+" bar");	// Bremsdruck
		pedal((data[15]+100),'bdruck',3)			// Wertkorrektur um +100, um Funktion pedal zu nutzen		
		$('#bremskraft')	.html(data[16]+" %");	// Bremskraft
		pedal(data[16],'bkraft',3);					// Bremskraft	(graphic)
		$('#bremsposition')	.html(data[17]+" %");	// Bremsposition
		pedal(data[17],'bremse',3);					// Bremsposition	(graphic)
		$('#federweg01')	.html(data[18]+" mm");	// Federweg vorne links
		feder(data[18],'vl');						// Federweg vorne links (graphic)
		$('#federweg02')	.html(data[19]+" mm");	// Federweg vorne rechts
		feder(data[19],'vr');						// Federweg vorne rechts (graphic)
		$('#federweg03')	.html(data[20]+" mm");	// Federweg hinten links
		feder(data[20],'hl');						// Federweg hinten links (graphic)
		$('#federweg04')	.html(data[21]+" mm");	// Federweg hinten rechts
		feder(data[21],'hr');						// Federweg hinten rechts(graphic)
		$('#gaspedal1')	.html(data[22]+" %");		// Gaspedal1
		pedal(data[22],'gaseins',2);				// Gaspedal1	graphic
		$('#gaspedal2')	.html(data[23]+" %");		// Gaspedal2
		pedal(data[23],'gaszwei',2);				// Gaspedal2 	graphic				
		$('#lenkwinkel')	.html(data[24]+" °");	// Lenkwinkel 
		winkel(data[24]);							// Lenkwinkel	graphic
		$('#zeitp')			.html(data[25]+" s");	// Zeitpunkt
	/*	$('#fehlerfeld')   	.html(data[26]);		// Fehlerfeld (ungenutzt) */
	});
			
	setTimeout(executeQuery,1000);
};



