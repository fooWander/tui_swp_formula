#include "dbData.h"

using namespace std;

  dbData::dbData()
  {
        fstream file("dbconfig.txt");
        int i = 0;
        while(!file.eof())
        {
	  switch(i){
	    case 0:
	      file >> host;
            case 1:
              file >> user;
            case 2:
              file >> pw;
            case 3:
              file >> db;
	  }
	
	i++;
	}
	//check:
	cout << "Host= " << host << " User= " << user << " PW= " << pw << " DB= " << db << endl;
 	
  }


  string dbData::getHost()
  {
	return host;
  }

  string dbData::getUser()
  {
        return user;
  }

  string dbData::getPW()
  {
        return pw;
  }

  string dbData::getDB()
  {
        return db;
  }



