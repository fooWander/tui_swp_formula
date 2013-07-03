#include "DBPacketInsert.h"
#include "Insert.h"
#include <boost/lexical_cast.hpp>

using namespace boost;

DBPacketInsert::DBPacketInsert()
{
	//myDec = dec;
	sql_anw = "";
}

void DBPacketInsert::db_insert()
{
    int nowPos;
	/*Sämtliche Daten auslesen, da in der Datenbank teilweise
	/ der gleiche Wert mehrmals in verschiedene Tabellen
	/ eingetragen wird!*/

	//Fehlervariable initialisieren
	bool error = false;
		
	//Zeitstempel holen:
	time = slave.getTime();
	//Erstes Element eines neuen Pakets holen:
	wertStuecke[0] = slave.parseNextValue();
	//Position im Übertragungsvektor bestimmen:
	nowPos = slave.getPosActualPacket();
	//durch Position bestimmen, welches Paket jetzt kommt,
	//dementsprechend die Insert-Routine aufrufen:
	switch(nowPos){
	case allgemeineFahrzeugdaten: 
	    //Über Anzahl aller Werte dieses Pakets:
	    for(int i=1; i<(akkudaten - allgemeineFahrzeugdaten); i++){
	        //Werte einlesen
	        wertStuecke[i] = slave.parseNextValue();
	    }
	    //Insert-Routine aufrufen
	    error = insert_allgemeineFahrzeugdaten();
	    //switch-Anweisung verlassen
	    break;
	case akkudaten:
	    for(int i=1; i<(dynamischeDaten - akkudaten); i++){
	        wertStuecke[i] = slave.parseNextValue();
	    }
	    error = insert_akkudaten();
	    break;
	case dynamischeDaten:
	    for(int i=1; i<(fahrdynamikregelung - dynamischeDaten); i++){
	        wertStuecke[i] = slave.parseNextValue();
	    }
	    error = insert_dynamischeDaten();
	    break;
	case fahrdynamikregelung:
	    for(int i=1; i<(motorUmrichterdaten - fahrdynamikregelung); i++){
	        wertStuecke[i] = slave.parseNextValue();
	    }
	    error = insert_fahrdynamikregelung();
	    break;
	case motorUmrichterdaten:
	    for(int i=1; i<(ende - motorUmrichterdaten); i++){
	        wertStuecke[i] = slave.parseNextValue();
	    }
	    error = insert_motorUmrichterdaten();
	    break;
	}
	
	//Daten in DB schreiben lassen:
	//(falls keine Fehler aufgetreten sind)
	if (!error){
	  insertMethodes.insertIntoDB(&sql_anw);
	  cout << "db_insert abgelaufen." << endl;
	}
	else{
	  //Fehlerausgabe als Log-Eintrag
	  logData lg;
          lg.logWrite(3, sql_anw);
	}

}



bool DBPacketInsert::insert_allgemeineFahrzeugdaten()
{
    /*sql_anw ist immer gleich aufgebaut:
		"INSERT INTO [tabellenname] ([Auswahl der Spalten]) 
			VALUES ([Werte])"
	*/
	bool error = false;
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
		//Fehlerueberpruefung
		if ((wertStuecke[i] < 0) || (wertStuecke[i] > 1)){
		  error = true;
		}
	}
	sql_anw += ", ";
	//Temperaturen 1-3 einfügen:
	for(int i=10; i<13; i++){
		sql_anw += wertStuecke[i] + ", ";
                //Fehlerueberpruefung
		if ((wertStuecke[i] < -999.9) || (wertStuecke[i] > 999.9)){
                  error = true;
                }
	}
	//Geschwindigkeit einfügen:
	sql_anw += wertStuecke[13] + ", ";
		//Fehlerueberpruefung
                if ((wertStuecke[13] < -200.0) || (wertStuecke[13] > 200.0)){
                  error = true;
                }
	//Gaswerte 1&2 einfügen:
	sql_anw += wertStuecke[14] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[14] < -100.0) || (wertStuecke[14] > 100.0)){
                  error = true;
                }
	sql_anw += wertStuecke[15] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[15] < -100.0) || (wertStuecke[15] > 100.0)){
                  error = true;
                }
	//AkkuGesamtspannung einfügen:
	sql_anw += wertStuecke[16] + ", ";
                //Fehlerueberpruefung
		if ((wertStuecke[16] < 0.0) || (wertStuecke[16] > 1000.0)){
                  error = true;
                }
	//Aktuelle Fahrzeugzeit einfügen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "10, ";
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	sql_anw += "'NARF')";
	
	//cout << "SQL-Anweisung: " << sql_anw << endl;

	//Fehlerausgabe in Logdatei:
	if (error){
	  logData lg;
	  lg.logWrite(4, "Werte der allgemeinen Fahrzeugdaten liegen ausserhalb des gueltigen Bereichs, Packet wird nicht in die DB geschieben.");
	}
	return error;
}


bool DBPacketInsert::insert_akkudaten()
{
	//Errorvariable
	bool error = false;
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
	for(int i=0; i<144; i++){
		sql_anw += wertStuecke[i] + ", ";
		//Fehlerueberpruefung
                if ((wertStuecke[i] < 0.0) || (wertStuecke[i] > 5.0)){
                  error = true;
                }
	}
	//MaxZellspannung & MinZellspannung einfügen:
	sql_anw += wertStuecke[192] + ", ";
		//Fehlerueberpruefung
		 if ((wertStuecke[192] < 0.0) || (wertStuecke[192] > 5.0)){
                  error = true;
                }	
	sql_anw += wertStuecke[193] + ", ";
                //Fehlerueberpruefung
                 if ((wertStuecke[193] < 0.0) || (wertStuecke[193] > 5.0)){
                  error = true;
                }
	//Gesamtspannung einfügen:
	sql_anw += wertStuecke[194] + ", ";
                //Fehlerueberpruefung
                 if ((wertStuecke[194] < 0.0) || (wertStuecke[194] > 1000.0)){
                  error = true;
                }
	//Stromladegerät und SpannungLadegerät einfügen:
	sql_anw += wertStuecke[195] + ", ";
                //Fehlerueberpruefung
                 if ((wertStuecke[195] < -100.0) || (wertStuecke[195] > 100.0)){
                  error = true;
                }
	sql_anw += wertStuecke[196] + ", ";
                //Fehlerueberpruefung
                 if ((wertStuecke[196] < -1000.0) || (wertStuecke[196] > 1000.0)){
                  error = true;
                }
	//Balancing einfügen:
	for(int i=197; i<269; i++){
		sql_anw += wertStuecke[i];
                //Fehlerueberpruefung
                 if ((wertStuecke[i] < 0.0) || (wertStuecke[i] > 1.0)){
                  error = true;
                }
	}
	//Balancing2 einfügen:
	sql_anw += ", ";
	for(int i=269; i<341; i++){
		sql_anw += wertStuecke[i];
                //Fehlerueberpruefung
                 if ((wertStuecke[i] < 0.0) || (wertStuecke[i] > 1.0)){
                  error = true;
                }
	}
	sql_anw += ", ";
	//Temperaturen einfügen:
	for(int i=144; i<192; i++){
		sql_anw += wertStuecke[i] + ", ";
                //Fehlerueberpruefung
                 if ((wertStuecke[i] < -100.0) || (wertStuecke[i] > 200.0)){
                  error = true;
                }
	}
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "'NARF')";

	//cout << "SQL-Anweisung: " << sql_anw << endl;
	cout << "insert_akkudaten abgelaufen." << endl;
        
	//Fehlerausgabe in Logdatei:
	if (error){
          logData lg;
          lg.logWrite(4, "Werte der Akkudaten liegen ausserhalb des gueltigen Bereichs, Packet wird nicht in die DB geschieben.");
        }
	return error;
}

bool DBPacketInsert::insert_dynamischeDaten()
{
	//Errorvariable
	bool error = false;
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
	sql_anw += "Lenkwinkel2, ";
	//Zeitpunkt einfügen:
	sql_anw += "Zeitpunkt, ";
	//FehlerFeld einfügen:
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	sql_anw += " VALUES (";
	//Geschwindigkeiten einfügen:
	for(int i=0; i<3; i++){
		sql_anw += wertStuecke[i] + ", ";
		//Fehlerueberpruefung
		if ((wertStuecke[i] < -200.0) || (wertStuecke[i] > 200.0)){
                  error = true;
                }
	}
	//Beschleunigungen einfügen:
	for(int i=3; i<6; i++){
		sql_anw += wertStuecke[i] + ", ";
		//Fehlerueberpruefung
                if ((wertStuecke[i] < -200.0) || (wertStuecke[i] > 200.0)){
                  error = true;
                }
	}
	//Gierraten einfügen:
	for(int i=6; i<9; i++){
		sql_anw += wertStuecke[i] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[i] < -760.0) || (wertStuecke[i] > 760.0)){
                  error = true;
                }
	}
	//Drehzahlen einfügen:
	for(int i=9; i<13; i++){
		sql_anw += wertStuecke[i] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[i] < -2000.0) || (wertStuecke[i] > 2000.0)){
                  error = true;
                }
	}
	//Wassertemperaturen 1&2 einfügen:
	sql_anw += wertStuecke[13] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[13] < -999.9) || (wertStuecke[13] > 999.9)){
                  error = true;
                }
	sql_anw += wertStuecke[14] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[14] < -999.9) || (wertStuecke[14] > 999.9)){
                  error = true;
                }
	//Bremsdruck einfügen:
	sql_anw += wertStuecke[15] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[15] < -200.0) || (wertStuecke[15] > 200.0)){
                  error = true;
                }
	//Bremskraft einfügen:
	sql_anw += wertStuecke[16] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[16] < -100.0) || (wertStuecke[16] > 100.0)){
                  error = true;
                }
	//Bremsposition einfügen:
	sql_anw += wertStuecke[17] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[17] < -100.0) || (wertStuecke[17] > 100.0)){
                  error = true;
                }
	//Federwege 1-4 einfügen:
	for(int i=18; i<22; i++){
		sql_anw += wertStuecke[i] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[i] < 0.0) || (wertStuecke[i] > 100.0)){
                  error = true;
                }
	}
	//Gaspedalstellung 1&2 einfügen:
	sql_anw += wertStuecke[22] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[22] < -100.0) || (wertStuecke[22] > 100.0)){
                  error = true;
                }
	sql_anw += wertStuecke[23] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[23] < -100.0) || (wertStuecke[23] > 100.0)){
                  error = true;
                }
	//Lenkwinkel einfügen:
	sql_anw += wertStuecke[24] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[24] < -180.0) || (wertStuecke[24] > 180.0)){
                  error = true;
                }
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "'NARF')";

	//cout << "SQL-Anweisung: " << sql_anw << endl;
	cout << "insert_dynamischeDaten abgelaufen." << endl;
	//Fehlerausgabe in Logdatei:
	if (error){
          logData lg;
          lg.logWrite(4, "Werte der dynamischen Daten liegen ausserhalb des gueltigen Bereichs, Packet wird nicht in die DB geschieben.");
        }
	return error;
}

bool DBPacketInsert::insert_fahrdynamikregelung()
{
	//Errorvariable
	bool error = false;
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
	//Zeitpunkt einfügen:
	sql_anw += "Zeitpunkt, ";
	//Fehlerfeld einfügen:
	sql_anw += "Fehlerfeld)";

	//Daten einfügen:
	sql_anw += " VALUES (";
	//Antriebschlupfregelung einfügen:
	sql_anw += wertStuecke[0] + ", ";
		//Fehlerueberpruefung
		if ((wertStuecke[0] < 0.0) || (wertStuecke[0] > 1.0)){
                  error = true;
                }
	//TorqueVectoring einfügen:
	sql_anw += wertStuecke[1] + ", ";
		//Fehlerueberpruefung
		if ((wertStuecke[1] < 0.0) || (wertStuecke[1] > 1.0)){
                  error = true;
                }
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "'NARF')";

	//cout << "SQL-Anweisung: " << sql_anw << endl;
	cout << "insert_fahrdynamikregelung abgelaufen." << endl;
	
	//Fehlerausgabe in Logdatei:
	if (error){
          logData lg;
          lg.logWrite(4, "Werte der Fahrdynamikregelung liegen ausserhalb des gueltigen Bereichs, Packet wird nicht in die DB geschieben.");
        }
	return error;
}

bool DBPacketInsert::insert_motorUmrichterdaten()
{
	//Errorvariable
	bool error = false;
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
	sql_anw += wertStuecke[0] + ", ";
		//Fehlerueberpruefung
		if ((wertStuecke[0] < -200.0) || (wertStuecke[0] > 200.0)){
                  error = true;
                }
	//DCSpannung einfügen:
	sql_anw += wertStuecke[1] + ", ";
                //Fehlerueberpruefung
		if ((wertStuecke[1] < 0.0) || (wertStuecke[1] > 1000.0)){
                  error = true;
                }               
	//Motortemperaturen 1-8 einfügen:
	for(int i=2; i<10; i++){
		sql_anw += wertStuecke[i] + ", ";
                //Fehlerueberpruefung
       		if ((wertStuecke[i] < -999.9) || (wertStuecke[i] > 999.9)){
                  error = true;
                }         
	}
	//Stromgrenze einfügen:
	sql_anw += wertStuecke[10] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[10] < 0.0) || (wertStuecke[10] > 1.0)){
                  error = true;
                }
	//Maximalleistung einfügen:
	sql_anw += wertStuecke[11] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[11] < 0.0) || (wertStuecke[11] > 1.0)){
                  error = true;
                }
	//Lüfterdrehzahl einfügen:
	sql_anw += wertStuecke[12] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[12] < -999.9) || (wertStuecke[12] > 999.9)){
                  error = true;
                }
	//Lüfter einfügen:
	sql_anw += wertStuecke[13] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[13] < 0.0) || (wertStuecke[13] > 1.0)){
                  error = true;
                }
	//Pumpe einfügen:
	sql_anw += wertStuecke[14] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[14] < 0.0) || (wertStuecke[14] > 1.0)){
                  error = true;
                }
	//Wassertemperatur einfügen:
	sql_anw += wertStuecke[15] + ", ";
                //Fehlerueberpruefung
                if ((wertStuecke[15] < -999.9) || (wertStuecke[15] > 999.9)){
                  error = true;
                }
	//Zeitpunkt einfügen:
	sql_anw += lexical_cast<string>(time) + ", ";
	//Fehlerfeld füllen:
	//ACHTUNG: DUMMY!!!
	sql_anw += "'NARF')";

	//cout << "SQL-Anweisung: " << sql_anw << endl;
	cout << "insert_motorUmrichterdaten abgelaufen." << endl;
	//Fehlerausgabe in Logdatei:
	 if (error){
          logData lg;
          lg.logWrite(4, "Werte der Motorumrichterdaten liegen ausserhalb des gueltigen Bereichs, Packet wird nicht in die DB geschieben.");
        }
	return error;
}
