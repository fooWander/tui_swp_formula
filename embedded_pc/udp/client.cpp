#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argument_count, char *argument_vector[])
{

  //Initialisierung der Variablen
  int sock;
  struct sockaddr_in sa;
  int bytes_sent;
  char buffer[255]; // ####
 
  strcpy(buffer, "Dies ist ein Prototyp");
 
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
  sa.sin_addr.s_addr = inet_addr("eulerbox.no-ip.biz");
 
  //festgelegter Port
  sa.sin_port = htons(9999); // ##PORT## 
 
  //sendto(int Socket, char Daten, int Dateilaenge, Flags, ZeilAddresse, int ZielStructurLaenge)
  bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  if (bytes_sent < 0) {
    printf("Packet konnte nicht gesendet werden: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
 
  close(sock); /* Socket schließen */
  return 0;
}
