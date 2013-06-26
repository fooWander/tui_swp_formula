#include <iostream>
#include "logData.h"
#include <string>

using namespace std;

  int main()
  {
    cout << "Geben Sie einen Text ein:" << endl;
    logData lg;
    string insert;
    getline(cin, insert); 
    lg.logWrite(insert);
    lg.logWrite(-2, "Noe das willste nicht");
    string b =  ("Das klingt schön besser!");
    lg.logWrite(4, b);
    string sql_anw = "SELCET * FROM uni;";
    //lg.logWrite(1);
    return 0;
  }
