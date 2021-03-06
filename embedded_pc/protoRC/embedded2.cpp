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

class SendC
{

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
        // Beenden falls Socket nicht erzeugt/initialisiert werden konnte
        if (-1 == sock) {
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
        if (bytes_sent < 0) {
            printf("Packet konnte nicht gesendet werden: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        // Socket schließen
        close(sock);   
    }
private:    

};


int main()
{
    cout << "Prototyp des EmbeddedPC." << endl;

    for (;;){
        cout << "Bitte geben geben Sie die Daten ein:" << endl;
        string testString;// = "Testsignal vom Embedded-PC.";
        getline(std::cin, testString); 
        sendData(testString);
        cout << endl;
    }

    return 0;
}

void sendData(string estr)
{
    cout << "Daten werden via UDP gesendet.\n";
    SendC sc;
    sc.sChar(estr);
}

