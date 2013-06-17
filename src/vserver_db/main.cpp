#include <iostream>
#include "DBPacketInsert.h"

using namespace std;

int main(int argc, const char **argv)
{
	cout << "Start." << endl;
	DBPacketInsert inserts;
	for(int i=0; i<10; i++){
	    inserts.db_insert();
	}
}
