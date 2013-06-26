#ifndef PacketInsert_H
#define PacketInsert_H

#include <iostream>
#include <string>
#include "Insert.h"
#include "DBPacketInsert.h"
#include "DatatypeDaemon.h"
#include "logData.h"

using namespace std;

/*!	Klasse zum Aufbau eines SQL-Strings.
*
*	Diese Klasse baut einen SQL-String mit Hilfe anderer Funktionen auf, mit dem
*	schließlich die Daten in die Datenbank geschrieben werden. Gleichzeitig findet eine
*	Wertebereichspruefung der Daten statt.
*	\sa DatatypeDaemon
*	\sa Insert
*/
class DBPacketInsert{
	public:
		//! Konstruktor der Klasse.
		DBPacketInsert();
		/** Memberfunktion zum Aufruf aus anderen Klassen.
		*
		*	Diese Funktion l\"ost den Aufruf von Unterfunktionen aus, die dann
		*	den SQL-String modular aufbauen und schließlich an Insert \"ubergeben.
		*	Gleichzeitig bietet sie die Schnittstelle zu den anderen Teilen des
		*	Programms.
		*/
		void db_insert();
	private:
		/** Eine Aufz\"ahlung der Trennstellen der Pakete.
		*
		*	Die Werte richten sich nach den Positionen im \"Ubertragungsvektor der
		*	MikroAutoBoxII. Der erste Wert hat dabei den Index 0.
		*	Wenn sich an diesem Vektor etwas \"andert, m\"ussen auch hier die Daten
		*	aktualisiert werden!
		*/
	    enum VektorTeile {
			allgemeineFahrzeugdaten = 0, //!< Beginn der allgemeinen Fahrzeugdaten.
			akkudaten = 17, 			 //!< Beginn der Akkudaten.
			dynamischeDaten = 358, 		 //!< Beginn der dynamischen Daten.
			fahrdynamikregelung = 383, 	 //!< Beginn der Daten f\"ur die Fahrdynamikregelung.
			motorUmrichterdaten = 385, 	 //!< Beginn der Motor- und Umrichterdaten.
			ende = 400};				 //!< Ende des \"Ubertragungsvektors.
	    //! Objekt zum Einf\"ugen in die Datenbank.
		//! Diesem wird der fertige SQL-String \"ubergeben.
		Insert insertMethodes;
		//! Der SQL-String mit der SQL-Anweisung. Er wird modular aufgebaut.
		string sql_anw;
		//! Array mit allen Werten aus einem Paket.
		string wertStuecke[341];
		//! Zeitstempel des Pakets.
		int time;
		//! Objekt zum Abholen und Aufbereiten der einzuf\"ugenden Werte.
		DatatypeDaemon slave;
		//! Diese Funktion baut die SQL-Anweisung f\"ur die Tabelle 'akkudaten' auf und prueft die Wertebereiche der Daten. Bei Fehlern wird false zurueckgegeben, anderenfalls true.
		bool insert_akkudaten();
		//! Diese Funktion baut die SQL-Anweisung f\"ur die Tabelle 'allgemeine_fahrzeugdaten' auf und prueft ebenfalls den Wertebereich.
		bool insert_allgemeineFahrzeugdaten();
		//! Diese Funktion baut die SQL-Anweisung f\"ur die Tabelle 'dynamische_daten' auf und prueft ebenfalls den Wertebereich.
		bool insert_dynamischeDaten();
		//! Diese Funktion baut die SQL-Anweisung f\"ur die Tabelle 'fahrdynamikregelung' auf und prueft ebenfalls den Wertebereich.
		bool insert_fahrdynamikregelung();
		//! Diese Funktion baut die SQL-Anweisung f\"ur die Tabelle 'motor_umrichterdaten' auf und prueft ebenfalls den Wertebereich.
		bool insert_motorUmrichterdaten();
};

#endif
