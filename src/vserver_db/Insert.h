#ifndef Insert_H
#define Insert_H
#include "dbData.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
/* uncomment for applications that use vectors */
/*#include <vector>*/

#include "mysql_connection.h"
//#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>

using namespace std;
using namespace sql::mysql;

/** \brief Klasse zum Aufbauen einer Verbindung zur Datenbank und Einfügen
*		von Daten.
*
*	In dieser Klasse wird die eigentliche Kommunikation mit der MySQL-Datenbank
*	realisiert. Hierzu wird der MySQL Connector/C++ benutzt. Die Zugangsdaten
*	werden dafür mit Hilfe einer anderen Klasse aus einer Textdatei ausgelesen.
*/
class Insert
{

public:
	/**
	*	Konstruktor der Klasse. Hier werden die Verbindungsdaten ermittelt.
	*/
	Insert();

	/**
	*	Verbindung aufbauen und MySQL-String an die Datenbank schicken.
	*	Diese führt ihn dann aus.
	*	\param anw ist ein Zeiger auf einen in DBPacketInsert aufgebauten SQL-String,
	*		der an diese Funktion übergeben wird.
	*	\return Integerwert, der aber nicht verwendet wird.
	*/
	int insertIntoDB(string* anw);

private:
	string url;			//!< speichert die Adresse der Datenbank.
	string user;		//!< speichert den Benutzernamen.
	string pass;		//!< speichert das Passwort für die Datenbank und den Nutzer.
	string database;	//!< speichert den Namen der Datenbank
};

#endif
