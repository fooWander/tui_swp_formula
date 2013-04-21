//$('table').find('tr:gt(0)').hide();

// Einklappen der Tabelle (funktioniert bis dato nur mit FF; IE / Chrome klappen nicht aus, Opera klappt nicht ein)
$(document).ready(function() {
	$("button").click(function() {
		$("table.data").find("tr:gt(0)").toggle();
	});
});
