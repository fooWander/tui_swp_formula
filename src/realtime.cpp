/*
 * ZEITSTEMPEL-TESTFUNKTION
 * Achten auf:
 * 		Jitter
 *		Zeitauflösung
 *			--> Nanosekunden
 *		Zeitquelle (Bias)
 *			--> Echtzeituhr des Systems
 *			--> ständige Abfragen vermeiden, da Abfrage etwas zeitintensiv
 *
 */
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
using namespace std;

#define NSEC_PER_SEC 1000000000ULL //unisigned long long - fuer Überlauf/Normierung
static struct timespec old, latest;

int64_t TO_NANO_SEC(struct timespec *t) {
  int64_t result;

  result	=  (int64_t)t->tv_sec;
  result	*= (int64_t)NSEC_PER_SEC; //Normierung
  result	+= (int64_t)t->tv_nsec;
  return result;
}

int main(/*int argc, char *argv[]*/)
{
	cout<<"Bitte warten..."<<endl;
    cout<<" "<<endl;
	int64_t	difference;
	int64_t	latency;

	clock_gettime(CLOCK_REALTIME, &old);
	//Aenderungen an sleep auch bei latency durchfuehren
	sleep(5);
	usleep(100000);
    clock_gettime(CLOCK_REALTIME, &latest);

    difference = TO_NANO_SEC(&latest) - TO_NANO_SEC(&old);

    	//Standardausgabe:
    	cout<<"Vorher: "<<TO_NANO_SEC(&old)<<endl;
    	cout<<"Danach: "<<TO_NANO_SEC(&latest)<<endl;
    	cout<<" "<<endl;
    	cout<<"Differenz: "<<difference<<endl;

    	fprintf(stderr,"\n\n");

    	//Formatiert:
    	fprintf(stderr,"this is before sleep: %lli.%09lli\n",((long long)TO_NANO_SEC(&old))/NSEC_PER_SEC, ((long long)TO_NANO_SEC(&old))%NSEC_PER_SEC);
    	fprintf(stderr,"this is after sleep: %lli.%09lli\n",((long long)TO_NANO_SEC(&latest))/NSEC_PER_SEC, ((long long)TO_NANO_SEC(&latest))%NSEC_PER_SEC);
    	fprintf(stderr,"\n\n");
    	fprintf(stderr,"difference: %lli.%09lli\n", ((long long)difference)/NSEC_PER_SEC, ((long long)difference)%NSEC_PER_SEC);
    	fprintf(stderr,"\n");

    	latency = difference - 5100000000; //= rund 225447 (auf Laptop)
    	cout<<"Latenz: "<<latency<<endl;
}
