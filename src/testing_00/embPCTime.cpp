/*
 * embPCTime.cpp
 *
 *  Created on: 31.05.2013
 *      Author: nogs
 */

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

char timestamp[6433];       //Zeitstempel String groesse 20 Zeichen
char muell[6433];
char buf[6416];



void Empfangen()
{
    cout << "\n EMPFANGEN:" << endl;
    int sockfd;
    struct sockaddr_in my_addr, remote_addr;
    socklen_t remote_addr_size = sizeof(remote_addr);


    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        // fprintf(stderr, "Error: socket()\n");
        cout << "\n socketERROR:" << endl;
        // return(1);
    }

    my_addr.sin_family      = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port        = htons(5000);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
        //fprintf(stderr, "Error: bind()\n");
        cout << "\n bindERROR:" << endl;
        shutdown(sockfd,2);
        //return(1);
    }

    //for(;;){ später mit poll
    if (recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&remote_addr, &remote_addr_size) > 0) {
        //printf("Getting Data from %s\n", inet_ntoa(remote_addr.sin_addr.s_addr) );
        printf("Daten: %s\n", buf);
    }

    //printf("ENDE\n");
    cout << "\n ENDE:" << endl;
}




void Zeitstempel()
{
    cout << "\n TIME:" << endl;
    int sekund=0;           //dek. Sekunden
    int mikro=0;            //dekl. Mikrosekunden
    struct timeval zeit1;
    //sleep(1);
    gettimeofday(&zeit1,NULL);

    sekund = zeit1.tv_sec;
    mikro = zeit1.tv_usec;
    sprintf(timestamp,"%d%d", sekund,mikro);
}




void Senden()
{
    cout << "\n SENDEN:" << endl;
    //strcat(rack,muell);  //evtl fuer Zeitstempel
    int sockfd;
    struct sockaddr_in remote_addr;
    struct hostent *host_addr;


    char Host [33]="";
    //char Host [33]="s16929463.onlinehome-server.info";  //www.eulerbox.no-ip.biz
    char IP [20]= "87.106.17.165"; // 192.168.56.39


    if ((gethostbyname(Host)) == NULL) {
        printf("HOSTERROR\n");
        memset(&remote_addr, 0, sizeof remote_addr);
        remote_addr.sin_addr.s_addr = inet_addr(IP);
    } else {
        host_addr = gethostbyname(Host);
        remote_addr.sin_addr   = *((struct in_addr *) host_addr->h_addr);
    }


    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "Error: socket()\n");
        //return(1);
    }

    remote_addr.sin_family = AF_INET;
    // remote_addr.sin_addr   = *((struct in_addr *) host_addr->h_addr);
    remote_addr.sin_port   = htons(7777); //http://www.beej.us/guide/bgnet/output/html/multipage/htonsman.html


    if (sendto(sockfd, muell, strlen(muell) + 1, 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) > 0) {
        printf("Sendung erfolgreich!\n");
    } else {
        fprintf(stderr, "Fehler beim Senden!\n");
    }

    shutdown(sockfd,2);
}






int main()
{
    for(;;) {
        Empfangen();
        printf("Daten: %s\n", buf);
        Zeitstempel();
        printf("\n Zeitstempel: %s\n",timestamp);
        strcat(timestamp,buf);
        strcat(muell,timestamp);
        Senden();
        muell[0]='\0';
        buf[0]='\0';
    }
// schauen das gelichzeitig gesendet und empfangen werden kann?
}





