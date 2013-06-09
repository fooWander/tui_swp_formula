//Achtung: Dummy-Objekt, dient nur zur Darstellung des Aufrufes!
#ifndef Insert_H
#define Insert_H
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
/* uncomment for applications that use vectors */
/*#include <vector>*/

#include "mysql_connection.h"
//#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
using namespace std;
using namespace sql::mysql;

class Insert
{

public:
	Insert(string ur, string us, string password, string db);

	int insertIntoDB(string* anw);

private:
	string url;
	string user;
	string pass;
	string database;
};

#endif
