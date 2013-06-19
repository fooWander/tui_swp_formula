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
	*	der \"Ubertragung entsprechen.
	*	Es werden weiterhin Zusatzinformationen angeboten, die es sowohl erm\"oglichen, die
	*	Paketnummer und damit die Tabelle, in die eingef\"ugt werden soll, zu ermitteln,
	*	als auch den Zeitstempel der Daten einzuf\"ugen.
	*	Diese Klasse dient also als Schnittstelle f\"ur DBPacketInsert zum Decoder.
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
			*	entsprechend dem jetzt erst extrahierten Wert aus Data durchgef\"uhrt, um den Wert
			*	auf seine urspr\"ungliche Gr\"oﬂe zur\"uckzubringen. Dies wird jedoch nur ausgef\"uhrt,
			*	wenn der Wert vor der \"Ubertragung ein Gleitkommawert war.
			*	Abschlieﬂend wird der Wert in einen String umgewandelt, der dann an den Aufrufer 
			*	zur\"uckgegeben wird.
			*/
			string parseNextValue();
			/*! Diese Funktion liefert die Position des jetzigen Datenwerts im \"Ubertragungsvektor
				der MikroAutoBoxII zur\"uck.
			*
			*	Dies ist f\"ur die Bestimmung des \"Ubertragungspakets vom Embedded PC wichtig, da
			*	darauf basierend die richtige Datenbankanfrage in DBPacketInsert aufgebaut wird.
			*
			*	\return Aus Data extrahierter und aufbereiteter Wert im String-Format.
			*/
			int getPosActualPacket();
			/*! Diese Memberfunktion gibt den Zeitstempel des aktuellen Pakets zur\"uck.
			* \return Zeitstempel des Pakets.
			*/
			int getTime();
		private:
			unsigned int dataType;	//!< Datentyp des aktuellen Werts.
			int pos;				//!< Position des Werts im \"Ubertragungsvektor der MikroAutoBoxII.
	};

#endif
