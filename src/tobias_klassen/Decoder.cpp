//ACHTUNG: Dummy-Element
#include "Data.h"
#include "Decoder.h"

Decoder::Decoder()
{
	position=0;
	//Dummydaten initialisieren
	daten[0] = 0;
	daten[1] = 1;
	daten[2] = 1;
	daten[3] = 0;
	daten[4] = 1;
	daten[5] = 0;
	daten[6] = 0;
	daten[7] = 1;
	daten[8] = 0;
	daten[9] = 0;
	daten[10] = 999.9;
	daten[11] = -999.9;
	daten[12] = 7.8;
	daten[13] = 200.0;
	daten[14] = 100.0;
	daten[15] = -100.0;
	daten[16] = 1000.0;
	daten[17] = 1234567890;
	daten[18] = 130000;
	for(int i=19; i<401; i++){
		daten[i] = 1;
		if(i>359){
			daten[i] = i;
		}
	}
	daten[11] = 60;
}

Data Decoder::getNextValue()
{
	if(position<10){
		Data data(daten[position], 1, position);
		position++;
		return data;
	}else{
		if(position<214){
			Data data(daten[position], 4, position);
			position++;
			return data;
		}else{
			if(position<358){
				Data data(daten[position], 1, position);
				position++;
				return data;
			}else{
				Data data(daten[position], 4, position);
				position++;
				return data;
			}
		}
	}

	position++;
	if(position>=401)
		position = 0;

}

unsigned int Decoder::getTimestamp()
{
	unsigned int ts = 1111;
	return ts;
}
