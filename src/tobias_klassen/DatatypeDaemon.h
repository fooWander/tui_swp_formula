#ifndef DatatypeDaemon_H
#define DatatypeDaemon_H

#include <string>
#include <boost/lexical_cast.hpp>
#include "Data.h"
#include "Decoder.h"

using namespace std;
using namespace boost;

class DatatypeDaemon{
	public:
		DatatypeDaemon();
		string parseNextValue();
		int getPosActualPacket();
		int getTime();
	private:
		unsigned int dataType;
		int pos;
};

#endif
