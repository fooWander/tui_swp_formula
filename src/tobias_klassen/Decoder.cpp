//ACHTUNG: Dummy-Element
#include "Data.h"
#include "Decoder.h"

Decoder::Decoder()
{
	position=0;
	//Dummydaten initialisieren
	for(int i=0; i<401; i++){
		daten[i] = 1;
		if(i>350){
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
	unsigned int ts = 1000;
	return ts;
}
