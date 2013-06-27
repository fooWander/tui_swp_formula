
/*
 *  Service Interface for Formula Student Car.
 *  Copyright (C) 2013
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "mysql_connection.h"
//Einbindung des MySQL Connector/C++
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
//Einbindung von boost
#include <boost/lexical_cast.hpp>

#include "dbData.h"


using namespace std;
using namespace sql::mysql;
using namespace boost;

/** Programm zum Loeschen veralteter Daten aus der Datenbank.
 *
 * Dieses Programm loggt sich in die Datenbank ein und ueberprueft die Tabellen auf die Anzahl ihrer
 * Eintraege. Sind mehr Datensaetze vorhanden als benoetigt, werden die
 * aeltesten automatisch geloescht.
 *
 * Das Programm ist so konzipiert, das es mittels eines Cronjobs periodisch aufgerufen
 * werden kann. Dieses Programm ist unabhaegig von den anderen auf dem virtuellem Server
 * laufenden Programmen, benoetigt jedoch die Datei dbconfig.txt um die Datenbank-
 * Zugriffsdaten auszulesen sowie den MySQL Connector/C++ und eine boost-Bibliothek.
 *
 * Beim Programmstart werden ueber die Klasse dbData die Zugangsdaten fuer die Datenbank bezogen und anschliessend eine
 * Verbindung zur Datenbank hergestellt.
 *
 * Ueber die Verbindung wird nun mittels eines MySQL-Statements (SELECT COUNT(*) FROM tabelle;) die Anzahl der Datensaetze
 * in der jeweiligen Tabelle ermittelt und mit dem Referenzwert verglichen.
 * Sind mehr Datensaetze in der Tabelle als vorgesehen, werden die aeltesten Eintraege mithilfe eines 
 * MySQL-Statements (DELETE FROM tabelle ORDER BY Zeitstempel LIMIT diff) geloescht.
 * Die Anzahl der geloeschten Eintraege richtet sich dabei nach der Differenz zwischen der aktuellen Datensatzanzahl
 * und dem Referenzwert.
 * Gemaess der Dokumentation des MySQL Connector/C++ werden auftretende Fehler abgefangen.
 * Damit das Programm auch sinnvoll von der Kommandozeile ausgefuehrt werden kann, etwa um die Datenbankverbindung zu testen, erfolgen
 * Ausgaben ueber den Bearbeitungsstand.
 */

  int main(){
	
	dbData db; /*!< Erstellung des dbData-Objektes um Zugriff auf die Datenbankdaten zu erhalten. */
        
	string url = db.getHost(); /*!< Auslesen des Hostnamen der MySQL-Datenbank. */
        string user = db.getUser(); /*!< Auslesen des Benutzername fuer die MySQL-Datenbank. */
        string pass = db.getPW(); /*!< Auslesen des Passwortes fuer den Benutzer der MySQL-Datenbank. */
        string database = db.getDB(); /*!< Auslesen des Namen der verwendeten MySQL-Datenbank. */

	int cur; /*!< Integervariable fuer die aktuelle Anzahl an Datensaetzen in der jeweiligen Tabelle. */ 
	int norm = 36000; /*!< Anzahl der in der Tabelle zu haltenden Datensaetze. */
	int diff; /*!< Anzahl zu loeschender Eintraege als die jeweilige Differenz zwischen der aktuellen Datensatzanzahl und dem Sollwert. */ 
		
	try{
          sql::Driver* driver = get_driver_instance(); /*!< Initialisierung der Datenbankverbindung. */
          std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass )); /*!< Herstellung der Verbindung zum Datenbankserver mittels Hostname, DB-Benutzer und Passwort. */
          con->setSchema(database); /*!< Auswahl der zu verwendenden Datenbank. */
          std::auto_ptr<sql::Statement> stmt(con->createStatement()); /*!< Erstellung eines Statments zur Ausfuehrung von Datenbankanweisungen. */
	  sql::ResultSet  *res; /*!< Pointer fuer das Ergebnis der Anweisung. */
        
	/**
	 * Tabelle akkudaten limitieren.
	 */  		
		
	  res = stmt->executeQuery("SELECT COUNT(*) FROM akkudaten;"); /*!< Aktuelle Anzahl an Datensaetzen in der Tabelle akkudaten abrufen. */ 
	  while (res->next()) { /*!< Ergebnis der Abfrage speichern und auswerten. */
                  cur = res->getInt(1);
          }
            if (cur > norm){ /*!< Pruefung ob mehr Datensaetze als vorgesehen vorhanden sind. */
              diff = cur - norm; /*!< Berechnung ueberfluessiger Datensaetze. */
              stmt->execute("DELETE FROM akkudaten ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";"); /*!< Loeschen ueberfluessiger Datensaetze. */
              cout << "Datensaetze aus Tabelle akkudaten geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle akkudaten geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
	    }

	/**
	 * Tabelle  allgemeine_fahrzeugdaten limitieren.
	 */
          res = stmt->executeQuery("SELECT COUNT(*) FROM allgemeine_fahrzeugdaten;"); /*!< Aktuelle Anzahl an Datensaetzen in der Tabelle allgemeine_fahrzeugdaten abrufen. */
          while (res->next()) { /*!< Ergebnis der Abfrage speichern und auswerten. */
            cur = res->getInt(1);
          }
            if (cur > norm){ /*!< Pruefung ob mehr Datensaetze als vorgesehen vorhanden sind. */
              diff = cur - norm; /*!< Berechnung ueberfluessiger Datensaetze. */
              stmt->execute("DELETE FROM allgemeine_fahrzeugdaten ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";"); /*!< Loeschen ueberfluessiger Datensaetze. */
              cout << "Datensaetze aus Tabelle allgemeine_fahrzeugdaten geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle allgemeine_fahrzeugdaten geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
            }

	/**
	 * Tabelle dynamische_daten limitieren.
	 */

          res = stmt->executeQuery("SELECT COUNT(*) FROM dynamische_daten;"); /*!< Aktuelle Anzahl an Datensaetzen in der Tabelle dynamische_daten abrufen. */
          while (res->next()) { /*!< Ergebnis der Abfrage speichern und auswerten. */
            cur = res->getInt(1);
          }
            if (cur > norm){ /*!< Pruefung ob mehr Datensaetze als vorgesehen vorhanden sind. */
              diff = cur - norm; /*!< Berechnung ueberfluessiger Datensaetze. */
              stmt->execute("DELETE FROM dynamische_daten ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";"); /*!< Loeschen ueberfluessiger Datensaetze. */
              cout << "Datensaetze aus Tabelle dynamische_daten geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle dynamische_daten geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
            }

	/**
	 * Tabelle fahrdynamikregelung limitieren.
	 */

          res = stmt->executeQuery("SELECT COUNT(*) FROM fahrdynamikregelung;"); /*!< Aktuelle Anzahl an Datensaetzen in der Tabelle fahrdynamikregelung abrufen. */
          while (res->next()) { /*!< Ergebnis der Abfrage speichern und auswerten. */
            cur = res->getInt(1);
          }
            if (cur > norm){ /*!< Pruefung ob mehr Datensaetze als vorgesehen vorhanden sind. */
              diff = cur - norm; /*!< Berechnung ueberfluessiger Datensaetze. */
              stmt->execute("DELETE FROM fahrdynamikregelung ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";"); /*!< Loeschen ueberfluessiger Datensaetze. */
              cout << "Datensaetze aus Tabelle fahrdynamikregelung geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle fahrdynamikregelung geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
            }

	/**
	 * Tabelle motor_umrichterdaten limitieren.
	 */

          res = stmt->executeQuery("SELECT COUNT(*) FROM motor_umrichterdaten;"); /*!< Aktuelle Anzahl an Datensaetzen in der Tabelle motor_umrichterdaten abrufen. */
	  while (res->next()) { /*!< Ergebnis der Abfrage speichern und auswerten. */
            cur = res->getInt(1);
          }
            if (cur > norm){ /*!< Pruefung ob mehr Datensaetze als vorgesehen vorhanden sind. */
              diff = cur - norm; /*!< Berechnung ueberfluessiger Datensaetze. */
              stmt->execute("DELETE FROM motor_umrichterdaten ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";"); /*!< Loeschen ueberfluessiger Datensaetze. */
              cout << "Datensaetze aus Tabelle motor_umrichterdaten geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle motor_umrichterdaten geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
            }


	}
	
	/** 
	 * Behandlung/Ausgabe von MySQL-Fehlern entsprechend der Dokumentation des MySQL Connector/C++.
	 */

	catch(sql::SQLException &e)
	{
          cout << "# ERR: SQLException in " << __FILE__;
          cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
          cout << "# ERR: " << e.what();
          cout << " (MySQL error code: " << e.getErrorCode();
          cout << ", SQLState: " << e.getSQLState() << " )" << endl;
          return EXIT_FAILURE;
	}
  return 0;
}
