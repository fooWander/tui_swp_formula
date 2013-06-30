#include <iostream>
#include "dbData.h"

using namespace std;

  int main()
  {
    cout << "Testprogramm gestartet" << endl;
    dbData db;
    cout << "Host= " << db.getHost() << " User = " << db.getUser() << " PW= " << db.getPW() << " DB= " << db.getDB() << endl;

    cout << "ServerIP= " << db.getVSERVER_IP() << "  EMBPC-Port= " << db.getEMBPC_PORT() << endl;

    return 0;
  }

