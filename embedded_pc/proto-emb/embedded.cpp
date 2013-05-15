#include <iostream>

using namespace std;

void recvData(string estr);
void handleData(string estr);
void sendData(string estr);


int main()
{
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Testprogramm zur Verdeutlichung der Programmstruktur." << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << endl;
	cout << "Definiere Testsignal..." << endl;
	string testString = "Testsignal vom Embedded-PC. ";

	
	cout << "Rufe Funktion recvData auf..." << endl;
	recvData(testString);



	return 0;
}


 void recvData(string estr)
{
	cout << "Erhaltene Daten:" << endl << endl;
	cout << "   " + estr << endl << endl;
	
	cout << "Rufe Funktion handleData auf..." << endl;
	handleData(estr);
}

void handleData(string estr)
{
	cout << "Erweiterung des Testsignals..." << endl;
	estr = estr + "Von handleData hinzugefügter String.";

	cout << "Rufe Funktion sendData auf..." << endl << endl;
	sendData(estr);
}

void sendData(string estr)
{
	cout << "Erhaltene Daten:" << endl;
	cout << endl << "   " + estr << endl;
}

