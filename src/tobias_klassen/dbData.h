#ifndef DBDATA_H
#define DBDATA_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

  class dbData
  {
    public:
      dbData();
      string getHost();
      string getUser();
      string getPW();
      string getDB();
    private:
      string host;
      string user;
      string pw;
      string db;

  };

#endif

