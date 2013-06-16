/*
 *  Service Interface for Formula Student Car.
 *  Copyright (C) 2013  Christian Boxdörfer
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "Encoding.h"


#define NSEC_PER_SEC 1000000000ULL
//const int PACKAGESIZE_MAX;


char VEC_COMMA[];
int VEC_COMMA_SIZE;
char VEC_DATATYPES[];
int VEC_DATATYPES_SIZE;
char VEC_LAYOUT[] = {0,0, 0,20, 0,25, 0,30, 0,100};
int VEC_LAYOUT_SIZE = 10;

int PACKAGE_COUNTER = 80;
unsigned int TIME_THRESHOLD=5000000;
int64_t LOCAL_TIMESTAMP;




int exp10(int exp)
{
    int res = 1;
    for (int i = 1; i <= exp; ++i)
    {
        res = res / 10;
    }

    return res;
}

int exp2(int exp)
{
    int res = 1;
    for (int i = 0; i < exp; ++i)
    {
        res = res * 2;
    }

    return res;
}

int64_t TO_NANO_SEC(struct timespec *t) 
{
    int64_t result;
    result  =  (int64_t)t->tv_sec;
    result  *= (int64_t)NSEC_PER_SEC; //Normierung
    result  += (int64_t)t->tv_nsec;
    return result;
}

int64_t getTimestamp()
{
    int64_t result;
    struct timespec timestamp;
    clock_gettime(CLOCK_REALTIME, &timestamp);
    result = TO_NANO_SEC(&timestamp);
    return result;
}


Encoder::Encoder(const char * buffer, const int bufferlen, const char * vecLayout, const int vecLayoutlen,
                const char * vecDatatypes, const int vecDatatypeslen) 
    : myPackageSum(0), myPackagePointer(0), myPackageNum(1)
{
    myPackageSum = vecLayoutlen/2;
    //myPackagePos[myPackageSum];
    for (int i = 0; i < 100; ++i)
    {
        myPackagePos[i] = 0;
    }
    //std::cout << "Spliting data..." << std::endl;
    splitData(buffer, bufferlen,vecLayout, vecLayoutlen);
    //std::cout << "Data splitted..." << std::endl;
    //compressData();
}

unsigned int Encoder::getPackageSum()
{
    return myPackageSum;
}



unsigned int Encoder::getPackageSize(unsigned short packageNumber)
{
    if (packageNumber == 1)
    {
        return (myPackagePos[0] - 1);
    } else {
        return ((myPackagePos[packageNumber - 1] - myPackagePos[packageNumber - 2]) - 1);
    }
}

int Encoder::getPackage(char * package, unsigned short packageNumber)
{
    std::cout << "packageNumber = " << packageNumber << std::endl;
    std::cout << "==========myPackages===========" << std::endl;
    for (int i = 0; i < 100; ++i)
    {
        std::cout << myPackages[i];
    }
    std::cout << "==========/myPackages===========" << std::endl;
    int len;
    /*
    if (packageNumber == 0)
    {
        len = myPackagePos[packageNumber+1] - 1;
    } else {
        len = myPackagePos[packageNumber+1] - myPackagePos[packageNumber-1];
    }
    */
    len = myPackagePos[packageNumber+1] - myPackagePos[packageNumber];
    std::cout << "len: " << len << std::endl;

    for (int i = 0; i < len; ++i)
    {
        package[i] = myPackages[myPackagePos[packageNumber] + i];
    }
    return len;
}

int Encoder::getNextPackage(char * package)
{
    if (myPackageNum == myPackageSum) {
        int len = getPackage(package,myPackageNum);
        myPackageNum = 1;
        return len;
    }
    return getPackage(package, myPackageNum++);

}

void Encoder::createHeader()
{
    std::cout << "================Creating header ================" << std::endl;
    int64_t timestamp = getTimestamp();
    std::cout << "Zeistempel: " << timestamp << std::endl;
    myPackages[myPackagePointer+7] = timestamp & 0xff;
    myPackages[myPackagePointer+6] = (timestamp >> 8) & 0xff;
    myPackages[myPackagePointer+5] = (timestamp >> 16) & 0xff;
    myPackages[myPackagePointer+4] = (timestamp >> 24) & 0xff;
    myPackages[myPackagePointer+3] = (timestamp >> 32)& 0xff;
    myPackages[myPackagePointer+2] = (timestamp >> 40) & 0xff;
    myPackages[myPackagePointer+1] = (timestamp >> 48) & 0xff;
    myPackages[myPackagePointer] = (timestamp >> 56) & 0xff;
    
    for (int i = 0; i < 8; ++i)
    {
        std::cout << myPackages[myPackagePointer+7-i] << std::endl;
    }

    myPackagePointer += 8;
    std::cout << myPackagePointer << std::endl;

    // create ID
    /*
    myPackages[myPackagePointer+3] = 1212696648 & 0xff;
    myPackages[myPackagePointer+2] = (1212696648 >> 8) & 0xff;
    myPackages[myPackagePointer+1] = (1212696648 >> 16) & 0xff;
    myPackages[myPackagePointer] = (1212696648 >> 24) & 0xff;
    */
    myPackages[myPackagePointer+3] = myPackageNum & 0xff;
    myPackages[myPackagePointer+2] = (myPackageNum >> 8) & 0xff;
    myPackages[myPackagePointer+1] = (myPackageNum >> 16) & 0xff;
    myPackages[myPackagePointer] = (myPackageNum >> 24) & 0xff;
    myPackagePointer += 4;
    myPackageNum++;
    std::cout << myPackagePointer << std::endl;
    std::cout << "myPackageNum encoded: " << myPackageNum << std::endl;

}

// Bitte lager mich aus
unsigned short joinUnsigShort(unsigned char a,unsigned char b)
{
    return (a<<8) + b;
}

void Encoder::splitData(const char *buffer, const int bufferlen, 
                        const char *vecLayout, const int vecLayoutlen)
{
    int pointer = 0;
    //int k = 0;;
    unsigned short startPos = 0;
    unsigned short endPos = 0;
    /*
    for (int i = 0; i < bufferlen; ++i)
    {
        std::cout << buffer[i];
        if (i % 25 == 0)
        {
            std::cout << "|" << std::endl << "|";
        }
    }
    */

    for (int i = 0; i < vecLayoutlen; i=i+2) {
        myPackagePos[pointer] = myPackagePointer;
        std::cout << "myPackagePos: " << myPackagePos[pointer] << std::endl;
        std::cout << "pointer: " << pointer << std::endl;
        createHeader();

        
        startPos = joinUnsigShort(vecLayout[i],vecLayout[i+1]);
        if (i+2 > vecLayoutlen || i+3 > vecLayoutlen) {
            endPos = bufferlen;
        } else {
            endPos = joinUnsigShort(vecLayout[i+2], vecLayout[i+3]);
        }
        
        std::cout << "myPackagePointer " << myPackagePointer << std::endl;
        for (int j = startPos; j < endPos; ++j) {
            myPackages[myPackagePointer] = buffer[j];
            myPackagePointer++;
        }
        
        pointer++;
    }
    myPackagePos[pointer] = myPackagePointer;
    //std::cout << pointer << std::endl;
    std::cout << "myPackagesPos: " << myPackagePos[pointer] << std::endl;
    std::cout << "=====================" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << myPackagePos[i] << " ";

    }
    std::cout << std::endl << "=====================" << std::endl;
}

/*void Encoder::compressData()
{
    for (int i = 5 ; i < vecDatatypeslen; i+6)
    {
        if (joinUnsigShort(i,i+1) == 1)
        {
            
        }
    }
}*/

Decoder::Decoder(char * buffer, const int bufferlen)
{
    VEC_DATATYPES_SIZE = joinUnsigShort(buffer[0],buffer[1]);
    VEC_LAYOUT_SIZE = joinUnsigShort(buffer[2],buffer[3]);
    VEC_COMMA_SIZE = joinUnsigShort(buffer[4],buffer[5]);

    int border_0 = 6 + 2*(VEC_DATATYPES_SIZE);
    int border_1 = border_0 + 2*(VEC_LAYOUT_SIZE);
    int border_2 = border_1 + 2*(VEC_COMMA_SIZE);

    int j = 0;
    for (int i = 6; i < border_0; i=i+2) {
        VEC_DATATYPES[j] = joinUnsigShort(buffer[i],buffer[i+1]);
        //std::cout << "VEC_DATATYPES" << std::endl;
        //std::cout << VEC_DATATYPES[j] << std::endl;
        j++;
    }
    
    j = 0;
    for (int i = border_0 ;i < border_1; i=i+2) {
        VEC_LAYOUT[j] = joinUnsigShort(buffer[i],buffer[i+1]);
        //std::cout << "VEC_LAYOUT" << std::endl;
        //std::cout << VEC_LAYOUT[j] << std::endl;
        j++;
    }

    j = 0;
    for (int i= border_1;i < border_2; i=i+2) {
        VEC_COMMA[j] = joinUnsigShort(buffer[i],buffer[i+1]);
        //std::cout << "VEC_COMMA" << std::endl;
        //std::cout << VEC_COMMA[j] << std::endl;
        j++;
    }
}

Decoder::Decoder(char * buffer, const int bufferlen, char * vecLayout, const int vecLayoutlen,
                char * vecDatatypes, const int vecDatatypeslen, char *vecComma, const int vecCommalen)
    : /*myDataPos(8),myPackagePos(0),myTimestamp(0),*/myDataLength(0)
{
    myDataPos = 12;
    myPackage = buffer;
    myPackagelen = bufferlen;
    //std::cout << "Decoding header..." << std::endl;
    decodeHeader();
    //std::cout << "Checking timestamp..." << std::endl;
    checkTimestamp();
    //std::cout << "Decode package positions..." << std::endl;
    myPackagePos = getPackagePos(vecLayout, vecLayoutlen);
    //std::cout << "myPackagePos: " << myPackagePos << std::endl;
    //decompress();
}

/*
    Decode header of currently processed package (timestamp and ID (myPackageNum)).
*/
void Decoder::decodeHeader()
{
    //std::cout << "decoding header..." << std::endl;

    for (int i = 0; i < 8; ++i)
    {
        //std::cout << myPackage[7-i] << std::endl;
    }

    myTimestamp = ((myPackage[7] & 0xff)  
                + ((myPackage[6] << 8) & 0xff00)
                + ((myPackage[5] << 16) & 0xff0000)
                + ((myPackage[4] << 24) & 0xff000000)
                + (((int64_t)myPackage[3] << 32) & 0xff00000000)
                + (((int64_t)myPackage[2] << 40) & 0xff0000000000)
                + (((int64_t)myPackage[1] << 48) & 0xff000000000000)
                + (((int64_t)myPackage[0] << 56) & 0xff00000000000000));
    std::cout << myTimestamp << std::endl;

    myPackageNum = (myPackage[11] & 0xff)  
                + ((myPackage[10] << 8) & 0xff00)
                + ((myPackage[9] << 16) & 0xff0000)
                + ((myPackage[8] << 24) & 0xff000000);
    // TESTING
    //std::cout << "myPackageNum decoded: " << myPackageNum << std::endl;            
    //myPackageNum = 2;
    //TESTING
    //std::cout << "myPackageNum: " << myPackageNum << std::endl;
}

void Decoder::checkTimestamp()
{
    LOCAL_TIMESTAMP = getTimestamp();
    int64_t diff = LOCAL_TIMESTAMP - myTimestamp;
    std::cout << "Zeitdifferenz: " << (double)diff/1000000 << "ms" << std::endl;
    if (diff > TIME_THRESHOLD) {  //###
        //getNextPackage();   Fuktion muss noch definiert werden
    } else {
        return;
    }
}

unsigned int Decoder::getPackagePos(char * vecLayout, const int vecLayoutlen)
{
    //std::cout << exp2(3) << exp2(0) << std::endl;
    //std::cout << "myPackageNum: " << myPackageNum << std::endl;
    //std::cout << vecLayout[(2 * myPackageNum)-1] << std::endl;
    //std::cout << vecLayout[(2 * myPackageNum)] << std::endl;
    /*
    for (int i = 0; i < VEC_LAYOUT_SIZE; ++i)
    {
        std::cout << VEC_LAYOUT[i] << std::endl;
    }
    */
    myPackagePos = joinUnsigShort(vecLayout[(2 * myPackageNum)],
                                    vecLayout[(2 * myPackageNum)-1]);
    //std::cout << "getPackagePos: " << myPackagePos << std::endl;
    return(myPackagePos);
}

Data Decoder::getNextData()
{
    //std::cout << myPackage[myDataPos] << std::endl;
    //std::cout << myPackagelen << std::endl;
    double value = joinUnsigShort(myPackage[myDataPos],myPackage[myDataPos+1]);

    //int datatype = joinUnsigShort(VEC_DATATYPES[myDataPos],VEC_DATATYPES[myDataPos+1]);
    int datatype = 0;
    int pos = myDataPos;
    
    if ((myDataPos + 1) == myPackagelen) //###   --> Vergleich bufferlen muss unsigned int sein
    {
       Data datEnd(-1.0,-1,-1); //###
        return datEnd;
    }
    Data dat(value,datatype,pos);
    myDataPos++;
    return dat;
}

