<?php 

include 'includes/config.php';

/**
 * Erzeugt einen beliebigen zufälligen String der aus zehn Zeichen besteht. Diese Länge ist der Standardwert.
 * Durch Aufruf der Funktion mit einem Integer als Parameter kann die Länge manuell angepasst werden.
 * @param number $length
 * @return string
 */
function generateRandomString($length = 10) {
	$characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"§$%&/()=?+*#-_^';
	$randomString = '';

	for ($i = 0; $i < $length; $i++) {
		$randomString .= $characters[rand(0, strlen($characters) - 1)];
	}

	return $randomString;
}

/**
 * Erstellt alle wichtigen Datenbanken, Tabellen, legt einen Vorstand mit den übegebenen Daten an
 * und richtet die Benutzergruppen 'Vorstand', 'Beobachter' und 'Techniker' an
 * @param array $register_data
 */
function install_system($register_data) {
	global $connect, $dbhost, $dbuname, $dbpass, $dbname_ud, $dbname_fd, $accu_data, $general_data, $dynamic_data, $engine_data, $driving_data, $user, $rights, $online, $cryptsalt;
	
	array_walk($register_data, 'array_sanitize');
	$register_data['passwort'] = crypt($register_data['passwort'],$cryptsalt);
	$fields = '`' . implode('`, `', array_keys($register_data)) . '`';
	$data = '\'' . implode('\', \'', $register_data) . '\'';
	
	// Verbindungsaufbau
	$connection = mysqli_connect("$dbhost", "$dbuname", "$dbpass") or die("Verbindung zur Datenbank konnte nicht hergestellt werden.");
	
	// Erstellen der Akkudaten-Tabelle
	$query_accu_data = "CREATE  TABLE IF NOT EXISTS $dbname_fd.$accu_data(
						  `zelldaten001` DECIMAL(4,3) NULL ,
						  `zelldaten002` DECIMAL(4,3) NULL ,
						  `zelldaten003` DECIMAL(4,3) NULL ,
						  `zelldaten004` DECIMAL(4,3) NULL ,
						  `zelldaten005` DECIMAL(4,3) NULL ,
						  `zelldaten006` DECIMAL(4,3) NULL ,
						  `zelldaten007` DECIMAL(4,3) NULL ,
						  `zelldaten008` DECIMAL(4,3) NULL ,
						  `zelldaten009` DECIMAL(4,3) NULL ,
						  `zelldaten010` DECIMAL(4,3) NULL ,
						  `zelldaten011` DECIMAL(4,3) NULL ,
						  `zelldaten012` DECIMAL(4,3) NULL ,
						  `zelldaten013` DECIMAL(4,3) NULL ,
						  `zelldaten014` DECIMAL(4,3) NULL ,
						  `zelldaten015` DECIMAL(4,3) NULL ,
						  `zelldaten016` DECIMAL(4,3) NULL ,
						  `zelldaten017` DECIMAL(4,3) NULL ,
						  `zelldaten018` DECIMAL(4,3) NULL ,
						  `zelldaten019` DECIMAL(4,3) NULL ,
						  `zelldaten020` DECIMAL(4,3) NULL ,
						  `zelldaten021` DECIMAL(4,3) NULL ,
						  `zelldaten022` DECIMAL(4,3) NULL ,
						  `zelldaten023` DECIMAL(4,3) NULL ,
						  `zelldaten024` DECIMAL(4,3) NULL ,
						  `zelldaten025` DECIMAL(4,3) NULL ,
						  `zelldaten026` DECIMAL(4,3) NULL ,
						  `zelldaten027` DECIMAL(4,3) NULL ,
						  `zelldaten028` DECIMAL(4,3) NULL ,
						  `zelldaten029` DECIMAL(4,3) NULL ,
						  `zelldaten030` DECIMAL(4,3) NULL ,
						  `zelldaten031` DECIMAL(4,3) NULL ,
						  `zelldaten032` DECIMAL(4,3) NULL ,
						  `zelldaten033` DECIMAL(4,3) NULL ,
						  `zelldaten034` DECIMAL(4,3) NULL ,
						  `zelldaten035` DECIMAL(4,3) NULL ,
						  `zelldaten036` DECIMAL(4,3) NULL ,
						  `zelldaten037` DECIMAL(4,3) NULL ,
						  `zelldaten038` DECIMAL(4,3) NULL ,
						  `zelldaten039` DECIMAL(4,3) NULL ,
						  `zelldaten040` DECIMAL(4,3) NULL ,
						  `zelldaten041` DECIMAL(4,3) NULL ,
						  `zelldaten042` DECIMAL(4,3) NULL ,
						  `zelldaten043` DECIMAL(4,3) NULL ,
						  `zelldaten044` DECIMAL(4,3) NULL ,
						  `zelldaten045` DECIMAL(4,3) NULL ,
						  `zelldaten046` DECIMAL(4,3) NULL ,
						  `zelldaten047` DECIMAL(4,3) NULL ,
						  `zelldaten048` DECIMAL(4,3) NULL ,
						  `zelldaten049` DECIMAL(4,3) NULL ,
						  `zelldaten050` DECIMAL(4,3) NULL ,
						  `zelldaten051` DECIMAL(4,3) NULL ,
						  `zelldaten052` DECIMAL(4,3) NULL ,
						  `zelldaten053` DECIMAL(4,3) NULL ,
						  `zelldaten054` DECIMAL(4,3) NULL ,
						  `zelldaten055` DECIMAL(4,3) NULL ,
						  `zelldaten056` DECIMAL(4,3) NULL ,
						  `zelldaten057` DECIMAL(4,3) NULL ,
						  `zelldaten058` DECIMAL(4,3) NULL ,
						  `zelldaten059` DECIMAL(4,3) NULL ,
						  `zelldaten060` DECIMAL(4,3) NULL ,
						  `zelldaten061` DECIMAL(4,3) NULL ,
						  `zelldaten062` DECIMAL(4,3) NULL ,
						  `zelldaten063` DECIMAL(4,3) NULL ,
						  `zelldaten064` DECIMAL(4,3) NULL ,
						  `zelldaten065` DECIMAL(4,3) NULL ,
						  `zelldaten066` DECIMAL(4,3) NULL ,
						  `zelldaten067` DECIMAL(4,3) NULL ,
						  `zelldaten068` DECIMAL(4,3) NULL ,
						  `zelldaten069` DECIMAL(4,3) NULL ,
						  `zelldaten070` DECIMAL(4,3) NULL ,
						  `zelldaten071` DECIMAL(4,3) NULL ,
						  `zelldaten072` DECIMAL(4,3) NULL ,
						  `zelldaten073` DECIMAL(4,3) NULL ,
						  `zelldaten074` DECIMAL(4,3) NULL ,
						  `zelldaten075` DECIMAL(4,3) NULL ,
						  `zelldaten076` DECIMAL(4,3) NULL ,
						  `zelldaten077` DECIMAL(4,3) NULL ,
						  `zelldaten078` DECIMAL(4,3) NULL ,
						  `zelldaten079` DECIMAL(4,3) NULL ,
						  `zelldaten080` DECIMAL(4,3) NULL ,
						  `zelldaten081` DECIMAL(4,3) NULL ,
						  `zelldaten082` DECIMAL(4,3) NULL ,
						  `zelldaten083` DECIMAL(4,3) NULL ,
						  `zelldaten084` DECIMAL(4,3) NULL ,
						  `zelldaten085` DECIMAL(4,3) NULL ,
						  `zelldaten086` DECIMAL(4,3) NULL ,
						  `zelldaten087` DECIMAL(4,3) NULL ,
						  `zelldaten088` DECIMAL(4,3) NULL ,
						  `zelldaten089` DECIMAL(4,3) NULL ,
						  `zelldaten090` DECIMAL(4,3) NULL ,
						  `zelldaten091` DECIMAL(4,3) NULL ,
						  `zelldaten092` DECIMAL(4,3) NULL ,
						  `zelldaten093` DECIMAL(4,3) NULL ,
						  `zelldaten094` DECIMAL(4,3) NULL ,
						  `zelldaten095` DECIMAL(4,3) NULL ,
						  `zelldaten096` DECIMAL(4,3) NULL ,
						  `zelldaten097` DECIMAL(4,3) NULL ,
						  `zelldaten098` DECIMAL(4,3) NULL ,
						  `zelldaten099` DECIMAL(4,3) NULL ,
						  `zelldaten100` DECIMAL(4,3) NULL ,
						  `zelldaten101` DECIMAL(4,3) NULL ,
						  `zelldaten102` DECIMAL(4,3) NULL ,
						  `zelldaten103` DECIMAL(4,3) NULL ,
						  `zelldaten104` DECIMAL(4,3) NULL ,
						  `zelldaten105` DECIMAL(4,3) NULL ,
						  `zelldaten106` DECIMAL(4,3) NULL ,
						  `zelldaten107` DECIMAL(4,3) NULL ,
						  `zelldaten108` DECIMAL(4,3) NULL ,
						  `zelldaten109` DECIMAL(4,3) NULL ,
						  `zelldaten110` DECIMAL(4,3) NULL ,
						  `zelldaten111` DECIMAL(4,3) NULL ,
						  `zelldaten112` DECIMAL(4,3) NULL ,
						  `zelldaten113` DECIMAL(4,3) NULL ,
						  `zelldaten114` DECIMAL(4,3) NULL ,
						  `zelldaten115` DECIMAL(4,3) NULL ,
						  `zelldaten116` DECIMAL(4,3) NULL ,
						  `zelldaten117` DECIMAL(4,3) NULL ,
						  `zelldaten118` DECIMAL(4,3) NULL ,
						  `zelldaten119` DECIMAL(4,3) NULL ,
						  `zelldaten120` DECIMAL(4,3) NULL ,
						  `zelldaten121` DECIMAL(4,3) NULL ,
						  `zelldaten122` DECIMAL(4,3) NULL ,
						  `zelldaten123` DECIMAL(4,3) NULL ,
						  `zelldaten124` DECIMAL(4,3) NULL ,
						  `zelldaten125` DECIMAL(4,3) NULL ,
						  `zelldaten126` DECIMAL(4,3) NULL ,
						  `zelldaten127` DECIMAL(4,3) NULL ,
						  `zelldaten128` DECIMAL(4,3) NULL ,
						  `zelldaten129` DECIMAL(4,3) NULL ,
						  `zelldaten130` DECIMAL(4,3) NULL ,
						  `zelldaten131` DECIMAL(4,3) NULL ,
						  `zelldaten132` DECIMAL(4,3) NULL ,
						  `zelldaten133` DECIMAL(4,3) NULL ,
						  `zelldaten134` DECIMAL(4,3) NULL ,
						  `zelldaten135` DECIMAL(4,3) NULL ,
						  `zelldaten136` DECIMAL(4,3) NULL ,
						  `zelldaten137` DECIMAL(4,3) NULL ,
						  `zelldaten138` DECIMAL(4,3) NULL ,
						  `zelldaten139` DECIMAL(4,3) NULL ,
						  `zelldaten140` DECIMAL(4,3) NULL ,
						  `zelldaten141` DECIMAL(4,3) NULL ,
						  `zelldaten142` DECIMAL(4,3) NULL ,
						  `zelldaten143` DECIMAL(4,3) NULL ,
						  `zelldaten144` DECIMAL(4,3) NULL ,
						  `MaxZellspannung` DECIMAL(4,3) NULL ,
						  `MinZellspannung` DECIMAL(4,3) NULL ,
						  `GesamtspannungAkku` DECIMAL(5,1) NULL,
						  `StromLadegerät` DECIMAL(5,1) NULL ,
						  `SpannungLadegerät` DECIMAL(5,1) NULL,
						  `Balancing` CHAR(72) NULL ,
						  `Balancing2` CHAR(72) NULL ,
						  `Zelltemperatur01` DECIMAL(4,1) NULL ,
						  `Zelltemperatur02` DECIMAL(4,1) NULL ,
						  `Zelltemperatur03` DECIMAL(4,1) NULL ,
						  `Zelltemperatur04` DECIMAL(4,1) NULL ,
						  `Zelltemperatur05` DECIMAL(4,1) NULL ,
						  `Zelltemperatur06` DECIMAL(4,1) NULL ,
						  `Zelltemperatur07` DECIMAL(4,1) NULL ,
						  `Zelltemperatur08` DECIMAL(4,1) NULL ,
						  `Zelltemperatur09` DECIMAL(4,1) NULL ,
						  `Zelltemperatur10` DECIMAL(4,1) NULL ,
						  `Zelltemperatur11` DECIMAL(4,1) NULL ,
						  `Zelltemperatur12` DECIMAL(4,1) NULL ,
						  `Zelltemperatur13` DECIMAL(4,1) NULL ,
						  `Zelltemperatur14` DECIMAL(4,1) NULL ,
						  `Zelltemperatur15` DECIMAL(4,1) NULL ,
						  `Zelltemperatur16` DECIMAL(4,1) NULL ,
						  `Zelltemperatur17` DECIMAL(4,1) NULL ,
						  `Zelltemperatur18` DECIMAL(4,1) NULL ,
						  `Zelltemperatur19` DECIMAL(4,1) NULL ,
						  `Zelltemperatur20` DECIMAL(4,1) NULL ,
						  `Zelltemperatur21` DECIMAL(4,1) NULL ,
						  `Zelltemperatur22` DECIMAL(4,1) NULL ,
						  `Zelltemperatur23` DECIMAL(4,1) NULL ,
						  `Zelltemperatur24` DECIMAL(4,1) NULL ,
						  `Zelltemperatur25` DECIMAL(4,1) NULL ,
						  `Zelltemperatur26` DECIMAL(4,1) NULL ,
						  `Zelltemperatur27` DECIMAL(4,1) NULL ,
						  `Zelltemperatur28` DECIMAL(4,1) NULL ,
						  `Zelltemperatur29` DECIMAL(4,1) NULL ,
						  `Zelltemperatur30` DECIMAL(4,1) NULL ,
						  `Zelltemperatur31` DECIMAL(4,1) NULL ,
						  `Zelltemperatur32` DECIMAL(4,1) NULL ,
						  `Zelltemperatur33` DECIMAL(4,1) NULL ,
						  `Zelltemperatur34` DECIMAL(4,1) NULL ,
						  `Zelltemperatur35` DECIMAL(4,1) NULL ,
						  `Zelltemperatur36` DECIMAL(4,1) NULL ,
						  `Zelltemperatur37` DECIMAL(4,1) NULL ,
						  `Zelltemperatur38` DECIMAL(4,1) NULL ,
						  `Zelltemperatur39` DECIMAL(4,1) NULL ,
						  `Zelltemperatur40` DECIMAL(4,1) NULL ,
						  `Zelltemperatur41` DECIMAL(4,1) NULL ,
						  `Zelltemperatur42` DECIMAL(4,1) NULL ,
						  `Zelltemperatur43` DECIMAL(4,1) NULL ,
						  `Zelltemperatur44` DECIMAL(4,1) NULL ,
						  `Zelltemperatur45` DECIMAL(4,1) NULL ,
						  `Zelltemperatur46` DECIMAL(4,1) NULL ,
						  `Zelltemperatur47` DECIMAL(4,1) NULL ,
						  `Zelltemperatur48` DECIMAL(4,1) NULL ,
						  `Zeitpunkt` INT(19) NOT NULL ,							  
						  `AkkuFehlerFeld` VARCHAR(45) NULL,
						  PRIMARY KEY (`Zeitpunkt`) )";
	
	// SQL-Code der Allgemeine Fahrzeugdaten Tabelle
	$query_general_data = "CREATE  TABLE IF NOT EXISTS $dbname_fd.$general_data(
						  `StatusNotaus` CHAR(10) NULL ,
						  `Temperatur01` DECIMAL(4,1) NULL ,
						  `Temperatur02` DECIMAL(4,1) NULL ,
						  `Temperatur03` DECIMAL(4,1) NULL ,
						  `Geschwindigkeit` DECIMAL(4,1) NULL ,
						  `Gaswert01` DECIMAL(4,1) NULL ,
						  `Gaswert02` DECIMAL(4,1) NULL ,
						  `AkkuGesamtspannung` DECIMAL(5,1) NULL ,
						  `AktuelleFahrzeugzeit` INT(10) NULL ,
						  `Zeitpunkt` INT(19) NOT NULL ,
						  `AllgFehlerFeld` VARCHAR(45) NULL,
						  PRIMARY KEY (`Zeitpunkt`) )";
	
	// SQL-Code der Dynamischen Fahrzeugdaten Tabelle
	$query_dynamic_data = "CREATE  TABLE IF NOT EXISTS $dbname_fd.$dynamic_data(
						  `XGeschwindigkeit` DECIMAL(4,1) NULL ,
						  `YGeschwindigkeit` DECIMAL(4,1) NULL ,
						  `ZGeschwindigkeit` DECIMAL(4,1) NULL ,
						  `XBeschleunigung` DECIMAL(4,1) NULL ,
						  `YBeschleunigung` DECIMAL(4,1) NULL ,
						  `ZBeschleunigung` DECIMAL(4,1) NULL ,
						  `XGierrate` DECIMAL(4,1) NULL ,
						  `YGierrate` DECIMAL(4,1) NULL ,
						  `ZGierrate` DECIMAL(4,1) NULL ,
						  `DrehzahlVRL` DECIMAL(5,1) NULL ,
						  `DrehzahlVRR` DECIMAL(5,1) NULL ,
						  `DrehzahlHRL` DECIMAL(5,1) NULL ,
						  `DrehzahlHRR` DECIMAL(5,1) NULL ,
						  `Wassertemperatur01` DECIMAL(4,1) NULL ,
						  `Wassertemperatur02` DECIMAL(4,1) NULL ,
						  `Bremsdruck` SMALLINT(3) NULL ,
						  `Bremskraft` DECIMAL(4,1) NULL ,
						  `Bremsposition` DECIMAL(4,1) NULL ,
						  `Federweg01` TINYINT(3) NULL ,
						  `Federweg02` TINYINT(3) NULL ,
						  `Federweg03` TINYINT(3) NULL ,
						  `Federweg04` TINYINT(3) NULL ,
						  `Gaspedalstellung01` DECIMAL(4,1) NULL ,
						  `Gaspedalstellung02` DECIMAL(4,1) NULL ,
						  `Lenkwinkel` SMALLINT(3) NULL ,
						  `Zeitpunkt` INT(19) NOT NULL ,
						  `DynFehlerFeld` VARCHAR(45) NULL,
						  PRIMARY KEY (`Zeitpunkt`) )";
	
	// SQL-Code der Motor- und Umrichterdaten Tabelle
	$query_engine_data = "CREATE  TABLE IF NOT EXISTS $dbname_fd.$engine_data(
						  `DCStrom` DECIMAL(4,1) NULL ,
						  `DCSpannung` DECIMAL(5,1) NULL ,
						  `Motortemperatur01` DECIMAL(4,1) NULL ,
						  `Motortemperatur02` DECIMAL(4,1) NULL ,
						  `Motortemperatur03` DECIMAL(4,1) NULL ,
						  `Motortemperatur04` DECIMAL(4,1) NULL ,
						  `Motortemperatur05` DECIMAL(4,1) NULL ,
						  `Motortemperatur06` DECIMAL(4,1) NULL ,
						  `Motortemperatur07` DECIMAL(4,1) NULL ,
						  `Motortemperatur08` DECIMAL(4,1) NULL ,
						  `Stromgrenze` DECIMAL(4,1) NULL ,
						  `Maximalleistung` DECIMAL(4,1) NULL ,
						  `Lüfterdrehzahl` INT(4) NULL ,
						  `Lüfter` DECIMAL(4,1) NULL ,
						  `Pumpe` DECIMAL(4,1) NULL ,
						  `Wassertemperatur` DECIMAL(4,1) NULL ,
						  `Zeitpunkt` INT(19) NOT NULL ,
						  `MotorFehlerFeld` VARCHAR(45) NULL,
						  PRIMARY KEY (`Zeitpunkt`) )";	
	
	// SQL-Code der Fahrdynamikregelung Tabelle
	$query_driving_data = "CREATE  TABLE IF NOT EXISTS $dbname_fd.$driving_data(
						  `Antriebschlupfregelung` DECIMAL(4,3) NULL ,
						  `TorqueVectoring` DECIMAL(4,3) NULL ,
						  `Zeitpunkt` INT(19) NOT NULL ,
						  `FahrdynFehlerFeld` VARCHAR(45) NULL,
						  PRIMARY KEY (`Zeitpunkt`) )";
	
	// SQL-Code der Nutzertabellen (Rechte-, Nutzer- und Onlinetabelle)
	$query_rights = "CREATE  TABLE IF NOT EXISTS $dbname_ud.$rights (
						  `id` INT NOT NULL AUTO_INCREMENT ,
						  `bezeichnung` VARCHAR(20) NOT NULL ,
						  PRIMARY KEY (`id`) )";
	$query_user = "CREATE  TABLE IF NOT EXISTS $dbname_ud.$user (
						  `id` INT NOT NULL AUTO_INCREMENT ,
						  `email` VARCHAR(45) NOT NULL ,
						  `vorname` VARCHAR(45) NOT NULL ,
						  `nachname` VARCHAR(45) NOT NULL ,
						  `passwort` CHAR(116) NOT NULL ,
						  `status` BIT NULL DEFAULT 0 ,
						  `rechte` INT NULL ,
						  PRIMARY KEY (`id`, `email`) ,
						  INDEX `id_idx` (`rechte` ASC) ,
						  CONSTRAINT `rechte`
						  FOREIGN KEY (`rechte` )
						  REFERENCES $dbname_ud.$rights (`id` )
						  ON DELETE NO ACTION
						  ON UPDATE NO ACTION)";
	$query_online = "CREATE  TABLE IF NOT EXISTS $dbname_ud.$online (
						  `id` INT NOT NULL ,
						  `zeitpunkt` TIMESTAMP NULL ,
						  INDEX `id_idx` (`id` ASC) ,
						  CONSTRAINT `id`
						  FOREIGN KEY (`id` )
						  REFERENCES $dbname_ud.$user (`id` )
						  ON DELETE NO ACTION
						  ON UPDATE NO ACTION)";
	
	// SQL-Code der Nutzertabellen (Rechte-, Nutzer- und Onlinetabelle)
	$query_rights = "CREATE  TABLE IF NOT EXISTS $dbname_ud.$rights (
							`id` INT NOT NULL AUTO_INCREMENT ,
							`bezeichnung` VARCHAR(20) NOT NULL ,
							PRIMARY KEY (`id`) )";
	$query_user = 	"CREATE  TABLE IF NOT EXISTS $dbname_ud.$user (
							`id` INT NOT NULL AUTO_INCREMENT ,
							`email` VARCHAR(45) NOT NULL ,
							`vorname` VARCHAR(45) NOT NULL ,
							`nachname` VARCHAR(45) NOT NULL ,
							`passwort` CHAR(116) NOT NULL ,
							`status` BIT NULL DEFAULT 0 ,
							`rechte` INT NULL ,
							PRIMARY KEY (`id`, `email`) ,
							INDEX `id_idx` (`rechte` ASC) ,
							CONSTRAINT `rechte`
							FOREIGN KEY (`rechte` )
							REFERENCES $dbname_ud.$rights (`id` )
							ON DELETE NO ACTION
							ON UPDATE NO ACTION)";
	$query_online = "CREATE  TABLE IF NOT EXISTS $dbname_ud.$online (
							`id` INT NOT NULL ,
							`zeitpunkt` INT(10) NULL ,
							INDEX `id_idx` (`id` ASC) ,
							CONSTRAINT `id`
							FOREIGN KEY (`id` )
							REFERENCES $dbname_ud.$user (`id` )
							ON DELETE NO ACTION
							ON UPDATE NO ACTION)";
	
	// Einfügen der Benutzergruppen
	$query_insert_rights = "INSERT INTO $dbname_ud.$rights (`id`, `bezeichnung`) VALUES (NULL, 'Vorstand'), (NULL, 'Beobachter'), (NULL, 'Techniker');";
	
	// Überprüfen der Verbindung
	echo "<h2>MySQL-Verbindungsaufbau ...</h2>\n";
	if (mysqli_connect_errno())
	{
		echo "		MySQL-Verbindungsaufbau fehlgeschlagen: <br>		<i>" . mysqli_connect_error($connection) . "</i> <br>\n";
	}
	
	// Datenbanken erstellen
	echo "		<h2>Erstellen der Nutzer- und Fahrzeugdatenbank</h2>\n";
	$sql = "CREATE DATABASE $dbname_fd";
	if (mysqli_query($connection, $sql)) {
		echo "		Die Datenbank für die <strong>Fahrzeugdaten</strong> wurde erfolgreich angelegt.<br>\n";
	} else {
		echo "		Es ist ein Fehler beim Erstellen der Datenbank für die <strong>Fahrzeugdaten</strong> aufgetreten: <br>		<i>" . mysqli_error($connection) . "</i> <br>\n";
	}
	
	$sql = "CREATE DATABASE $dbname_ud";
	if (mysqli_query($connection, $sql)) {
		echo "		Die Datenbank für die <strong>Nutzerdaten</strong> wurde erfolgreich angelegt.<br>\n";
	} else {
		echo "		Es ist ein Fehler beim Erstellen der Datenbank für die <strong>Nutzerdaten</strong> aufgetreten: <br>		<i>" . mysqli_error($connection) . "</i> <br>\n";
	}
	
	// Erstellen der Tabelle für die Benutzerdaten inkl. Informationen über Erfolg / Misserfolg
	echo "		<h2>Erstellen der einzelnen Nutzer-Tabellen</h2>\n";
	if (mysqli_query($connection, $query_rights)) {
		echo "		Die Tabelle für die <strong>Rechtegruppen</strong> wurde erfolgreich erstellt.<br>\n";
	} else {
		echo "		Fehler beim Erstellen der Tabelle für die <strong>Rechtegruppen</strong>: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}
	
	if (mysqli_query($connection, $query_insert_rights)) {
		echo "		Die <strong>Benutzergruppen</strong> wurden erfolgreich eingerichtet.<br>\n";
	} else {
		echo "		Es ist ein Fehler beim Erstellen der <strong>Benutzergruppen</strong> aufgetreten: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}
	
	if (mysqli_query($connection, $query_user)) {
		echo "		Die Tabelle für die <strong>Nutzerkonten</strong> wurde erfolgreich erstellt.<br>\n";
	} else {
		echo "		Fehler beim Erstellen der Tabelle für die <strong>Nutzerkonten</strong>: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}
	
	if (mysqli_query($connection, $query_online)) {
			echo "		Die Tabelle für die <strong>Online-User</strong> wurde erfolgreich erstellt.<br>\n";
	} else {
			echo "		Fehler beim Erstellen der Tabelle für die <strong>Online-User</strong>: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}
	
	// Erstellen der Tabelle für die Fahrzeugdaten inkl. Informationen über Erfolg / Misserfolg
	echo "		<h2>Erstellen der einzelnen Fahrzeug-Tabellen</h2>\n";
	if (mysqli_query($connection, $query_accu_data)) {
		echo "		Die Tabelle der <strong>Akkudaten</strong> wurde erfolgreich erstellt.<br>\n";
	} else {
		echo "		Fehler beim Erstellen der Tabelle der <strong>Akkudaten</strong>: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}
	
	if (mysqli_query($connection, $query_general_data)) {
		echo "		Die Tabelle der <strong>Allgemeinen Fahrzeugdaten</strong> wurde erfolgreich erstellt.<br>\n";
	} else {
		echo "		Fehler beim Erstellen der Tabelle der <strong>Allgemeinen Fahrzeugdaten</strong>: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}

	if (mysqli_query($connection, $query_engine_data)) {
		echo "		Die Tabelle der <strong>Motor- und Umrichterdaten</strong> wurde erfolgreich erstellt.<br>\n";
	} else {
		echo "		Fehler beim Erstellen der Tabelle der <strong>Motor- und Umrichterdaten</strong>: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}

	if (mysqli_query($connection, $query_dynamic_data)) {
		echo "		Die Tabelle der <strong>dynamischen Fahrzeugdaten</strong> wurde erfolgreich erstellt.<br>\n";
	} else {
		echo "		Fehler beim Erstellen der Tabelle der <strong>dynamischen Fahrzeugdaten</strong>: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}

	if (mysqli_query($connection, $query_driving_data)) {
		echo "		Die Tabelle der <strong>Fahrdynamikregelung</strong> wurde erfolgreich erstellt.<br>\n";
	} else {
		echo "		Fehler beim Erstellen der Tabelle der <strong>Fahrdynamikregelung</strong>: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}	
	
	mysqli_select_db($connect,$dbname_ud);
	if (mysqli_query($connect, "INSERT INTO `" . $user . "` (`email`,`vorname`,`nachname`,`passwort`,`status`,`rechte`) VALUES ($data, b'1', '1')")) {
		echo "		Der Vorstand wurde erfolgreich angelegt.<br>\n";
	} else {
		echo "		Beim Erstellen des Vorstands ist ein Fehler aufgetreten: <br>		<i>" . mysqli_error($connection) ."</i> <br>\n";
	}
}

/**
 * Arbeitet ähnlich wie protect_page(), verhindert dass angemeldete Benutzer auf Seiten zugreifen, deren Zugriff für einen bereits registrierten Nutzer keinen Sinn ergibt. (z.B. die Registrierungsseite)
 */
function logged_in_redirect() {
	if (logged_in() == true) {
		header('Location: index.php');
		exit();		
	}
}

/**
 * Prüft beim Aufruf der Funktion ob der Benutzer eingeloggt ist und leitet ihn, falls dies nicht der Fall ist, auf die Startseite um.
 */
function protect_page() {
	if (logged_in() == false) {
		header('Location: index.php?denied');
		exit();
	}
}

/**
 * Bereitet ein Array von Strings auf, umd SQL-Injections vorzubeugen.
 * @param array $item
 */
function array_sanitize(&$item) {
	global $connect;
	$item = mysqli_real_escape_string($connect,$item);
}

/**
 * Bereitet einen String auf, um vor SQL-Injections zu schützen.
 * @param string $data
 * @return string
 */
function sanitize($data) {
	global $connect;
	return mysqli_real_escape_string($connect,$data);
}

/**
 * Gibt gesammelte und übergebene Fehler in geordneter Weise aus.
 * @param array $errors
 * @return string
 */
function output_errors($errors) {
	$output = array();
	foreach ($errors as $error) {
		$output[] = '<li><p class="fehlermeldung">' . $error . '</p></li>';
	}
	return '<ul class="error">' . implode('', $output) . '</ul>';
}

?>