#include <iostream>
#include "logData.h"
#include "resizeDB.h"

using namespace std;

int main(){
  resizeDB rsDB;
  logData lg;
  bool error;
  error = rsDB.resDB();
  if (error){
    lg.logWrite(6, "Es sind Fehler beim leeren der Datenbank aufgetreten");
  }
  else{
    lg.logWrite(4, "Es sind keine Fehler beim leeren der Datenbank aufgetreten");
  }
 return 0;  
}