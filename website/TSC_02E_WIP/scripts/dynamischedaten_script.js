/**
 *	"includes/Header.php" class="active" für aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header").setAttribute("class", "inactive");
document.getElementById("fahrdyn_header").setAttribute("class", "inactive");
document.getElementById("dyndata_header").setAttribute("class", "active");
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
	$.getJSON('core/functions/dynamischedaten_sql.php',function(data)
	{
		$('#xGeschw')		.html(data[0]);		// Geschindigkeit(X)				
		$('#yGeschw')		.html(data[1]);		// Geschindigkeit(Y)
		$('#zGeschw')		.html(data[2]);		// Geschindigkeit(Z)
		$('#xBeschl')		.html(data[3]);		// Beschleunigung(X)
		$('#yBeschl')		.html(data[4]);		// Beschleunigung(Y)
		$('#zBeschl')		.html(data[5]);		// Beschleunigung(Z)
		$('#xGier')			.html(data[6]);		// Gier(X)
		$('#yGier')			.html(data[7]);		// Gier(Y)
		$('#zGier')			.html(data[8]);		// Gier(Z)
		$('#vrl')			.html(data[9]);		// Vorderrad links
		$('#vrr')			.html(data[10]);	// Vorderrad rechts
		$('#hrl')			.html(data[11]);	// Hinterrad links
		$('#hrr')			.html(data[12]);	// Hinterrad rechts
		$('#wassertemp01')	.html(data[13]);	// Wassertemperatur 1
		$('#wassertemp02')	.html(data[14]);	// Wassertemperatur 2
		$('#bremsdruck')	.html(data[15]);	// Bremsdruck
		$('#bremskraft')	.html(data[16]);	// Bremskraft
		$('#bremsposition')	.html(data[17]);	// Bremsposition
		$('#federweg')		.html(data[18]);	// Federweg
		$('#gaspedal')		.html(data[19]);	// Gaspedal
		$('#lenkwinkel')	.html(data[20]);	// Lenkwinkel
		$('#zeitp')			.html(data[21]);	// Zeitpunkt
	/*	$('#fehlerfeld')   	.html(data[22]);	// Fehlerfeld (ungenutzt) */
	});
			
	setTimeout(executeQuery,1000);
};