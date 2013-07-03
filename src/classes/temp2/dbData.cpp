#include "dbData.h"

using namespace std;
using namespace boost;

  dbData::dbData()
  {

        fstream file("Konfiguration.conf");
        while(!file.eof()){ 
          getline(file, parameter, '\n');
	  if(parameter == "#Hostadresse der Datenbank") {
                getline(file, value, '\n');
                host = value;
          }else if(parameter == "#Name des Datenbankbenutzers"){
                getline(file, value, '\n');
                user = value;
          }else if(parameter == "#Passwort des Datenbankbenutzers"){
                getline(file, value, '\n');
          	pw = value;
          }else if(parameter == "#Datenbankname"){
                getline(file, value, '\n');
                db = value;
          }
          /*
          else if(parameter == "#PACKAGE_SIZE_MAX"){
                getline(file, value, '\n');
                PACKAGE_SIZE_MAX = lexical_cast<int>(value);
          }else if(parameter == "#ACK_SIZE_MAX"){
                getline(file, value, '\n');
                ACK_SIZE_MAX =  lexical_cast<int>(value);
          }else if(parameter == "#DATA_NUM"){
                getline(file, value, '\n');
                DATA_NUM = lexical_cast<int>(value);
          }else if(parameter == "#DATA_NUM_OF_BYTES"){
                getline(file, value, '\n');
                DATA_NUM_OF_BYTES = lexical_cast<int>(value);
          }else if(parameter == "#EMBPC_IP"){
                getline(file, value, '\n');
                EMBPC_IP = value;
          }else if(parameter == "#MABXII_IP"){
                getline(file, value, '\n');
                MABXII_IP = value;
          }else if(parameter == "#VSERVER_IP"){
                getline(file, value, '\n');
                VSERVER_IP = value;
          }else if(parameter == "#MABXII_PORT"){
                getline(file, value, '\n');
                MABXII_PORT = lexical_cast<int>(value);
          }else if(parameter == "#MABXII_INFO_PORT"){
                getline(file, value, '\n');
                MABXII_INFO_PORT = lexical_cast<int>(value);
          }else if(parameter == "#EMBPC_PORT"){
                getline(file, value, '\n');
                EMBPC_PORT = lexical_cast<int>(value);
          }else if(parameter == "#EMBPC_INFO_PORT"){
                getline(file, value, '\n');
                EMBPC_INFO_PORT = lexical_cast<int>(value);
          }else if(parameter == "#VSERVER_PORT"){
                getline(file, value, '\n');
                VSERVER_PORT = lexical_cast<int>(value);
          }else if(parameter == "#VSERVER_INFO_PORT"){
                getline(file, value, '\n');
                VSERVER_INFO_PORT = lexical_cast<int>(value);
          }else if(parameter == "#MSG_READY_1"){
                getline(file, value, '\n');
                MSG_READY_1 = lexical_cast<int>(value);
          }else if(parameter == "#MSG_READY_2"){
                getline(file, value, '\n');
                MSG_READY_2 = lexical_cast<int>(value);
          }
          */else if(parameter == "#NORM_DB"){
                getline(file, value, '\n');
                NORM_DB = lexical_cast<int>(value);		

          }else if(parameter.length() >  0){	//Fehlerausgabe, Leerzeilen und mit # beginnende weglassen
	        if (parameter[0] != '#'){
		  logData log;
                  string msg = "dbData: Fehler beim Einlesen der Konfiguratiosdatei. Zeile mit folgendem Wert uebersprungen: " + lexical_cast<string>(parameter);
		  log.logWrite(5, msg);
		}
          }
        }	
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

  int dbData::getPACKAGE_SIZE_MAX()
  {
        return PACKAGE_SIZE_MAX;
  }

  int dbData::getACK_SIZE_MAX()
  {
        return ACK_SIZE_MAX;
  }

  int dbData::getDATA_NUM()
  {
        return DATA_NUM;
  }

  int dbData::getDATA_NUM_OF_BYTES()
  {
        return DATA_NUM_OF_BYTES;
  }

  string dbData::getEMBPC_IP()
  {
        return EMBPC_IP;
  }

  string dbData::getMABXII_IP()
  {
        return MABXII_IP;
  }

  string dbData::getVSERVER_IP()
  {
        return VSERVER_IP;
  }

  int dbData::getMABXII_PORT()
  {
        return MABXII_PORT;
  }

  int dbData::getMABXII_INFO_PORT()
  {
        return MABXII_INFO_PORT;
  }

  int dbData::getEMBPC_PORT()
  {
        return EMBPC_PORT;
  }

  int dbData::getEMBPC_INFO_PORT()
  {
        return EMBPC_INFO_PORT;
  }

  int dbData::getVSERVER_PORT()
  {
        return VSERVER_PORT;
  }

  int dbData::getVSERVER_INFO_PORT()
  {
        return VSERVER_INFO_PORT;
  }

  int dbData::getMSG_READY_1()
  {
        return MSG_READY_1;
  }

  int dbData::getMSG_READY_2()
  {
        return MSG_READY_2;
  }

  int dbData::getNORM_DB()
  {
	return NORM_DB;
  }

