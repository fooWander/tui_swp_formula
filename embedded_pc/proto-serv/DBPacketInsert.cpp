#include "DBPacketInsert.h"
#include "Insert.h"
#include <boost/lexical_cast.hpp>

using namespace boost;

Insert insertmethoden("localhost", "root", "", "fahrzeugdaten");

DBPacketInsert::DBPacketInsert()
{
	sql_anw = "";
}

void DBPacketInsert::db_insert()
{
	/*sql_anw ist immer gleich aufgebaut:
		"INSERT INTO [tabellenname] ([Auswahl der Spalten]) 
			VALUES ([Werte])"
	*/
	insert_akkudaten();
	cout << "insert_akkudaten glatt abgelaufen." << endl;
	insert_allgemeineFahrzeugdaten();
	cout << "insert_allgemeineFahrzeugdaten glatt abgelaufen." << endl;
	insert_dynamischeDaten();
	cout << "insert_dynamischeDaten glatt abgelaufen." << endl;
	insert_fahrdynamikregelung();
	cout << "insert_fahrdynamikregelung glatt abgelaufen." << endl;
	insert_motorUmrichterdaten();
	cout << "insert_motorUmrichterdaten glatt abgelaufen." << endl;
	cout << "db_insert glatt abgelaufen." << endl;
}

void DBPacketInsert::insert_akkudaten()
{
	sql_anw = "";
	//Start der Anfrage:	
	sql_anw += "INSERT INTO akkudaten (";

	//Auswahl der Spalten:
	//Zelldaten 1-144 einfügen:
	for(int i=1; i<=144; i++)
	{
		sql_anw += "zelldaten";
		if(i<10){
			sql_anw += "00";
		}else{
			sql_anw += "0";
		}
		sql_anw += lexical_cast<string>(i);
		sql_anw += ", ";
	}
	//MaxZellspannung & MinZellspannung einfügen:
	sql_anw += "MaxZellspannung, MinZellspannung, ";
	//Stromladegerät & Balancing einfügen:
	sql_anw += "StromLadegerät, Balancing, ";
	//Zelltemperaturen 1-48 einfügen:
	for(int i=1; i<=48; i++)
	{
		sql_anw += "Zelltemperatur";
		if(i<10){
			sql_anw += "0";
		}
		sql_anw += lexical_cast<string>(i);
		sql_anw += ", ";
	}
	//Zeitpunkt & FehlerFeld einfügen:
	sql_anw += "Zeitpunkt, ";
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	sql_anw += " VALUES (";
	//TODO Hier die Werte einfügen!

	//cout << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
}

void DBPacketInsert::insert_allgemeineFahrzeugdaten()
{
	sql_anw = "";
	//Start der Anfrage:
	sql_anw += "INSERT INTO allgemeine_fahrzeugdaten (";
	
	//Auswahl der Spalten:
	//StatusNotaus einfügen:
	sql_anw += "StatusNotaus, ";
	//Temperatur 1-3 einfügen:
	sql_anw += "Temperatur01, Temperatur02, Temperatur03, ";
	//Geschwindigkeit einfügen:
	sql_anw += "Geschwindigkeit, ";
	//Gaswerte 1&2 einfügen:
	sql_anw += "Gaswert01, Gaswert 02, ";
	//AkkuGesamtspannung einfügen:
	sql_anw += "AkkuGesamtspannung, ";
	//Aktuelle Fahrzeugzeit einfügen:
	sql_anw += "AktuelleFahrzeugzeit, ";
	//Zeitpunkt einfügen:
	sql_anw += "Zeitpunkt, ";
	//Fehlerfeld einfügen:
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	sql_anw += " VALUES (";
	//TODO Hier die Werte einfügen!

	//cout << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
}

void DBPacketInsert::insert_dynamischeDaten()
{
	sql_anw = "";
	//Start der Anfrage:
	sql_anw += "INSERT INTO dynamische_daten (";

	//Auswahl der Spalten:
	//X-, Y- & ZGeschwindigkeiten einfügen:
	sql_anw += "XGeschwindigkeit, YGeschwindigkeit, ZGeschwindigkeit, ";
	//X-, Y- & ZBeschleunigungen einfügen:
	sql_anw += "XBeschleunigung, YBeschleunigung, ZBeschleunigung, ";
	//X-, Y- & ZGierraten einfügen:
	sql_anw += "XGierrate, YGierrate, ZGierrate, ";
	//Drehzahlen der einzelnen Räder einfügen:
	sql_anw += "DrehzahlVRL, DrehzahlVRR, DrehzahlHRL, DrehzahlHRR, ";
	//Wassertemperatur 1&2 einfügen:
	sql_anw += "Wassertemperatur01, Wassertemperatur02, ";
	//Wer das liest ist doof!
	//Bremsdruck, -kraft & -position einfügen:
	sql_anw += "Bremsdruck, Bremskraft, Bremsposition, ";
	//Federweg und Gaspedalstellung einfügen:
	sql_anw += "Federweg, Gaspedalstellung, ";
	//Lenkwinkel einfügen:
	sql_anw += "Lenkwinkel, ";
	//Zeitpunkt einfügen:
	sql_anw += "Zeitpunkt, ";
	//FehlerFeld einfügen:
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	sql_anw += " VALUES (";
	//TODO Hier die Werte einfügen:

	//cout << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
}

void DBPacketInsert::insert_fahrdynamikregelung()
{
	sql_anw = "";
	//Start der Anfrage:
	sql_anw += "INSERT INTO fahrdynamikregelung (";

	//Auswahl der Spalten:
	//Antriebsschlupfregelung einfügen:
	sql_anw += "Antriebsschlupfregelung, ";
	//TorqueVectoring 1-3 einfügen:
	for(int i=1; i<=3; i++)
	{
		sql_anw += "TorqueVectoring0";
		sql_anw += lexical_cast<string>(i);
		sql_anw += ", ";
	}
	//Lenkwinkel einfügen:
	sql_anw += "Lenkwinkel, ";
	//Zeitpunkt einfügen:
	sql_anw += "Zeitpunkt, ";
	//Fehlerfeld einfügen:
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	sql_anw += " VALUES (";
	//TODO Hier die Werte einfügen!

	//cout << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
}

void DBPacketInsert::insert_motorUmrichterdaten()
{
	sql_anw = "";
	//Start der Anfrage:
	sql_anw += "INSERT INTO motor_umrichterdaten (";

	//Auswahl der Spalten:
	//DCStrom & DCSpannung einfügen:
	sql_anw += "DCStrom, DCSpannung, ";
	//Motortemperaturen 1-8 einfügen:
	for(int i=1; i<=8; i++)
	{
		sql_anw += "Motortemperatur0";
		sql_anw += lexical_cast<string>(i);
		sql_anw += ", ";
	}
	//Stromgrenze einfügen:
	sql_anw += "Stromgrenze, ";
	//Maximalleistung einfügen:
	sql_anw += "Maximalleistung, ";
	//Lüfterdrehzahl einfügen:
	sql_anw += "Lüfterdrehzahl, ";
	//Lüfter einfügen:
	sql_anw += "Lüfter, ";
	//Pumpe einfügen:
	sql_anw += "Pumpe, ";
	//Wassertemperatur einfügen:
	sql_anw += "Wassertemperatur, ";
	//Zeitpunkt einfügen:
	sql_anw += "Zeitpunkt, ";
	//FehlerFeld einfügen:
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	sql_anw += " VALUES (";
	//TODO Hier die Werte einfügen!

	cout << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
}
