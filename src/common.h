/*

	TODO: Add all includes here.

*/
			//#include "PracticalSocket.h"
			#include "Data.h"
//#include "Encoding.h"
#include <string>
			//#include "Encoding.h"
//#include "vserver.h"


const int PACKAGESIZE_MAX = 65535;

char DATA_ACK_VSERVER[] = {1}; 
char DATA_PACKAGE[PACKAGESIZE_MAX];
char DATA_PACKAGE_INFO[PACKAGESIZE_MAX];

Location HOST_EMBPC("10.42.0.55",5000);
Location HOST_MABXII("10.42.0.42",5002);
Location HOST_VSERVER("87.106.17.165",5000);

int LOCAL_TIMESTAMP;
char MSG_INFO_REQUEST[] = {96};
char MSG_READY[] ="144"; //={144}
int PACKAGE_COUNTER;
unsigned int TIME_THRESHOLD=5; //###

char VEC_COMMA[PACKAGESIZE_MAX];
int VEC_COMMA_SIZE;
char VEC_DATATYPES[PACKAGESIZE_MAX];
int VEC_DATATYPES_SIZE;
char VEC_LAYOUT[PACKAGESIZE_MAX];
int VEC_LAYOUT_SIZE;

int LOCALPORT = 5000;
