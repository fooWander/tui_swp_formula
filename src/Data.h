#ifndef Data_H
#define Data_H

class Data
{
public:
	Data(double value, unsigned int datatype, unsigned int position, int decPointValue);
	//~Data();

	/* data */
	int getValue();
	unsigned int getDatatype();
	unsigned int getPosition();
	int getDecPointValue();

private:
	double myValue;
	unsigned int myDatatype;
	unsigned int myPosition;
	int myDecPointValue;
};

#endif
