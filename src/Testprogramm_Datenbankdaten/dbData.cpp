#include "dbData.h"

using namespace std;

  dbData::dbData()
  {
        fstream file("dbconfig.txt");
        int i = 1;
        while(!file.eof())
        {
	  switch(i){
	    case 2:
	      file >> host;
            case 4:
              file >> user;
            case 6:
              file >> pw;
            case 9:
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



