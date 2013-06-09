#include <iostream>
#include "DBPacketInsert.h"

using namespace std;

int main(int argc, const char **argv)
{
	cout << "Start." << endl;
	DBPacketInsert inserts;
	inserts.db_insert();
}
