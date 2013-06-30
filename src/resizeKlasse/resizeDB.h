#ifndef RESIZEDB_H
#define RESIZEDB_H


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
 * Dieses Programm loggt sich in die Datenbank ein und ueberprueft die Tabellen auf die Anzahl ihrer * Eintraege. Sind mehr Datensaetze vorhanden als benoetigt, werden die
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

class resizeDB
{
  public:
      //!Memberfunktion, die zur Datenbank verbindet und ueberfluessige Eintraege loescht
      /*!
      *  Wird von DBresize aufgerufen.
      *  \return Information, ob die Aktion erfolgreich war als Boolean.
      */
    bool resDB(int norm);
    
    bool resDB();
      //!Memberfunktion, welche die Ueberladene Memberfunktion mit festgelegt norm-Parameter aufruft
      /*!
      *  Koennte von innerhalb eines Programms aufgerufen werden, ohne einen norm-Parameter zu uebergeben.
      *  Dieser wird dann auf den voreingestellten Wert von 36000 festgelegt.
      *  \return Information, ob die Aktion erfolgreich war als Boolean.
      */  

  private:
      string url; 	/*!< Auslesen des Hostnamen der MySQL-Datenbank. */
      string user;	/*!< Auslesen des Benutzername fuer die MySQL-Datenbank. */
      string pass;	/*!< Auslesen des Passwortes fuer den Benutzer der MySQL-Datenbank. */
      string database;	/*!< Auslesen des Namen der verwendeten MySQL-Datenbank. */

      string msg;       /*!< String fuer eine Loggingausgabe. */
      bool error;       /*!< Variable um Fehler Festzustellen. */


      int cur; 		/*!< Integervariable fuer die aktuelle Anzahl an Datensaetzen in der jeweiligen Tabelle. */
      int norm;		/*!< Anzahl der in der Tabelle zu haltenden Datensaetze. */
      int diff; 	/*!< Anzahl zu loeschender Eintraege als die jeweilige Differenz zwischen der aktuellen Datensatzanzahl und dem Sollwert. */

};

#endif
