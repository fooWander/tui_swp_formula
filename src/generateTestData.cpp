#include "iostream"
#include "cstdlib"

const int PACKAGESIZE_MAX = 65535;

//char DATA_ACK_VSERVER[] = {1}; 
char DATA_PACKAGE[PACKAGESIZE_MAX];
int DATA_PACKAGE_SIZE = 802;
char DATA_PACKAGE_INFO[PACKAGESIZE_MAX];

//char MSG_INFO_REQUEST[] = {96};
//char MSG_READY[] ={144}; //={144}
//int PACKAGE_COUNTER;
//unsigned int TIME_THRESHOLD=5; //###

char VEC_COMMA[802];
int VEC_COMMA_SIZE = 802;
char VEC_DATATYPES[802];
int VEC_DATATYPES_SIZE;
char VEC_LAYOUT[] = {0,20,0,3,0,2,0,200};
int VEC_LAYOUT_SIZE = 8;

int LOCALPORT = 5000;


int main(int argc, char const *argv[])
{
	for (int i = 0; i < 20; ++i)
	{
		if (i % 2 == 0)
		{
			DATA_PACKAGE[i] = 0;
		} else {
			DATA_PACKAGE[i] = 1;
		}
		VEC_DATATYPES[i] = 1;
		std::cout << "Value " << i << ": " << DATA_PACKAGE[i] << std::endl;
	}
	for (int i = 20; i < 802; ++i)
	{
		VEC_DATATYPES[i] = 4;
		DATA_PACKAGE[i] = rand() % 100;
		std::cout << "Value " << i << ": " << DATA_PACKAGE[i] << std::endl;
	}
}