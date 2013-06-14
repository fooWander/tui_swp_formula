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
document.getElementById("dyndata_header")	.setAttribute("class", "nav_inactive");
document.getElementById("akkudaten_header")	.setAttribute("class", "nav_active"); 
document.getElementById("allgdata_header")	.setAttribute("class", "nav_inactive");
});

/**
 *
 *	Masrony sorgt dafür, dass im oberen Container die Werte richtig angeordnet werden.
 *
 *	$(value).click() sorgt dafür, dass die Tabellenspalten für Zellen ausgeblendet werden 
 *	können. 
 *	
 */
 
$(document).ready(function()
{	
	for(h=0;h<12;h++){toggle_tab(h);}	//initialisiere alle Untertabellen als geschlossen
	
	$("#akku0")	.click(function() {toggle_tab(0);});
	$("#akku1")	.click(function() {toggle_tab(1);});
	$("#akku2")	.click(function() {toggle_tab(2);});
	$("#akku3")	.click(function() {toggle_tab(3);});
	$("#akku4")	.click(function() {toggle_tab(4);});
	$("#akku5")	.click(function() {toggle_tab(5);});
	$("#akku6")	.click(function() {toggle_tab(6);});
	$("#akku7")	.click(function() {toggle_tab(7);});
	$("#akku8")	.click(function() {toggle_tab(8);});
	$("#akku9")	.click(function() {toggle_tab(9);});
	$("#akku10").click(function() {toggle_tab(10);});
	$("#akku11").click(function() {toggle_tab(11);});
	
	
});

/**
 *
 *	Durch toggle_tab werden die Untermenüs für die Details der Blöcke
 *	auf bzw. zugeklappt. Bei initialisierung werden sie automatisch
 *	geschlossen.
 *
 *	@param: int 0 bis 11, wählt die richtige Zeile aus, deren Untermenü
 *	getoggelt werden soll.
 *
 */

function toggle_tab(k)
{	
	toggle_arrow(k);
	function toggle_arrow(k)
	{
		if($('#arrow'+k).attr('class')=='akkubutton2')
		{
			$('#arrow'+k).removeClass("akkubutton2");
		}
		else
		{
			$('#arrow'+k).addClass("akkubutton2");
		}
	};
	for(i=0+(k*12);i<(12+k*12);i++)
	{
		$("#tr"+i).toggle();
		$("#row"+i).toggle();
		$("#nr"+i).toggle();
		$("#zelle"+i).toggle();
		$("#balance"+i).toggle();
	}
	for(j=0+(k*12);j<4+(k*12);j++)
	{
		$("#temperatur"+j).toggle();
	}
};

/**
 *
 *	Grafische Aufbereitung der Restkapazität. Wertebreich von 0 bis1000.
 *	Daher wird durch 5 geteilt, um auf eine Skala von 200 Einheiten zu passen. 
 *
 *	@param: int $akku_ges
 *
 */
 
function kapa(param)
{	
	var temp= (parseInt(param))/100; 
	for(i=0;i<temp;i++)
	{
		if($('#akkuide'+i).attr('class')=='akku_indica')
		{
			$('#akkuide'+i).removeClass('akku_indica');
			$('#akkuide'+i).addClass('akku_indica1');
		}
	};
	for(j=temp;j<10;j++)
	{
		$('#akkuide'+i).removeClass('akku_indica1');
		$('#akkuide'+i).addClass('akku_indica');
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
 * 	Funktion die durch die erste Funktion aufgerufen wird.
 *	realisiert sekündliche Anfrage an die Datenbank und
 *	überschreibt die Werte auf der PHP Seite
 */

function executeQuery()
{
	$.getJSON('core/functions/akkudaten_sql.php',function(data)
	{
		
		/**
		 *	Im folgenden werden 144 Zellspannungen aus dem JSON-Array (data) geholt und 
		 *  dann sofort an die entsprechende ID geschrieben.
		 *	Weiterhin wird die maximal, sowie die minimals Spannung pro Block ermittelt
		 *	und ebenfalls auf die Webseite geschrieben.
		 */
		 
		var spgmax=0;								// Initialwert Spgmax
		var spgmin=5;								// Initialwert Spgmin
		var counter_zell=0;							// Zähler für die 12 Zellen pro Block							
		var counter_block=0;						// Zähler für die Blöcke 
		for(i=0;i<144;i++)
		{
			$('#zelle'+i) .html(data[i]+" V");		// Zellspannung
			
			if(data[i]<spgmin){						// bestimme max Zellspannung pro Block
				spgmin=data[i];
			}
			if(data[i]>spgmax){						// bestimme min Zellspannung pro Block
				spgmax=data[i];
			}
			
			counter_zell++;
			
			/**
			 *	Wenn 12 Zellen durchlaufen, schreibe max und min Werte in den aktuellen
			 *	Zellblock.
			 */
			
			if(counter_zell==11){
				$('#minSpg'+counter_block).html(spgmin+" V");
				$('#maxSpg'+counter_block).html(spgmax+" V");
				counter_block++;
				counter_zell=0;							// Zurücksetzen für nächste Runde
				spgmax=0;								// Zurücksetzen für nächste Runde		
				spgmin=5;								// Zurücksetzen für nächste Runde
			}
		}
		
		/**
		 *	Maximale, sowie Minimale Spannung und Ladestrom ausgeben
		 */
		
		
		$('#max_spg')		.html(data[144]+" Volt");
		$('#min_spg')		.html(data[145]+" Volt");
		$('#ges_spg')		.html(data[146]+" Volt");
		$('#akku_ges')		.html((data[146]/10)+" %");		
		kapa(data[146]);
		
		$('#lade_strom')	.html(data[147]+" Ampere");
		$('#lade_spg')		.html(data[148]+" Volt")
		$('#zeitp')			.html(data[199]+" s");
	/*  $('#fehlerfeld')	.html(data[200]);	// Fehlerfeld (ungenutzt)   */	
		
		/**
		 *	Folgende Block bekommt einen String (aus Folge von 0 und 1) aus dem 
		 *	JSON-Array(data).
		 *	
		 *	Dieser String mit split aufgeteilt,so dass wieder ein Array (balancing) 
		 *	entsteht.
		 *	
		 *	Danach wird das Array durchlaufen der Wert aus dem Array in "Integer" gewandelt.
		 *  Nun folgt die Fallunterscheidung, ob Balancing aktiviert wurde oder nicht.
		 *
		 *	Zusätzlich wird immer noch ermittelt, wie viele Zellen pro Block im Balancing
		 *  Modus sind. Dafür werden 3 Variablen initialisiert und eine weitere if-else-
		 *	Klausel genutzt.
		 *
		 *	Aufgrund der Limiterung der "Insert" Operation auf vServer Seite muss das 
		 *	Balancing Feld in 2 Teile geteilt werden.
		 *	
		 */
		 
		var round_count=0;				// zählt wie viel balancing Werte abgefragt wurden
		var bal_count=0;				// zählt die Anzahl, wie viel Zellen balancing aktiviert haben
		var block_count=0;				// zählt die Zellblocknummer 
		balancing=data[149].split("");
		for(i=0;i<72;i++)					
		{	
			temp=parseInt(balancing[i]);
			if(temp==1)
			{
				$('#balance'+i).addClass("status_balance_an");
				$('#balance'+i).html("AN");
				bal_count++;				
			}
			else
			{					
				$('#balance'+i).removeClass("status_balance_an");
				$('#balance'+i).html("AUS");							
			}
			
			// Beginn der Abfrage für die Anzahl von Zellen mit balancing pro Block 
			
			round_count++;
			if(round_count==12){
				if(bal_count>0)
				{
					$('#bal'+block_count).addClass("status_balance_an");
					$('#bal'+block_count).html(bal_count);					
				}
				else
				{
					$('#bal'+block_count).removeClass("status_balance_an");					
					$('#bal'+block_count).html("AUS");					
				}
				block_count++;
				bal_count=0;
				round_count=0;
			}
			
		}
		
		balancing=data[150].split("");
		for(i=72;i<144;i++)					
		{	
			temp=parseInt(balancing[i-72]);
			if(temp==1)
			{
				$('#balance'+i).addClass("status_balance_an");
				$('#balance'+i).html("AN");
				bal_count++;				
			}
			else
			{					
				$('#balance'+i).removeClass("status_balance_an");
				$('#balance'+i).html("AUS");							
			}
			
			// Beginn der Abfrage für die Anzahl von Zellen mit balancing pro Block 
			
			round_count++;
			if(round_count==12){
				if(bal_count>0)
				{
					$('#bal'+block_count).addClass("status_balance_an");
					$('#bal'+block_count).html(bal_count);					
				}
				else
				{
					$('#bal'+block_count).removeClass("status_balance_an");					
					$('#bal'+block_count).html("AUS");					
				}
				block_count++;
				bal_count=0;
				round_count=0;
			}
			
		}
		
		/**
		 *	Zelltemperaturen. mit der Variable tem wird der Wert wieder zurückgesetzt,
		 *	da die IDs immer bei 0 beginnen, müssen diese hier angepasst werden.
		 */
		
		for(i=150;i<201;i++)								// Zelltemperatur
		{
			var tem=i-151;								// IDs beginnen bei 0
			$('#temperatur'+tem) .html(data[i]+" °C");		
		}		
	});			
	setTimeout(executeQuery,1000);
};

