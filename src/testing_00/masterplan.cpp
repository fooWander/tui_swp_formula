/*
 * masterplan.cpp
 *
 *  Created on: 30.05.2013
 *      Author: nogs
 */

/* Diese Programm wurde so einfach wie möglich gestaltet um die Funktionalität
 * zu testen und später anzupassen oder zu vervollständigen
 *
 */


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$_Bibliotheken_$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <stdio.h>      // printf, NULL
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//#include <math.h>
#include <time.h>       // time
#include <stdlib.h>     // srand, rand
#include <sys/types.h>
#include <arpa/inet.h>  //fuer inet_addr
#include <fstream>       //Speicher in Datei
#include <unistd.h>     //fuer sleep
using namespace std;





//##################################################_globaleVariablen_##################################################
#define MAX_DATE 21             //LOG
char the_date[MAX_DATE];        //LOG

//char rack[65535];
int zahl;       //Zufallszahl
int x,i,j;      //Zählervariablen
int anz=0;      //Anzahl der Zeichen Zeichen

struct T_nuex {
    short int testen[401];      //401 Werte
} variablen;

char muell[6416];       //HIER PROBLEM  // (401 Werte * 16 Bit )-1 = eigentlich 6416 -1



void Logzeit()
{
    time_t now;
    the_date[0] = '\0';
    now = time(NULL);

    if (now != -1) {
        strftime(the_date, MAX_DATE, "%H:%M:%S_%d_%m_%Y", gmtime(&now));
    }
}

//==================================================_DefinitionERZEUGEN_==================================================
void Erzeugen()
{
    fstream datei;
    //datei.open("DEZoutput.txt", ios::out);
    strcat(the_date,"DEZ");
    datei.open(the_date, ios::out);
    srand (time(NULL));     //zufallsstartpunkt fuer rand(void)

    //muell[0] = '\0';      //Leervorgang
    /*
    for(int t=13;t>0;t--) {
        variablen.testen[t]=t;
    }
    */
    variablen.testen[0]=1;
    variablen.testen[1]=0;
    variablen.testen[2]=1;
    variablen.testen[3]=1;
    variablen.testen[4]=0;
    variablen.testen[5]=1024;
    variablen.testen[6]=-512;
    variablen.testen[7]=-32;
    variablen.testen[8]=8192;
    variablen.testen[9]=-128;
    variablen.testen[10]=16384;
    variablen.testen[11]=1;
    variablen.testen[12]=65535;

    for (int u=13;u<401;u++) {            //restliche Zahlen Zufallszahlen vergeben
        zahl=rand()%(65535+32766)-32766;
        variablen.testen[u]= zahl;
         //printf("%i",zahl);
    }


    for (int u=0;u<401;u++) {                 //negative Zahlen umwandeln - Kompplement
        if (variablen.testen[u]<0) {
            variablen.testen[u]=65536+variablen.testen[u]; //+1     evtl 65535
        }
        datei << variablen.testen[u] << endl;

        for (j = (sizeof(variablen.testen[u]) * 8) - 1; j >= 0;j--) {
            if (variablen.testen[u] & (1 << j)) {
                //printf("1\n");
                strcat(muell,"1");
                anz++;
            } else {
                //printf("0\n");
                strcat(muell,"0");
                anz++;
            } //if ENDE
        }   //for ENDE
        //printf ("\n");
    }   //for ENDE
    datei.close();
}   //Funktion ENDE





//==================================================_DefinitionAUSGABE_==================================================
void Ausgabe()
{
    fstream datei;
    //datei.open("DUALoutput.txt", ios::out);
    // strcat(the_date,"txt");
    strcat(the_date,"BIN");
    datei.open(the_date, ios::out);
    datei << muell << endl;
    datei.close();

    printf ("%s\n",muell);
    printf ("Laenge: %i\n",sizeof(muell));
    printf ("Zeichenanzahl: %i\n",anz);

    //muell[0] = '\0';
    printf ("ENDE\n");
    //getchar();
}





//==================================================_DefinitionSENDEN_==================================================
int Senden()
{
    //strcat(rack,muell);  //evtl fuer Zeitstempel
    int sockfd;
    struct sockaddr_in remote_addr;
    struct hostent *host_addr;


    char Host [20]="localhost";  //www.eulerbox.no-ip.biz
    char IP [20]= "127.0.0.1"; //127.0.0.1


    if ((gethostbyname(Host)) == NULL) {
        printf("HOSTERROR\n");
        memset(&remote_addr, 0, sizeof remote_addr);
        remote_addr.sin_addr.s_addr = inet_addr(IP);
    } else {
        host_addr = gethostbyname(Host);
        remote_addr.sin_addr = *((struct in_addr *) host_addr->h_addr);
    }



    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "Error: socket()\n");
        return(1);
    }

    remote_addr.sin_family = AF_INET;
    // remote_addr.sin_addr   = *((struct in_addr *) host_addr->h_addr);
    remote_addr.sin_port   = htons(5000);


    if (sendto(sockfd, muell, strlen(muell) + 1, 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) > 0) {
        printf("Sendung erfolgreich!\n");
    } else {
        fprintf(stderr, "Fehler beim Senden!\n");
    }
    shutdown(sockfd,2);
}





//==================================================_HAUPTPROGRAMM_==================================================
int main()
{
    for(;;) {
        Logzeit();
        Erzeugen(); //----mit Dateiausgabe: DEZ----
        the_date[0] = '\0';
        Logzeit();
        Ausgabe();  //----mit Dateiausgabe: BIN----
        the_date[0] = '\0';
        Senden();   //----mit Host- & IP-Angabe----
        anz=0;
        //testen[0] = '\0';
        the_date[0] = '\0';
        muell[0] = '\0';
        //sleep(10);
    }
}


/* BEISPIEL:
 *
ERZEUGEN:
1111111000000000        -512            negative Zahl weil erstes Bit =1 -->65536-512=65024

1111111000000000        65024

--------------------------------------------------------------------------------------------------

EMPFANGEN:
1111111000000000        65024           Zahl größer als 32767           --> 65024-65536=-512

 *
 */

