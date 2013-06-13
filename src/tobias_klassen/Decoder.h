#ifndef Decoder_H
#define	Decoder_H

using namespace std;

class Decoder
{
public:
    Decoder();
    Data getNextData();
	unsigned int getTimestamp();

private:
	unsigned int position;
	double daten[401];
};

#endif
