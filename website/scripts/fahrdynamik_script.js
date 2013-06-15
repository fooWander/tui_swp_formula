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
		$('#antrieb')	.html(data[0]);			// Antriebsschlupfregelung				
		$('#tvec')		.html(data[1]);			// Torque Vectoring 1		
		$d=new Date();
		$zeit=Math.round(($d.getTime()/1000)-data[2]);
		$('#zeitpunkt')		.html("Daten zuletzt aktualisiert vor: "+$zeit+" s");
	/*	$('#fehlerfeld').html(data[3]);			// Fehlerfeld (ungenutzt) */
	});
	$.getJSON('core/functions/dynamischedaten_sql.php',function(data)
	{	
		$('#lenkwinkel').html(data[24]+" %");	// Lenkwinkel			
	});
	

	
setTimeout(executeQuery,1000);

};