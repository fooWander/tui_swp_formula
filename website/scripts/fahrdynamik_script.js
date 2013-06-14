/**
 *	"includes/Header.php" class="active" f�r aufgerufene Seite
 */

$(document).ready(function()
{
document.getElementById("motor_header")		.setAttribute("class", "nav_inactive");
document.getElementById("fahrdyn_header")	.setAttribute("class", "nav_active");
document.getElementById("dyndata_header")	.setAttribute("class", "nav_inactive");
document.getElementById("akkudaten_header")	.setAttribute("class", "nav_inactive"); 
document.getElementById("allgdata_header")	.setAttribute("class", "nav_inactive");
});

/**
 * 	Funktion, die nach Laden der Seite startetm und die sek�ndliche
 *	Aktualisierung startet
 */

$(document).ready(function() 
	{setTimeout(executeQuery, 1000);
});

/**
 * 	Funktion die durch die erste Funktion aufgerufen wird.
 *	realisiert sek�ndliche Anfrage an die Datenbank und
 *	�berschreibt die Werte auf der PHP Seite
 */

function executeQuery()
{
	$.getJSON('core/functions/fahrdynamik_sql.php',function(data)
	{
		$('#antrieb')	.html(data[0]);			// Antriebsschlupfregelung				
		$('#tvec')		.html(data[1]);			// Torque Vectoring 1		
		$('#lenkwinkel').html(data[2]+" �");	// Lenkwinkel
		$('#Zeitp')		.html(data[3]+" s");	// Zeitpunkt
	/*	$('#fehlerfeld').html(data[4]);			// Fehlerfeld (ungenutzt) */
	});
			
setTimeout(executeQuery,1000);

};