#include "DatatypeDaemon.h"
#include "Data.h"
#include "Decoder.h"

Decoder decode;

DatatypeDaemon::DatatypeDaemon()
{
	dataType = 20;	//Default-Wert f\"ur Fehlerausgabe
}

string DatatypeDaemon::parseNextValue()
{
	//Daten umwandeln direkt in Strings:
	string rueckgabe = "";
	Data dat = decode.getNextData();
	int type = dat.getDatatype();
	pos = dat.getPosition();
	//Datentyp ist Boolean oder (Unsigned) Integer:
	if(type>=0 && type<=7){
		int temp = dat.getValue();
		if(temp > 32767){
			temp = 32767 - temp;
		}
		rueckgabe = lexical_cast<string>(temp);
	}
	//Datentyp ist float oder double:
	if(type==8 || type==9){
	    double temp = (double)dat.getValue();
	    int temp2 = dat.getDecPointValue();
		if(temp > 32767){
			temp = 32767 - temp;
		}
	    temp = temp/pow(10.0, temp2);
		rueckgabe = lexical_cast<string>(temp);
	}

	return rueckgabe;
}

int DatatypeDaemon::getPosActualPacket()
{
    //Position weiterreichen:
    return pos;
}

int DatatypeDaemon::getTime()
{
	//Zeitstempel von Decoder holen:
	int timestamp = (int)decode.getTimestamp();
	return timestamp;
}
