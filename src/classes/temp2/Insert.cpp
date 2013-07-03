#include "Insert.h"

using namespace std;
using namespace sql::mysql;

	Insert::Insert()
	{
		//Verbindungsdaten festlegen:
		dbData getDBDataDaemon;
		url = getDBDataDaemon.getHost();
		user = getDBDataDaemon.getUser();
		pass = getDBDataDaemon.getPW();
		database = getDBDataDaemon.getDB();
	}

	int Insert::insertIntoDB(string* anw)
	{
		try{
			sql::Driver* driver = get_driver_instance();
    		std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    		con->setSchema(database);
    		std::auto_ptr<sql::Statement> stmt(con->createStatement());
			stmt->execute(*anw); // An dieser Stelle wird der String an die Datenbank übergeben.
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

