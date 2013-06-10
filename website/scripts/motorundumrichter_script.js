/**
 *
 *	Autor: 			David Kudlek
 *	Zweck: 			Softwareprojekt an der TU Ilmenau
 *	Thema: 			Service Interface für ein Formula Student Fahrzeug
 *	Auftraggeber: 	TeamStarcraft e.V.
 *
 */

/**
 *	"includes/Header.php" class="active" für aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header")		.setAttribute("class", "nav_active");
document.getElementById("fahrdyn_header")	.setAttribute("class", "nav_inactive");
document.getElementById("dyndata_header")	.setAttribute("class", "nav_inactive");
document.getElementById("akkudaten_header")	.setAttribute("class", "nav_inactive"); 
document.getElementById("allgdata_header")	.setAttribute("class", "nav_inactive");
});

/**
 * 	Funktion, die nach Laden der Seite startetm und die sekündliche
 *	Aktualisierung startet
 */

$(document).ready(function() 
{
	setTimeout(executeQuery, 1000);
});

/**
 * 	Funktion die durch die erste Funktion aufgerufen wird.
 *	realisiert sekündliche Anfrage an die Datenbank und
 *	überschreibt die Werte auf der PHP Seite
 */
 
function executeQuery()
{
	$.getJSON('core/functions/motorundumrichter_sql.php',function(data)
	{
		$('#dcstrom')			.html(data[0]+" Ampere"); 	// DC Strom				
		$('#dcspannung')		.html(data[1]+" Volt");	// DC Spannung
		$('#motortemp01')		.html(data[2]+" °C");	// Motortemperatur 1
		$('#motortemp02')		.html(data[3]+" °C");	// Motortemperatur 2
		$('#motortemp03')		.html(data[4]+" °C");	// Motortemperatur 3
		$('#motortemp04')		.html(data[5]+" °C");	// Motortemperatur 4
		$('#motortemp05')		.html(data[6]+" °C");	// Motortemperatur 5
		$('#motortemp06')		.html(data[7]+" °C");	// Motortemperatur 6
		$('#motortemp07')		.html(data[8]+" °C");	// Motortemperatur 7
		$('#motortemp08')		.html(data[9]+" °C");	// Motortemperatur 8
		$('#stromgrenze')		.html(data[10]);		// Stromgrenze
		$('#maximalleistung')	.html(data[11]);		// Maximalleistung
		$('#lüfterdrehzahl')	.html(data[12]+" rpm");	// Lüfterdrehzahl
		$('#lüfter')			.html(data[13]);		// Lüfter
		$('#pumpe')				.html(data[14]);		// Pumpe
		$('#wassertemp')		.html(data[15]+" °C");	// Wassertemperatur
		$('#zeitp')				.html(data[16]+" s");	// Zeitpunkt
	/*	$('#fehlerfeld')		.html(data[17]);		// Fehlerfeld (ungenutzt) */	
	});
			
	setTimeout(executeQuery,1000);
};