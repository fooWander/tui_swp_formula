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
    int stand;
	unsigned int position[401];
	double daten[401];
};

#endif
