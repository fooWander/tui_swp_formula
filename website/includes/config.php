<?php

/* Konfigurationsdatei
 * Bitte füllen Sie vor der ersten Inbetriebnahme alle notwendigen Felder aus.
 * Diese sind für die Funktionalität dieses Produktes essentiell. 
 * */

/* Datenbankzugriff - Zugangsdatens */
$dbhost = 'localhost';											// Das kann so stehen bleiben.
$dbuname = 'root';  											// Hier den Datenbanknutzernamen eingeben.
$dbpass = '';   												// Hier das Datenbankpasswort eintragen.

$dbname_fd = 'fahrzeugdaten';									// Datenbanknamen für Fahrzeugdaten festlegen
$dbname_ud = 'nutzerdaten';										// Datenbanknamen für Userdaten festlegen
	
$accu_data = 'akkudaten'; 										// Tabelle: Akkudaten
$general_data = 'allgemeine_fahrzeugdaten';						// Tabelle: Allgemeine Fahrzeugdaten
$dynamic_data = 'dynamische_daten';								// Tabelle: Dynamische Daten
$engine_data = 'motor_umrichterdaten';							// Tabelle: Motor- und Umrichterdaten
$driving_data = 'fahrdynamikregelung';							// Tabelle: Fahrdynamikdaten

$user = 'benutzerdaten';										// Tabelle: Benutzerdaten
$rights = 'rechte';												// Tabelle: Rechtegruppen
$online = 'online_benutzer';									// Tabelle: Onlineuser

/* Sonstige Werte */
$mail = 'golda@gmx.net';										// Email-Adresse des Vorstands

$salt = 'tuilmenaufakia';										// Für Passwörter als zusätzlicher Schutz
$alg = '6'; 													// CRYPT_SHA512 als Verschlüsselungsalgorithmus (siehe Dokumentation von crypt())
$rounds = '5000'; 												// Anzahl der Verschlüsselungsrunden. Je größer desto besser, aber auch rechenlastiger.
$cryptsalt = '$' . $alg . '$rounds=' . $rounds . '$' . $salt;	// Endgültiger Salt

?>