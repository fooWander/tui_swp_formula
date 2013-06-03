// Einklappen der Tabelle
/*
$(document).ready(function() {
	$("button").click(function() {
		$("table.data").find("tr:gt(0)").toggle();
	});
});
*/

// Contentboxen auf der Seite in zwei Spalten anordnen
$(function(){
	$('.content').masonry({
		// options
		itemSelector : '.item',
		columnWidth: function( containerWidth ) {
			return containerWidth / 2; }
	});
});