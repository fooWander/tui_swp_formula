#include <iostream>
#include "dbData.h"
using namespace std;

  int main()
  {
    cout << "main called" << endl;
    dbData db;
    cout << db.getHost() << endl;
    return 0;
  }
