//============================================================================
// Name        : umwandlungstest.cpp
// Author      : Tino
// Version     :
// Copyright   : SWP-Ilmenau
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include<fstream>
#include <unistd.h>
using namespace std;

char buf[6433];
short shZahlen[402];
char Zeit[16];


void Empfangen(){
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
  my_addr.sin_port        = htons(7777);

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
}
//}
void Zeitstempel(){
	for (int k=0; k<16; k++){
		Zeit[k]=buf[k];
	}

}


void Umwandeln(){

	for (int i=1; i<402; i++)
	{
	    shZahlen[i] = 0;
	    for (int j=0; j<16; j++)
	    {
	        if (buf[i*16+j] != '0')
	            shZahlen[i] += 1 << (15-j);
	    }
	    cout << shZahlen[i] << endl;
	}

}











int main() {
	Empfangen();
	Zeitstempel();
	Umwandeln();
	printf("Zeitstempel");
	cout << Zeit << endl;

}





/*
char test[33]="11111111110000110000000011111111";
char help[17];
int j;
double d;

int main() {

	for(int j=sizeof(test);j<34;j++){


	for(int i=sizeof(help);i<18;i++){

	for(int a=0;a<=15;a++){
		if(test[a]=='1'){
		strcat(help,"1");
		}
		else{
			strcat(help,"0");
		}
}
	printf("\nhelp: %s\n",help);
d = atof(help);

//printf("\n Double: %f\n",d);
int x = (int) d;
	cout << x << endl; // prints
d=0;
	}
	help[0]='\0';
	}



	//test=1111111111000011;
	int x = (int) 0b1111111111000011;
	cout << x << endl; // prints

	for(int u=0;u<17;u++){
	for(j=(sizeof(test[u]) * 8) - 1; j >= 0;j--){

	 if(test[u] & (1 << j)){
		printf("1\n");

	 }
	  else      {
		printf("0\n");
	  } //if ENDE
	} 	//for ENDE
	}


	return 0;

}
*/

