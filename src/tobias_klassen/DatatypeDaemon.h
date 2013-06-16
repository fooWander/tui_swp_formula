#ifndef DatatypeDaemon_H
#define DatatypeDaemon_H

#include <math.h>
#include <string>
#include <boost/lexical_cast.hpp>
#include "Data.h"
#include "Decoder.h"
using namespace std;
using namespace boost;

	/*! \brief Klasse zum Aufbereiten der Daten.
	*
	*	In dieser Klasse werden Die Daten nicht nur in das richtige Format umgewandelt,
	*	sondern auch durch eine Zehnerpotenz geteilt, sodass sie wieder ihrem Wert vor
	*	der Übertragung entsprechen.
	*	Es werden weiterhin Zusatzinformationen angeboten, die es sowohl ermöglichen, die
	*	Paketnummer und damit die Tabelle, in die eingefügt werden soll, zu ermitteln,
	*	als auch den Zeitstempel der Daten einzufügen.
	*	Diese Klasse dient also als Schnittstelle für DBPacketInsert zum Decoder.
	*	
	*	\sa Data
	*/
	class DatatypeDaemon{
		public:
			/*! Konstruktor der Klasse.
			*
			*/
			DatatypeDaemon();
			/*! Diese Funktion wird von DBPacketInsert aufgerufen.
			*
			*	Sie holt sich ein Data Objekt vom Decoder und extrahiert daraus
			*	die Nutzdaten und die Position dieser Daten im Paket. 
			*	Die Position wird dabei in einer Membervariablen zwischengespeichert.
			*	Nachdem der Datentyp bestimmt wurde, wird eine Divison durch eine Zehnerpotenz
			*	entsprechend dem jetzt erst extrahierten Wert aus Data durchgeführt, um den Wert
			*	auf seine ursprüngliche Größe zurückzubringen. Dies wird jedoch nur ausgeführt,
			*	wenn der Wert vor der Übertragung ein Gleitkommawert war.
			*	Abschließend wird der Wert in einen String umgewandelt, der dann an den Aufrufer 
			*	zurückgegeben wird.
			*/
			string parseNextValue();
			/*! Diese Funktion liefert die Position des jetzigen Datenwerts im Übertragungsvektor
				der MikroAutoBoxII zurück.
			*
			*	Dies ist für die Bestimmung des Übertragungspakets vom Embedded PC wichtig, da
			*	darauf basierend die richtige Datenbankanfrage in DBPacketInsert aufgebaut wird.
			*
			*	\return Aus Data extrahierter und aufbereiteter Wert im String-Format.
			*/
			int getPosActualPacket();
			/*! Diese Memberfunktion gibt den Zeitstempel des aktuellen Pakets zurück.
			* \return Zeitstempel des Pakets.
			*/
			int getTime();
		private:
			unsigned int dataType;	//!< Datentyp des aktuellen Werts.
			int pos;				//!< Position des Werts im Übertragungsvektor der MikroAutoBoxII.
	};

#endif
