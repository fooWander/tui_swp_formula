#include "Data.h"

Data::Data(double value, unsigned int datatype, unsigned int position, int decPointValue)
	: myValue(value), myDatatype(datatype), myPosition(position), myDecPointValue(decPointValue)
{
	// check for validity
}

int Data::getValue()
{
	return myValue;
}

unsigned int Data::getDatatype()
{
	return myDatatype;
}

unsigned int Data::getPosition()
{
	return myPosition;
}

int Data::getDecPointValue()
{
    return myDecPointValue;
}
