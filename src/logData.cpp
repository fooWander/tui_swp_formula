#include "logData.h"
using namespace std;

  void logData::logWrite(int loglevel, string msg){
    //Loglevelueberpruefung:
    if (loglevel > 3.0){
      time_t now = time(0);
      //Logdatei oeffnen und Nachricht schreiben:
      ofstream log("log.txt", ios::out|ios::app);
      if (log.is_open()){
        log << ctime(&now) << "  "  << msg << " (Loglevel: " << loglevel << ")\n" << endl;
      }
      log.close();
    }
  }

  //Benutzung der ueberladenen Funktion
  void logData::logWrite(string msg){
	logWrite(6, msg);
  }
