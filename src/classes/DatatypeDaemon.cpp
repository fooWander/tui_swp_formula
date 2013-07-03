#include "DatatypeDaemon.h"
#include "Data.h"
//#include "Encoding.h"

DatatypeDaemon::DatatypeDaemon()
{
	dataType = 20;	//Default-Wert f\"ur Fehlerausgabe
}

string DatatypeDaemon::parseNextValue()
{
	//Daten umwandeln direkt in Strings:
	string rueckgabe = "";
	Data dat = DECODER.getNextData();
	int type = dat.getDatatype();
	std::cout << "TYP: " << type << std::endl;
	pos = dat.getPosition();
	std::cout << "POS: " << pos << std::endl;
	//Datentyp ist Boolean oder (Unsigned) Integer:
	if(type>=0 && type<=7){
		int temp = dat.getValue();
		rueckgabe = lexical_cast<string>(temp);
	}
	//Datentyp ist float oder double:
	if(type==8 || type==9){
	    double temp = (double)dat.getValue();
	    int temp2 = dat.getDecPointValue();
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
	int timestamp = (int)DECODER.getDataTimestamp();
	return timestamp;
}
