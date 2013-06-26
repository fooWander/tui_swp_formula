#ifndef LOGDATA_H
#define LOGDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

	/**	\brief Klasse dient zum Schreiben von Mitteilungen in eine Logdatei.
	*
	*	Diese Klasse bekommt eine Nachricht uebergeben, welche nach erfolgreicher 
	*	Pruefung des mitgelieferten Loglevels mit einem Zeitstempel versehen 
	*	in die Logdatei log.txt geschrieben wird. Wird kein Loglevel mit angegeben,
	*	wird der Loglevel automatisch auf "6" festgelegt.
	*	sie über Memberfunktionen bereit.
	*	\sa Insert
	*
	*/
  class logData
  {
    public:

      void logWrite(string msg);
	  //! Memberfunktion, welche die naechste Memberfunktion aufruft (Ueberladen).
	  /*!
	  *	Kann von ueberall aufgerufen werden wo diese Klasse eingebunden ist.
	  *	Ruft die ueberladene Memberfunktion mit einem festgelegten Loglevel auf.
	  */
      void logWrite(int loglevel, string msg);
          //! Memberfunktion, welche die die Mitteilung in die Logdatei schreibt.
          /*!
          *     Kann von ueberall aufgerufen werden wo diese Klasse eingebunden ist.
          *     Nach Pruefung des Loglevels wird die Datei log.txt aus selbigem
          *     Verzeichnis geoeffnet. Die uebergebene Mitteilung wird mit einem
          *     Zeitstempel versehen in die Logdatei geschrieben und diese anschliessend
          *     geschlossen.
          */
  };

#endif

