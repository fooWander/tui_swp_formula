#ifndef PacketInsert_H
#define PacketInsert_H

#include <iostream>
#include <string>
#include "DBPacketInsert.h"
#include "DatatypeDaemon.h"

using namespace std;

class DBPacketInsert{
	public:
		DBPacketInsert();
		void db_insert();
	private:
	    //Sollte im Vector sich vor diesen Daten etwas
	    //ändern, dann den offset aktualisieren!
	    enum VektorTeile {allgemeineFahrzeugdaten = 0, akkudaten = 17, dynamischeDaten = 358, fahrdynamikregelung = 383, motorUmrichterdaten = 385, ende = 400};
		string sql_anw;
		string wertStuecke[341];
		int time;
		DatatypeDaemon slave;
		void insert_akkudaten();
		void insert_allgemeineFahrzeugdaten();
		void insert_dynamischeDaten();
		void insert_fahrdynamikregelung();
		void insert_motorUmrichterdaten();
};

#endif
