#include "DBPacketInsert.h"
#include "Insert.h"
#include "DatatypeDaemon.h"
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

	/*Sämtliche Daten auslesen, da in der Datenbank teilweise
	/ der gleiche Wert mehrmals in verschiedene Tabellen
	/ eingetragen wird!*/
	DatatypeDaemon slave;
	for(int i=0; i<401; i++){
		wertStuecke[i] = slave.parseNextValue();
	}
	//Zeitstempel holen:
	time = slave.getTime();
	
	//SQL-Anweisungen für die einzelnen Tabellen erstellen:
	insert_allgemeineFahrzeugdaten();

	insert_akkudaten();
	
	insert_dynamischeDaten();
	
	insert_fahrdynamikregelung();
	
	insert_motorUmrichterdaten();
	
	cout << "db_insert abgelaufen." << endl;
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
	sql_anw += "Gaswert01, Gaswert02, ";
	//AkkuGesamtspannung einfügen:
	sql_anw += "AkkuGesamtspannung, ";
	//Aktuelle Fahrzeugzeit einfügen:
	sql_anw += "AktuelleFahrzeugzeit, ";
	//Zeitpunkt einfügen:
	sql_anw += "Zeitpunkt, ";
	//Fehlerfeld einfügen:
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	//Notausfunktionen einfügen:
	sql_anw += " VALUES (";
	for(int i=0; i<10; i++){
		sql_anw += wertStuecke[i];
	}
	sql_anw += ", ";
	//Temperaturen 1-3 einfügen:
	for(int i=10; i<13; i++){
		sql_anw += wertStuecke[i] + ", ";
	}
	//Geschwindigkeit einfügen:
	sql_anw += wertStuecke[13] + ", ";
	//Gaswerte 1&2 einfügen:
	sql_anw += wertStuecke[14] + ", ";
	sql_anw += wertStuecke[15] + ", ";
	//AkkuGesamtspannung einfügen:
	sql_anw += wertStuecke[16] + ", ";
	//Aktuelle Fahrzeugzeit einfügen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "10, ";
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	sql_anw += "'NARF')";
	

	//cout << "SQL-Anweisung: " << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
	cout << "insert_allgemeineFahrzeugdaten abgelaufen." << endl;
}

void DBPacketInsert::insert_akkudaten()
{
	//Sollte im Vector sich vor diesen Daten etwas
	//ändern, dann den offset aktualisieren!
	int offset = 17;

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
			if(i<100){
				sql_anw += "0";
			}
		}
		sql_anw += lexical_cast<string>(i);
		sql_anw += ", ";
	}
	//MaxZellspannung & MinZellspannung einfügen:
	sql_anw += "MaxZellspannung, MinZellspannung, ";
	//GesamtspannungAkku hinzufügen:
	sql_anw += "GesamtspannungAkku, ";
	//Stromladegerät, Spannungladegerät & Balancing einfügen:
	sql_anw += "StromLadegerät, SpannungLadegerät, Balancing, Balancing2, ";
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
	//Zelldaten 1-144 einfügen;
	for(int i=0+offset; i<144+offset; i++){
		sql_anw += wertStuecke[i+offset] + ", ";
	}
	//MaxZellspannung & MinZellspannung einfügen:
	sql_anw += wertStuecke[192+offset] + ", ";
	sql_anw += wertStuecke[193+offset] + ", ";
	//Gesamtspannung einfügen:
	sql_anw += wertStuecke[194+offset] + ", ";
	//Stromladegerät und SpannungLadegerät einfügen:
	sql_anw += wertStuecke[195+offset] + ", ";
	sql_anw += wertStuecke[196+offset] + ", ";
	//Balancing einfügen:
	for(int i=197+offset; i<269+offset; i++){
		sql_anw += wertStuecke[i];
	}
	//Balancing2 einfügen:
	sql_anw += ", ";
	for(int i=269+offset; i<341+offset; i++){
		sql_anw += wertStuecke[i];
	}
	sql_anw += ", ";
	//Temperaturen einfügen:
	for(int i=144+offset; i<192+offset; i++){
		sql_anw += wertStuecke[i] + ", ";
	}
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "'NARF')";

	//cout << "SQL-Anweisung: " << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
	cout << "insert_akkudaten abgelaufen." << endl;
}

void DBPacketInsert::insert_dynamischeDaten()
{
	//Sollte im Vector sich vor diesen Daten etwas
	//ändern, dann den offset aktualisieren!
	int offset = 358;

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
	//Federweg einfügen:
	sql_anw += "Federweg01, Federweg02, Federweg03, Federweg04, "; 
	//Gaspedalstellungen einfügen:
	sql_anw += "Gaspedalstellung01, Gaspedalstellung02, ";
	//Lenkwinkel einfügen:
	sql_anw += "Lenkwinkel, ";
	//Zeitpunkt einfügen:
	sql_anw += "Zeitpunkt, ";
	//FehlerFeld einfügen:
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	sql_anw += " VALUES (";
	//Geschwindigkeiten einfügen:
	for(int i=0+offset; i<3+offset; i++){
		sql_anw += wertStuecke[i] + ", ";
	}
	//Beschleunigungen einfügen:
	for(int i=3+offset; i<6+offset; i++){
		sql_anw += wertStuecke[i] + ", ";
	}
	//Gierraten einfügen:
	for(int i=6+offset; i<9+offset; i++){
		sql_anw += wertStuecke[i] + ", ";
	}
	//Drehzahlen einfügen:
	for(int i=9+offset; i<13+offset; i++){
		sql_anw += wertStuecke[i] + ", ";
	}
	//Wassertemperaturen 1&2 einfügen:
	sql_anw += wertStuecke[13+offset] + ", ";
	sql_anw += wertStuecke[14+offset] + ", ";
	//Bremsdruck einfügen:
	sql_anw += wertStuecke[15+offset] + ", ";
	//Bremskraft einfügen:
	sql_anw += wertStuecke[16+offset] + ", ";
	//Bremsposition einfügen:
	sql_anw += wertStuecke[17+offset] + ", ";
	//Federwege 1-4 einfügen:
	for(int i=18+offset; i<22+offset; i++){
		sql_anw += wertStuecke[i] + ", ";
	}
	//Gaspedalstellung 1&2 einfügen:
	sql_anw += wertStuecke[22+offset] + ", ";
	sql_anw += wertStuecke[23+offset] + ", ";
	//Lenkwinkel einfügen:
	sql_anw += wertStuecke[24+offset] + ", ";
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "'NARF')";

	//cout << "SQL-Anweisung: " << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
	cout << "insert_dynamischeDaten abgelaufen." << endl;
}

void DBPacketInsert::insert_fahrdynamikregelung()
{
	//Sollte im Vector sich vor diesen Daten etwas
	//ändern, dann den offset aktualisieren!
	int offset = 383;

	sql_anw = "";
	//Start der Anfrage:
	sql_anw += "INSERT INTO fahrdynamikregelung (";

	//Auswahl der Spalten:
	//Antriebsschlupfregelung einfügen:
	sql_anw += "Antriebschlupfregelung, ";
	/*
	//TorqueVectoring 1-3 einfügen:
	for(int i=1; i<=3; i++)
	{
		sql_anw += "TorqueVectoring0";
		sql_anw += lexical_cast<string>(i);
		sql_anw += ", ";
	}
	*/
	//TorqeVectoring einfügen:
	sql_anw += "TorqueVectoring, ";
	//Lenkwinkel einfügen:
	sql_anw += "Lenkwinkel, ";
	//Zeitpunkt einfügen:
	sql_anw += "Zeitpunkt, ";
	//Fehlerfeld einfügen:
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	sql_anw += " VALUES (";
	//Antriebschlupfregelung einfügen:
	sql_anw += wertStuecke[0+offset] + ", ";
	//TorqueVectoring einfügen:
	sql_anw += wertStuecke[1+offset] + ", ";
	//Lenkwinkel einfügen:
	//ACHTUNG: Wert aus einem anderen Teil des Vektors!
	//OFFSET beachten!
	sql_anw += wertStuecke[offset-1] + ", ";
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "'NARF')";

	//cout << "SQL-Anweisung: " << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
	cout << "insert_fahrdynamikregelung abgelaufen." << endl;
}

void DBPacketInsert::insert_motorUmrichterdaten()
{
	//Sollte im Vector sich vor diesen Daten etwas
	//ändern, dann den offset aktualisieren!
	int offset = 385;

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
	//DCStrom einfügen:
	sql_anw += wertStuecke[0+offset] + ", ";
	//DCSpannung einfügen:
	sql_anw += wertStuecke[1+offset] + ", ";
	//Motortemperaturen 1-8 einfügen:
	for(int i=2+offset; i<10+offset; i++){
		sql_anw += wertStuecke[i] + ", ";
	}
	//Stromgrenze einfügen:
	sql_anw += wertStuecke[10+offset] + ", ";
	//Maximalleistung einfügen:
	sql_anw += wertStuecke[11+offset] + ", ";
	//Lüfterdrehzahl einfügen:
	sql_anw += wertStuecke[12+offset] + ", ";
	//Lüfter einfügen:
	sql_anw += wertStuecke[13+offset] + ", ";
	//Pumpe einfügen:
	sql_anw += wertStuecke[14+offset] + ", ";
	//Wassertemperatur einfügen:
	sql_anw += wertStuecke[15+offset] + ", ";
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "'NARF')";

	//cout << "SQL-Anweisung: " << sql_anw << endl;
	//Daten in DB schreiben lassen:
	insertmethoden.insertIntoDB(&sql_anw);
	cout << "insert_motorUmrichterdaten abgelaufen." << endl;
}
