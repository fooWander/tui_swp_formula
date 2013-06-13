<?php
?>
<div class="item">
	<h2>Nutzerverwaltung</h2>
	<p style="width: 425px; padding: 5px; padding-bottom: 0px;">Geben Sie in das nachfolgende Textfeld eine ID (siehe Tabelle) ein und wählen Sie mittels der Checkboxen aus ob Sie den Nutzer aktivieren oder löschen wollen.</p><br>
	<?php 
		if (isset($_GET['notaccepted'])) {
	?>
	<p class="alert_small">Vorgang konnte nicht durchgeführt werden. Bitte versuchen Sie es erneut, und überprüfen Sie ob alle Felder ordnungsgemäß ausgefüllt bzw. ausgewählt wurden.<br><?php echo output_errors($errors)?></p>
	<?php 
		}
		if (isset($_GET['accepted'])) {
	?>
	<p class="alert_short">Änderungen wurden erfolgreich ausgeführt.</p>
	<?php 
		}
	?>
	<form id="login" action="core/functions/accept.php" method="post">
		<ul style="width: 260px;">
			<li>
				<input type="text" name="userid" placeholder="ID-Nummer">
			</li>
			<li>
				<p>Aktivieren</p> <input type="radio" name="manage" value="activate">		
			</li>
			<li>
				<p>Löschen</p> <input type="radio" name="manage" value="delete">		
			</li>
			<li>
				<select name="rights">
					<option value="beobachter">Beobachter</option>
					<option value="vorstand">Vorstand</option>
					<option value="techniker">Techniker</option>
				</select>
			</li>
			<li>
				<input type="submit" value="Ausführen" class="submit">
			</li>
		</ul>
	</form>
</div>
<?php
?>