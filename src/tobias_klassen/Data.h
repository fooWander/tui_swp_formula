#ifndef Data_H
#define Data_H

class Data
{
public:
	Data(double value, unsigned int datatype, unsigned int position);
	//~Data();

	/* data */
	double getValue();
	unsigned int getDatatype();
	unsigned int getPosition();

private:
	double myValue;
	unsigned int myDatatype;
	unsigned int myPosition;
};

#endif
