#ifndef PacketInsert_H
#define PacketInsert_H

#include <iostream>
#include <string>
#include "DBPacketInsert.h"

using namespace std;

class DBPacketInsert{
	public:
		DBPacketInsert();
		void db_insert();
	private:
		string sql_anw;
		string wertStuecke[401];
		int time;
		void insert_akkudaten();
		void insert_allgemeineFahrzeugdaten();
		void insert_dynamischeDaten();
		void insert_fahrdynamikregelung();
		void insert_motorUmrichterdaten();
};

#endif
