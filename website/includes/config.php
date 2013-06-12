<?php

/* Konfigurationsdatei
 * Bitte f�llen Sie vor der ersten Inbetriebnahme alle notwendigen Felder aus.
 * Diese sind f�r die Funktionalit�t dieses Produktes essentiell. 
 * */

/* Datenbankzugriff - Zugangsdatens */
$dbhost = 'localhost';						// Das kann so stehen bleiben.
$dbuname = 'root';  						// Hier den Datenbanknutzernamen eingeben.
$dbpass = '';   							// Hier das Datenbankpasswort eintragen.

$dbname_fd = 'fahrzeugdaten';				// Datenbanknamen f�r Fahrzeugdaten festlegen
$dbname_ud = 'nutzerdaten';					// Datenbanknamen f�r Userdaten festlegen
	
$accu_data = 'akkudaten'; 					// Tabelle: Akkudaten
$general_data = 'allgemeine_fahrzeugdaten';	// Tabelle: Allgemeine Fahrzeugdaten
$dynamic_data = 'dynamische_daten';			// Tabelle: Dynamische Daten
$engine_data = 'motor_umrichterdaten';		// Tabelle: Motor- und Umrichterdaten
$driving_data = 'fahrdynamikregelung';		// Tabelle: Fahrdynamikdaten

$user = 'benutzerdaten';					// Tabelle: Benutzerdaten
$rights = 'rechte';							// Tabelle: Rechtegruppen
$online = 'online_benutzer';				// Tabelle: Onlineuser

/* Sonstige Werte */
$salt = 'tuilmenaufakia';					// F�r Passw�rter als zus�tzlicher Schutz

?>