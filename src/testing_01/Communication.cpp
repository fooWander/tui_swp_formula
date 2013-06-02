#include <Communication.h>
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

Sender::Sender()
{
    myData = NULL;
    myHeader = NULL;
    myDestination = NULL;
}

Sender::Sender(Header h, Data d, Destination dest)
{
    myHeader = h;
    myData = d;
    myDestination = dest;
}

void Sender::addHeader(Header h)
{
    myHeader = h;
    if (myData && myDestination != NULL)
        readyToSend = true;
}

void Sender::removeHeader()
{
    readyToSend = false;
    myHeader = NULL;
}

void Sender::addData(Data d)
{
    myData = d;
    if (myHeader && myDestination != NULL)
        readyToSend = true;
}

void Sender::removeData()
{
    readyToSend = false;
    myData = NULL;
}

void Sender::setDestination(Destination dest)
{
    myDestination = dest;
    if (myHeader && myData != NULL)
        readyToSend = true;
}

void Sender::resetDestination()
{
    readyToSend = false;
    myDestination = NULL;
}

bool Sender::sendPackage() 
{
    int sizeOfHeader = sizeof(myHeader);
    int sizeOfData = sizeof(myData);
    int sizeOfDestination = sizeof(myDestination);
    int sizeOfPackage = sizeOfHeader + sizeOfData;

    char package[sizeOfPackage+1];

    Socket s(myDestination.addr, myDestination.port);
    int sockfd = s.getSocketDescriptor();

    if (sendto(sockfd, package, 0, (struct sockaddr *) 
        s.getRemoteAddrMemPlace(), sizeof(myDestination.addr)) {
        printf("Sendung erfolgreich!\n");
    } else {
        fprintf(stderr, "Fehler beim Senden!\n");
    }   
    s.closeSocket();
}

Socket::Socket() 
{
    myRemoteAddr = 0;
    myRemotePort = 0;
    myLocalPort = 0;
    socketCreated = false;
}

Socket::Socket(unsigned short localPort)
{
    /*
    cout << "\n EMPFANGEN:" << endl;
    int sockfd;
    struct sockaddr_in my_addr, remote_addr;
    socklen_t remote_addr_size = sizeof(remote_addr);


    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        // fprintf(stderr, "Error: socket()\n");
        cout << "\n socketERROR:" << endl;
        // return(1);
    }

    my_addr.sin_family      = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port        = htons(5000);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0){
        //fprintf(stderr, "Error: bind()\n");
        cout << "\n bindERROR:" << endl;
        shutdown(sockfd,2);
        //return(1);
    }

    //for(;;){ später mit poll
    if (recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&remote_addr, &remote_addr_size) > 0){
        //printf("Getting Data from %s\n", inet_ntoa(remote_addr.sin_addr.s_addr) );
        printf("Daten: %s\n", buf);

    }

    //printf("ENDE\n");
  cout << "\n ENDE:" << endl;
  */

  // TODO
}

Socket::Socket(unsigned short remoteAddr, unsigned short remotePort)
{
    myRemoteAddr = remoteAddr;
    myRemotePort = remotePort;
    cout << "\n SENDEN:" << endl;
    //strcat(rack,muell);  //evtl fuer Zeitstempel
    int sockfd;
    struct sockaddr_in remote_addr;
    struct hostent *host_addr;

    memset(&remote_addr, 0, sizeof remote_addr);
    remote_addr.sin_addr.s_addr = inet_addr(remoteAddr);

    if ((socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "Error: socket()\n");
        return(-1);
    }

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(remotePort);

}