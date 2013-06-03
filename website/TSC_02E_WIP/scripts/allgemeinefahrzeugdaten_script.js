/**
 *	"includes/Header.php" class="active" für aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header").setAttribute("class", "inactive");
document.getElementById("fahrdyn_header").setAttribute("class", "inactive");
document.getElementById("dyndata_header").setAttribute("class", "inactive");
document.getElementById("akkudaten_header").setAttribute("class", "inactive"); 
document.getElementById("allgdata_header").setAttribute("class", "active");
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
		$('#statN') 	.html(data[0]);		// Status Notaus
		$('#temp01')	.html(data[1]);		// Temperatur 1
		$('#temp02')	.html(data[2]);		// Temperatur 2
		$('#temp03')    .html(data[3]);		// Temperatur 3
		$('#geschw')	.html(data[4]);		// Geschwindigkeit				
		$('#gas01') 	.html(data[5]);		// Gas 1
		$('#gas02') 	.html(data[6]);		// Gas 2
		$('#akku')  	.html(data[7]);		// Akkuspannung
		$('#lzeit') 	.html(data[8]);		// Laufzeit
		$('#zeitp') 	.html(data[9]);		// Zeitpunkt
	/*	$('#fehlerfeld').html(data[10]);	// Fehlerfeld (ungenutzt) */
	});
			
	setTimeout(executeQuery,1000);
};