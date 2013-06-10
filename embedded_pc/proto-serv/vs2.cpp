#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
/* uncomment for applications that use vectors */
/*#include <vector>*/

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <string.h>
#include <cstring>

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>





#define EXAMPLE_HOST "192.168.1.3"
#define EXAMPLE_USER "u1"
#define EXAMPLE_PASS "stdvj"
#define EXAMPLE_DB "swp"

using namespace std;

//int main(int argc, const char **argv)
//{
//}

class UseDB{
	
public:
	
 void  mysqlWrite(string text){

  string url = EXAMPLE_HOST; //(argc >= 2 ? argv[1] : EXAMPLE_HOST);
  const string user = EXAMPLE_USER; //(argc >= 3 ? argv[2] : EXAMPLE_USER);
  const string pass = EXAMPLE_PASS; //(argc >= 4 ? argv[3] : EXAMPLE_PASS);
  const string database = EXAMPLE_DB; //(argc >= 5 ? argv[4] : EXAMPLE_DB);

  cout << "Connector/C++ tutorial framework..." << endl;
  cout << endl;

  try {


	sql::Driver* driver = get_driver_instance();
	std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
	con->setSchema(database);
	std::auto_ptr<sql::Statement> stmt(con->createStatement());
		
	// We need not check the return value explicitly. If it indicates
	// // an error, Connector/C++ generates an exception.
	stmt->execute("CALL add_text('" + text + "')");
	//add_text("Hallo hier ist das Programm, gz");
	

    /* INSERT TUTORIAL CODE HERE! */

  } catch (sql::SQLException &e) {
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

    //return EXIT_FAILURE;
  }

  cout << "Done." << endl;
  //return EXIT_SUCCESS;
}

};




int main(int argc, const char **argv)
 {
   
        cout << "Main Called" << endl;
        UseDB db;




  int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  struct sockaddr_in sa;
  char buffer[1024]; // ####
  ssize_t recsize;
  socklen_t fromlen;

  memset(&sa, 0, sizeof sa);
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  sa.sin_port = htons(9999); // ##PORT##
  fromlen = sizeof(sa);

  if (-1 == bind(sock,(struct sockaddr *)&sa, sizeof(sa)))
  {
    perror("Server-Socket konnte nicht an Port gebunden werden");
    close(sock);
    exit(EXIT_FAILURE);
  }

  for (;;)
  {
    //printf ("Empfangstest:....\n");
     recsize = recvfrom(sock, (void *)buffer, sizeof(buffer), 0, (struct sockaddr *)&sa, &fromlen);
     if (recsize < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
     }
 	db.mysqlWrite(buffer);  //     writeDB(buffer);
   }


//	cout << "Main Called" << endl;
//	UseDB db;
//	db.mysqlWrite("asdd");
	return 0;
 }

