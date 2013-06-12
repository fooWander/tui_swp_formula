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
#include <cstring>



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
  //char buffer[255]; // ####

  char * buffer = new char[data.length()];
  strcpy(buffer, data.c_str());

  //strcpy(buffer, data);
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
  bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
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
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Testprogramm zur Verdeutlichung der Programmstruktur." << endl;
<<<<<<< HEAD
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << endl;
	cout << "Definiere Testsignal..." << endl;
	string testString = "Testsignal vom Embedded-PC. ";
=======
	//cout << "Definiere Testsignal" << endl;
	cout << "Bitte geben geben Sie die Daten ein:" << endl;
>>>>>>> origin/webseite_david

	string testString;// = "Testsignal vom Embedded-PC.";
	getline(std::cin, testString); 
	
<<<<<<< HEAD
	cout << "Rufe Funktion recvData auf..." << endl;
=======
	cout << "Rufe Funktion recvData auf.\n\n";
>>>>>>> origin/webseite_david
	recvData(testString);



	return 0;
}


 void recvData(string estr)
{
<<<<<<< HEAD
	cout << "Erhaltene Daten:" << endl << endl;
	cout << "   " + estr << endl << endl;
	
	cout << "Rufe Funktion handleData auf..." << endl;
=======
	cout << "recvData aufgerufen. Erhaltene Daten:\n";
	cout << "   " + estr << endl;
	
	cout << "Rufe Funktion handleData auf.\n\n";
>>>>>>> origin/webseite_david
	handleData(estr);
}

void handleData(string estr)
{
<<<<<<< HEAD
	cout << "Erweiterung des Testsignals..." << endl;
	estr = estr + "Von handleData hinzugefügter String.";

	cout << "Rufe Funktion sendData auf..." << endl << endl;
=======
	cout << "handleData aufgerufen. Bitte erweitern Sie das Testsignal:\n";
	//estr = estr + "Von handleData hinzugefueger String.";
	string erw;
	getline(std::cin, erw);

	estr = estr + erw;

	cout << "Rufe Funktion sendData auf.\n\n";
>>>>>>> origin/webseite_david
	sendData(estr);
}

void sendData(string estr)
{
<<<<<<< HEAD
	cout << "Erhaltene Daten:" << endl;
	cout << endl << "   " + estr << endl;
=======
	cout << "sendData aufgerufen. Daten werden via UDP gesendet.\n";
   	SendC sc;
	sc.sChar(estr);
>>>>>>> origin/webseite_david
}

