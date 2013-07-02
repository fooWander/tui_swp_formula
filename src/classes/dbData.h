#ifndef DBDATA_H
#define DBDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "logData.h"

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


          //! Memberfunktion, die den Parameter PACKAGE_SIZE_MAX bereitstellt.
          /*!
          * \return PACKAGE_SIZE_MAX.
          */
      //int getPACKAGE_SIZE_MAX();

          //! Memberfunktion, die den Parameter ACK_SIZE_MAX bereitstellt.
          /*!
          * \return ACK_SIZE_MAX.
          */
      //int getACK_SIZE_MAX();

          //! Memberfunktion, die den Parameter DATA_NUM bereitstellt.
          /*!
          * \return DATA_NUM.
          */
      //int getDATA_NUM();

          //! Memberfunktion, die den Parameter DATA_NUM_OF_BYTES bereitstellt.
          /*!
          * \return DATA_NUM_OF_BYTES.
          */
      //int getDATA_NUM_OF_BYTES();

          //! Memberfunktion, welche die IP des Embetted-PC bereitstellt.
          /*!
          * \return EMBPC_IP.
          */
      //string getEMBPC_IP();

          //! Memberfunktion, welche die IP der Microautobox II bereitstellt.
          /*!
          * \return MABXII_IP.
          */
      //string getMABXII_IP();

          //! Memberfunktion, welche die IP des vServers bereitstellt.
          /*!
          * \return VSERVER_IP.
          */
      //string getVSERVER_IP();

          //! Memberfunktion, welche die Portnummer der MABXII bereitstellt.
          /*!
          * \return MABXII_PORT.
          */
      //int getMABXII_PORT();

          //! Memberfunktion, welche die Infoportnummer der MABXII bereitstellt.
          /*!
          * \return MABXII_INFO_PORT.
          */
      //int getMABXII_INFO_PORT();

          //! Memberfunktion, welche die Portnummer des Embedded-PC bereitstellt.
          /*!
          * \return EMBPC_PORT.
          */
      //int getEMBPC_PORT();

          //! Memberfunktion, welche die Infoportnummer des Embedded-PC bereitstellt.
          /*!
          * \return EMBPC_INFO_PORT.
          */
      //int getEMBPC_INFO_PORT();

          //! Memberfunktion, welche die Portnummer des vServers bereitstellt.
          /*!
          * \return VSERVER_PORT.
          */
      //int getVSERVER_PORT();

          //! Memberfunktion, welche die Infoportnummer des vServers bereitstellt.
          /*!
          * \return VSERVER_INFO_PORT.
          */
      //int getVSERVER_INFO_PORT();

          //! Memberfunktion, die den Parameter MSG_READY_1 bereitstellt.
          /*!
          * \return MSG_READY_1.
          */
      //int getMSG_READY_1();

          //! Memberfunktion, die den Parameter MSG_READY_2 bereitstellt.
          /*!
          * \return MSG_READY_2.
          */
      //int getMSG_READY_2();

          //! Memberfunktion, welche die Anzahl der mindestens in der DB zu speichernden Werte angibt.
          /*!
	  * \return NORM_DB.
	  */
      int getNORM_DB();


    private:
      string host;	//!< speichert die Hostadresse zwischen.
      string user;	//!< speichert den Benutzernamen zwischen.
      string pw;	//!< speichert das Passwort zwischen.
      string db;	//!< speichert den Namen der Datenbank zwischen.

/*
      int PACKAGE_SIZE_MAX;
      int ACK_SIZE_MAX;
      int DATA_NUM;
      int DATA_NUM_OF_BYTES ;
      
      string EMBPC_IP;
      string MABXII_IP;
      string VSERVER_IP;

      int MABXII_PORT;
      int MABXII_INFO_PORT;
      int EMBPC_PORT;
      int EMBPC_INFO_PORT;
      int VSERVER_PORT;
      int VSERVER_INFO_PORT;
      int MSG_READY_1;
      int MSG_READY_2;
      */
      int NORM_DB;

      string parameter;	//!< Hilfsvariable fuer ganze Zeilen aus der Konfigurationsdatei
      string value;	//!< Hilfsvariable fuer die zugehoerigen Werte aus der Konfigurationsdatei

  };

#endif

