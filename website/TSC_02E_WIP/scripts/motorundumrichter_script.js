/**
 *	"includes/Header.php" class="active" für aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header").setAttribute("class", "active");
document.getElementById("fahrdyn_header").setAttribute("class", "inactive");
document.getElementById("dyndata_header").setAttribute("class", "inactive");
document.getElementById("akkudaten_header").setAttribute("class", "inactive"); 
document.getElementById("allgdata_header").setAttribute("class", "inactive");
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
	$.getJSON('core/functions/motorundumrichter_sql.php',function(data)
	{
		$('#dcstrom')			.html(data[0]); 	// DC Strom				
		$('#dcspannung')		.html(data[1]);		// DC Spannung
		$('#motortemp01')		.html(data[2]);		// Motortemperatur 1
		$('#motortemp02')		.html(data[3]);		// Motortemperatur 2
		$('#motortemp03')		.html(data[4]);		// Motortemperatur 3
		$('#motortemp04')		.html(data[5]);		// Motortemperatur 4
		$('#motortemp05')		.html(data[6]);		// Motortemperatur 5
		$('#motortemp06')		.html(data[7]);		// Motortemperatur 6
		$('#motortemp07')		.html(data[8]);		// Motortemperatur 7
		$('#motortemp08')		.html(data[9]);		// Motortemperatur 8
		$('#stromgrenze')		.html(data[10]);	// Stromgrenze
		$('#maximalleistung')	.html(data[11]);	// Maximalleistung
		$('#lüfterdrehzahl')	.html(data[12]);	// Lüfterdrehzahl
		$('#lüfter')			.html(data[13]);	// Lüfter
		$('#pumpe')				.html(data[14]);	// Pumpe
		$('#wassertemp')		.html(data[15]);	// Wassertemperatur
		$('#zeitp')				.html(data[16]);	// Zeitpunkt
	/*	$('#fehlerfeld')		.html(data[17]);	// Fehlerfeld (ungenutzt) */	
	});
			
	setTimeout(executeQuery,1000);
};