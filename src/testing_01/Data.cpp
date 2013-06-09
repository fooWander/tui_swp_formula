#include "Data.h"

Data::Data(int value, unsigned int datatype, unsigned int position)
	: myValue(value), myDatatype(datatype), myPosition(position)
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