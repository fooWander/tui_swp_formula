#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{
  int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  struct sockaddr_in sa; 
  char buffer[1024]; // #### 
  ssize_t recsize;
  socklen_t fromlen;
 
  memset(&sa, 0, sizeof sa);
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  sa.sin_port = htons(9999); // ##PORT## 
  fromlen = sizeof(sa);
 
  if (-1 == bind(sock,(struct sockaddr *)&sa, sizeof(sa)))
  {
    perror("Server-Socket konnte nicht an Port gebunden werden");
    close(sock);
    exit(EXIT_FAILURE);
  } 
 
  for (;;) 
  {
    printf ("Empfangstest:....\n");
    recsize = recvfrom(sock, (void *)buffer, sizeof(buffer), 0, (struct sockaddr *)&sa, &fromlen);
    if (recsize < 0) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    printf("Datensatzlaenge: %d\n ", recsize);
    sleep(1);
    printf("Datagram: %.*s\n", (int)recsize, buffer);
  }
}
