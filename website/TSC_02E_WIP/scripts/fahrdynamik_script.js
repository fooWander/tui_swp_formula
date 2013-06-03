/**
 *	"includes/Header.php" class="active" für aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header").setAttribute("class", "inactive");
document.getElementById("fahrdyn_header").setAttribute("class", "active");
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
	$.getJSON('core/functions/fahrdynamik_sql.php',function(data)
	{
		$('#antrieb')	.html(data[0]);		// Antriebsschlupfregelung				
		$('#tvec1')		.html(data[1]);		// Torque Vectoring 1
		$('#tvec2')		.html(data[2]);		// Torque Vectoring 2
		$('#tvec3')		.html(data[3]);		// Torque Vectoring 3
		$('#lenkwinkel').html(data[4]);		// Lenkwinkel
		$('#Zeitp')		.html(data[5]);		// Zeitpunkt
	/*	$('#fehlerfeld').html(data[6]);		// Fehlerfeld (ungenutzt) */
	});
			
setTimeout(executeQuery,1000);

};