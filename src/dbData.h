#ifndef DBDATA_H
#define DBDATA_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

	/**	\brief Klasse zum Auslesen der Zugangsdaten für die Datenbank.
	*
	*	Diese Klasse liest die Zugangsdaten aus einer Textdatei (dbconfig.txt) aus und stellt
	*	sie über Memberfunktionen bereit.
	*	\sa Insert
	*
	*/
  class dbData
  {
    public:
	  /**
	  *	Konstruktor der Klasse. Hier werden die Zugangsdaten aus der Textdatei in die entsprechenden
	  * lokalen Variablen eingelesen.
	  */
      dbData();
	  //! Memberfunktion, die die Hostadresse bereitstellt.
	  /*!
	  *	Wird von Insert aufgerufen.
	  * \return Die Hostadresse.
	  */
      string getHost();
	  //! Memberfunktion, die den Benutzernamen für die Datenbank bereitstellt.
	  /*!
	  *	\return Der Nutzername.
	  */
      string getUser();
	  //! Memberfunktion, die das Passwort der Datenbank bereitstellt.
	  /*!
	  *	\return Das Passwort für die Datenbank und den Nutzer.
	  */
      string getPW();
	  //! Memberfunktion, die den Namen der Datenbank bereitstellt.
	  /*!
	  *	\return Der Name der Datenbank.
	  */
      string getDB();
    private:
      string host;	//!< speichert die Hostadresse zwischen.
      string user;	//!< speichert den Benutzernamen zwischen.
      string pw;	//!< speichert das Passwort zwischen.
      string db;	//!< speichert den Namen der Datenbank zwischen.

  };

#endif

