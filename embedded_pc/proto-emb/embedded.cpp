#include <iostream>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>




using namespace std;

void recvData(string estr);
void handleData(string estr);
void sendData(string estr);

class SendC{

 public:
 
 void sChar(string data)//char data[255])
 {

  //Initialisierung der Variablen
  int sock;
  struct sockaddr_in sa;
  int bytes_sent;
  char buffer[255]; // ####
  
  strcpy(buffer, data);
  //Erzeugen eines UDP-Sockets
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (-1 == sock) /* Beenden falls Socket nicht erzeugt/initialisiert werden konnte */
  {
    printf("Socket konnte nicht geoeffnet werden!");
    exit(EXIT_FAILURE);
  }
  memset(&sa, 0, sizeof sa);
  //ipv4 Adresse
  sa.sin_family = AF_INET;
  //ip_v4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value
  sa.sin_addr.s_addr = inet_addr("192.168.1.3");
  //festgelegter Port
  sa.sin_port = htons(9999); // ##PORT##
  //sendto(int Socket, char Daten, int Dateilaenge, Flags, ZeilAddresse, int ZielStructurLaenge)
  bytes_sent = sendto(sock, data, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  if (bytes_sent < 0)
  {
    printf("Packet konnte nicht gesendet werden: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  close(sock); /* Socket schlieÃn */
  
 }



  private:	

};


int main()
{
	cout << "Testprogramm zur Verdeutlichung der Programmstruktur." << endl;
	cout << " Definiere Testsignal" << endl;
	string testString = "Testsignal vom Embedded-PC.";

	
	cout << " Rufe Funktion recvData auf.\n";
	recvData(testString);



	return 0;
}


 void recvData(string estr)
{
	cout << "  recvData aufgerufen. Erhaltene Daten:\n";
	cout << "   " + estr << endl;
	
	cout << " Rufe Funktion handleData auf.\n";
	handleData(estr);
}

void handleData(string estr)
{
	cout << "  handleData aufgerufen. Erweiterung des Testsignals.\n";
	estr = estr + " Von handleData hinzugefügter String.";

	cout << " Rufe Funktion sendData auf.\n";
	sendData(estr);
}

void sendData(string estr)
{
	cout << "  sendData aufgerufen. Erhaltene Daten:\n";
	cout << "   " + estr << endl;
        string a;
	//std::string::c_str() a;
	cin >> a;

	//char a[255] = a.c_str();
	//cin >> a;
   	SendC sc;
	sc.sChar(a);
}

