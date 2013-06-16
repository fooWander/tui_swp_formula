#include <iostream>
#include "dbData.h"
using namespace std;

  int main()
  {
    cout << "main called" << endl;
    dbData db;
    cout << "Host= " << db.getHost() << " User = " << db.getUser() << " PW= " << db.getPW() << " DB= " << db.getDB() << endl;

    return 0;
  }
