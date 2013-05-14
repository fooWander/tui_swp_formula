#include <iostream>

using namespace std;

void recvData(string estr);
void handleData(string estr);
void sendData(string estr);


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
}

