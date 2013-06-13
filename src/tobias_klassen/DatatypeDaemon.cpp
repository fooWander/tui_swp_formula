#include "DatatypeDaemon.h"
#include "Data.h"
#include "Decoder.h"

Decoder decode;

DatatypeDaemon::DatatypeDaemon()
{
	dataType = 20;	//Default-Wert für Fehlerausgabe
}

string DatatypeDaemon::parseNextValue()
{
	//Daten umwandeln direkt in Strings:
	string rueckgabe = "";
	Data dat = decode.getNextData();
	int type = dat.getDatatype();
	//Datentyp ist Boolean oder (Unsigned) Integer:
	if(type>=0 && type<=7){
		int temp = (int)dat.getValue();
		rueckgabe = lexical_cast<string>(temp);
	}
	//Datentyp ist float oder double:
	if(type==8 || type==9){
		rueckgabe = lexical_cast<string>(dat.getValue());
	}

	return rueckgabe;
}

int DatatypeDaemon::getTime()
{
	//Zeitstempel von Decoder holen:
	int timestamp = (int)decode.getTimestamp();
	return timestamp;
}
