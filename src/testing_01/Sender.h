#include <iostream>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
//#include <string>
#include <sstream>
#include <sys/types.h>
#include <arpa/inet.h> //fuer inet_addr
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h> //fuer  gettimeofday
using namespace std;

class Sender
{
public:
	Sender(arguments);
	~Sender();

	void addHeader(Header);
	void addData(Data);
	void setDestination(Destination);

private:
	Data myData;
	Destination myDestination;
	Header myHeader;
};