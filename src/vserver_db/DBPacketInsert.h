#ifndef PacketInsert_H
#define PacketInsert_H

#include <iostream>
#include <string>
#include "Insert.h"
#include "DBPacketInsert.h"
#include "DatatypeDaemon.h"

using namespace std;

/*!	Klasse zum Aufbau eines SQL-Strings.
*
*	Diese Klasse baut einen SQL-String mit Hilfe anderer Klassen auf, mit dem
*	schließlich die Daten in die Datenbank geschrieben werden.
*	\sa DatatypeDaemon
*	\sa Insert
*/
class DBPacketInsert{
	public:
		//! Konstruktor der Klasse.
		DBPacketInsert();
		/** Memberfunktion zum Aufruf aus anderen Klassen.
		*
		*	Diese Funktion löst den Aufruf von Unterfunktionen aus, die dann
		*	den SQL-String modular aufbauen und schließlich an Insert übergeben.
		*	Gleichzeitig bietet sie die Schnittstelle zu den anderen Teilen des
		*	Programms.
		*/
		void db_insert();
	private:
		/** Eine Aufzählung der Trennstellen der Pakete.
		*
		*	Die Werte richten sich nach den Positionen im Übertragungsvektor der
		*	MikroAutoBoxII. Der erste Wert hat dabei den Index 0.
		*	Wenn sich an diesem Vektor etwas ändert, müssen auch hier die Daten
		*	aktualisiert werden!
		*/
	    enum VektorTeile {
			allgemeineFahrzeugdaten = 0, //!< Beginn der allgemeinen Fahrzeugdaten.
			akkudaten = 17, 			 //!< Beginn der Akkudaten.
			dynamischeDaten = 358, 		 //!< Beginn der dynamischen Daten.
			fahrdynamikregelung = 383, 	 //!< Beginn der Daten für die Fahrdynamikregelung.
			motorUmrichterdaten = 385, 	 //!< Beginn der Motor- und Umrichterdaten.
			ende = 400};				 //!< Ende des Übertragungsvektors.
	    //! Objekt zum Einfügen in die Datenbank.
		//! Diesem wird der fertige SQL-String übergeben.
		Insert insertMethodes;
		//! Der SQL-String mit der SQL-Anweisung. Er wird modular aufgebaut.
		string sql_anw;
		//! Array mit allen Werten aus einem Paket.
		string wertStuecke[341];
		//! Zeitstempel des Pakets.
		int time;
		//! Objekt zum Abholen und Aufbereiten der einzufügenden Werte.
		DatatypeDaemon slave;
		//! Diese Funktion baut die SQL-Anweisung für die Tabelle 'akkudaten' auf.
		void insert_akkudaten();
		//! Diese Funktion baut die SQL-Anweisung für die Tabelle 'allgemeine_fahrzeugdaten' auf.
		void insert_allgemeineFahrzeugdaten();
		//! Diese Funktion baut die SQL-Anweisung für die Tabelle 'dynamische_daten' auf.
		void insert_dynamischeDaten();
		//! Diese Funktion baut die SQL-Anweisung für die Tabelle 'fahrdynamikregelung' auf.
		void insert_fahrdynamikregelung();
		//! Diese Funktion baut die SQL-Anweisung für die Tabelle 'motor_umrichterdaten' auf.
		void insert_motorUmrichterdaten();
};

#endif
