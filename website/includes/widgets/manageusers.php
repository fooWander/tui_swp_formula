<?php
?>
<div class="item">
	<h2>Nutzerverwaltung</h2>
	<p style="width: 425px; padding: 5px; padding-bottom: 0px;">Geben Sie in das nachfolgende Textfeld eine ID (siehe Tabelle) ein und w�hlen Sie mittels der Checkboxen aus ob Sie den Nutzer aktivieren oder l�schen wollen.</p><br>
	<?php 
		if (isset($_GET['notaccepted'])) {
	?>
	<p class="alert_small">Vorgang konnte nicht durchgef�hrt werden. Bitte versuchen Sie es erneut, und �berpr�fen Sie ob alle Felder ordnungsgem�� ausgef�llt bzw. ausgew�hlt wurden.<br><?php echo output_errors($errors)?></p>
	<?php 
		}
		if (isset($_GET['accepted'])) {
	?>
	<p class="alert_short">�nderungen wurden erfolgreich ausgef�hrt.</p>
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
				<p>L�schen</p> <input type="radio" name="manage" value="delete">		
			</li>
			<li>
				<select name="rights">
					<option value="beobachter">Beobachter</option>
					<option value="vorstand">Vorstand</option>
					<option value="techniker">Techniker</option>
				</select>
			</li>
			<li>
				<input type="submit" value="Ausf�hren" class="submit">
			</li>
		</ul>
	</form>
</div>
<?php
?>