#include "Insert.h"

using namespace std;
using namespace sql::mysql;

	Insert::Insert(string ur, string us, string password, string db)
	{
		//Verbindungsdaten festlegen:
		url = ur;
		user = us;
		pass = password;
		database = db;
	}

	int Insert::insertIntoDB(string* anw)
	{
		try{
			/*Verbinden, evtl. umbauen, damit nicht bei jedem Aufruf der Prozedur
			ausgeführt. Bisher gab das dann immer Speicherzugriffsfehler.*/
			sql::Driver* driver = get_driver_instance();
    		std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    		con->setSchema(database);
    		std::auto_ptr<sql::Statement> stmt(con->createStatement());
			stmt->execute(*anw);
		}catch(sql::SQLException &e) {
			/*
			  MySQL Connector/C++ throws three different exceptions:

			  - sql::MethodNotImplementedException (derived from sql::SQLException)
			  - sql::InvalidArgumentException (derived from sql::SQLException)
			  - sql::SQLException (derived from std::runtime_error)
			*/
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			/* what() (derived from std::runtime_error) fetches error message */
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
			return EXIT_FAILURE;
		}

		cout << "MySQL-Anweisung abgelaufen." << endl;
		return EXIT_SUCCESS;
	};

