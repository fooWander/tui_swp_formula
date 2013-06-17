#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <boost/lexical_cast.hpp>

#include "dbData.h"


using namespace std;
using namespace sql::mysql;
using namespace boost;

  int main(){

	//Auslesen der Datenbankzugriffsdaten aus der Konfigurationsdatei und Speicherung in Variablen
	dbData db;
	string url, user, pass, database;
        
	url = db.getHost();
        user = db.getUser();
        pass = db.getPW();
        database = db.getDB();

	//Variablen fuer die Datnsatzanzahl, Sollanzahl und die Anzahl der zu loeschenden Eintraege
	int cur, norm, diff;
	//Destlegung der maximalen Anzahl an zulaessigen Datensaetzen
	norm = 36000;
		
	try{
	  //Initialisierung der Datenbankverbindung 
          sql::Driver* driver = get_driver_instance();
	  //Verbuindung mittels Hostname, Benutzer und Passwort
          std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass ));
	  //Auswahl der Datenbank
          con->setSchema(database);
	  //Erstellung eines Statments zur Ausfuehrung von Datenbankanweisungen
          std::auto_ptr<sql::Statement> stmt(con->createStatement());
	  //Pointer fuer das Ergebnis der Anweisung
	  sql::ResultSet  *res;
        
		
	//Tabelle akkudaten limitieren
		
	  //Aktuelle Anzahl an Datensaetzen in der Tabelle akkudaten abrufen
	  res = stmt->executeQuery("SELECT COUNT(*) FROM akkudaten;");
	  //Ergebnis der Abfrage speichern und auswerten
	  while (res->next()) {
                  cur = res->getInt(1);
          }
	  //Pruefung ob mehr Datensaetze als der Soll vorhanden sind
            if (cur > norm){	
	      //Berechnung ueberfluessiger Datensaetze
              diff = cur - norm;
	      //Loeschen ueberfluessiger Datensaetze
              stmt->execute("DELETE FROM akkudaten ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";");
              cout << "Datensaetze aus Tabelle akkudaten geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle akkudaten geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
	    }


	//Tabelle  allgemeine_fahrzeugdaten limitieren

	  //Aktuelle Anzahl an Datensaetzen in der Tabelle allgemeine_fahrzeugdaten abrufen
          res = stmt->executeQuery("SELECT COUNT(*) FROM allgemeine_fahrzeugdaten;");
          //Ergebnis der Abfrage speichern und auswerten
          while (res->next()) {
            cur = res->getInt(1);
          }
          //Pruefung ob mehr Datensaetze als der Soll vorhanden sind
            if (cur > norm){
              //Berechnung ueberfluessiger Datensaetze
              diff = cur - norm;
              //Loeschen ueberfluessiger Datensaetze
              stmt->execute("DELETE FROM allgemeine_fahrzeugdaten ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";");
              cout << "Datensaetze aus Tabelle allgemeine_fahrzeugdaten geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle allgemeine_fahrzeugdaten geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
            }


	//Tabelle dynamische_daten limitieren

          //Aktuelle Anzahl an Datensaetzen in der Tabelle dynamische_daten abrufen
          res = stmt->executeQuery("SELECT COUNT(*) FROM dynamische_daten;");
          //Ergebnis der Abfrage speichern und auswerten
          while (res->next()) {
            cur = res->getInt(1);
          }
          //Pruefung ob mehr Datensaetze als der Soll vorhanden sind
            if (cur > norm){
              //Berechnung ueberfluessiger Datensaetze
              diff = cur - norm;
              //Loeschen ueberfluessiger Datensaetze
              stmt->execute("DELETE FROM dynamische_daten ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";");
              cout << "Datensaetze aus Tabelle dynamische_daten geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle dynamische_daten geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
            }


	//Tabelle fahrdynamikregelung limitieren

          //Aktuelle Anzahl an Datensaetzen in der Tabelle fahrdynamikregelung abrufen
          res = stmt->executeQuery("SELECT COUNT(*) FROM fahrdynamikregelung;");
          //Ergebnis der Abfrage speichern und auswerten
          while (res->next()) {
            cur = res->getInt(1);
          }
          //Pruefung ob mehr Datensaetze als der Soll vorhanden sind
            if (cur > norm){
              //Berechnung ueberfluessiger Datensaetze
              diff = cur - norm;
              //Loeschen ueberfluessiger Datensaetze
              stmt->execute("DELETE FROM fahrdynamikregelung ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";");
              cout << "Datensaetze aus Tabelle fahrdynamikregelung geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle fahrdynamikregelung geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
            }


	//Tabelle motor_umrichterdaten limitieren

          //Aktuelle Anzahl an Datensaetzen in der Tabelle motor_umrichterdaten abrufen
          res = stmt->executeQuery("SELECT COUNT(*) FROM motor_umrichterdaten;");
	  //Ergebnis der Abfrage speichern und auswerten
	  while (res->next()) {
            cur = res->getInt(1);
          }
          //Pruefung ob mehr Datensaetze als der Soll vorhanden sind
            if (cur > norm){
              //Berechnung ueberfluessiger Datensaetze
              diff = cur - norm;
              //Loeschen ueberfluessiger Datensaetze
              stmt->execute("DELETE FROM motor_umrichterdaten ORDER BY Zeitpunkt LIMIT " + lexical_cast<string>(diff) + ";");
              cout << "Datensaetze aus Tabelle motor_umrichterdaten geloescht: " << diff << endl;
            }
            else
            {
              cout << "Keine Datensaetze in der Tabelle motor_umrichterdaten geloescht. Aktuelle Anzahl an Eintraegen: " << cur << endl;
            }


	}
	//Behandlung/Ausgabe von MySQL-Fehlern
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
