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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>

using namespace std;

#define NSEC_PER_SEC 1000000000ULL //unisigned long long - fuer Überlauf/Normierung
static struct timespec before, after;

int64_t timespec_to_ns(struct timespec *t) {
  int64_t result;

  result	=  (int64_t)t->tv_sec;
  result	*= (int64_t)NSEC_PER_SEC; //Normierung
  result	+= (int64_t)t->tv_nsec;
  return result;
}

int main(/*int argc, char *argv[]*/)
{
	cout<<"Bitte warten..."<<endl;
	int64_t		timedifference;

	clock_gettime(CLOCK_REALTIME, &before);
	sleep(5);
	usleep(100000);
    clock_gettime(CLOCK_REALTIME, &after);

    cout<<"Fertig!"<<endl;
    cout<<" "<<endl;

    timedifference = timespec_to_ns(&after) - timespec_to_ns(&before);

    	//Standardausgabe:
    	cout<<"Vorher: "<<timespec_to_ns(&before)<<endl;
    	cout<<"Danach: "<<timespec_to_ns(&after)<<endl;
    	cout<<" "<<endl;
    	cout<<"Differenz: "<<timedifference<<endl;

    	fprintf(stderr,"\n\n");

    	//Formatiert:
    	fprintf(stderr,"this is before sleep: %lli.%09lli\n", ((long long)timespec_to_ns(&before))/NSEC_PER_SEC, ((long long)timespec_to_ns(&before))%NSEC_PER_SEC);
    	fprintf(stderr,"this is after sleep: %lli.%09lli\n", ((long long)timespec_to_ns(&after))/NSEC_PER_SEC, ((long long)timespec_to_ns(&after))%NSEC_PER_SEC);
    	fprintf(stderr,"\n\n");
    	fprintf(stderr,"Timediff: %lli.%09lli\n", ((long long)timedifference)/NSEC_PER_SEC, ((long long)timedifference)%NSEC_PER_SEC);
    	fprintf(stderr,"\n");
}
