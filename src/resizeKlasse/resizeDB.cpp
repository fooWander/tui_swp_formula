#include "resizeDB.h"

  bool resizeDB:resDB(){
    return resDB(36000);
  }

  bool resizeDB::resDB(int norm){

	dbData db; 		/*!< Erstellung des dbData-Objektes um Zugriff auf die Datenbankdaten zu erhalten. */
        
	url = db.getHost(); 	/*!< Auslesen des Hostnamen der MySQL-Datenbank. */
        user = db.getUser(); 	/*!< Auslesen des Benutzername fuer die MySQL-Datenbank. */
        pass = db.getPW();	/*!< Auslesen des Passwortes fuer den Benutzer der MySQL-Datenbank. */
        database = db.getDB();	/*!< Auslesen des Namen der verwendeten MySQL-Datenbank. */
 	
	error = false;
	
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
              msg = "Keine Datensaetze in der Tabelle akkudaten geloescht. Aktuelle Anzahl an Eintraegen: ";
	      
	    }
	    lg.logWrite(5, msg);

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
          error = true;
	}
  return error;
}
