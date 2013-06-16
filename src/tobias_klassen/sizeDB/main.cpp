#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
using namespace std;
using namespace sql::mysql;


  int main(){
  cout << "Programm zur DB-Bereinigung aufgerufen" << endl;
 

                   try{
                         sql::Driver* driver = get_driver_instance();
                         std::auto_ptr<sql::Connection> con(driver->connect("localhost", "telemetrie", "Ume1Fon3"));
                         con->setSchema( "telemetrie");
                         std::auto_ptr<sql::Statement> stmt(con->createStatement());
                         stmt->execute("delete from test_daniel where (SELECT COUNT(*) FROM (SELECT * FROM test_daniel) AS B) > 10 order by id limit 6;");

                   }catch(sql::SQLException &e) {
                        cout << "# ERR: SQLException in " << __FILE__;
                        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
                        cout << "# ERR: " << e.what();
                        cout << " (MySQL error code: " << e.getErrorCode();
                        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
                        return EXIT_FAILURE;

		   }
  return 0;
}
