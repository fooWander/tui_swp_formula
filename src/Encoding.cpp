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
int HEADER_SIZE = 12;




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


Encoder::Encoder(const char * buffer, size_t bufferlen, const char * vecLayout, size_t vecLayoutlen,
                 const char * vecDatatypes, size_t vecDatatypeslen) 
    : myPackageSum(0), myPackagePointer(0), myPackageNum(1)
{
    if (vecLayoutlen % sizeof(int16_t) != 0) {
        /*
            vecLayoutlen muss Vielfaches von 2 sein, da jeder Fahrzeugwert 2 Bytes groß ist.
            Falls nicht: Exception werfen??
        */
    }
    myPackageSum = vecLayoutlen/sizeof(int16_t);
    for (int i = 0; i < sizeof(myPackagePos)/sizeof(int16_t); ++i) {
        myPackagePos[i] = -1;
    }
    splitData(buffer, bufferlen,vecLayout, vecLayoutlen);
    //compressData();
}

int Encoder::getPackageSum()
{
    if (myPackageSum < 1) {
        return -1;
    }
    return myPackageSum;
}



int Encoder::getPackageSize(unsigned short packageNumber)
{
    if (packageNumber < 1) {
        return -1;
    } else {
        return ((myPackagePos[packageNumber] 
                - myPackagePos[packageNumber - 1]) + HEADER_SIZE);
    }
}

int Encoder::getPackage(char * package, size_t len, unsigned short packageNumber)
{
    std::cout << "packageNumber = " << packageNumber << std::endl;
    std::cout << "==========myPackages===========" << std::endl;
    for (int i = 0; i < 100; ++i) {
        std::cout << myPackages[i];
    }
    std::cout << "==========/myPackages===========" << std::endl;
    
    int dataSize;
    dataSize = myPackagePos[packageNumber+1] - myPackagePos[packageNumber];
    //dataSize = getPackageSize(packageNumber);

    if (dataSize > len) {
        return -1;
    }

    for (int i = 0; i < dataSize; ++i)
    {
        package[i] = myPackages[myPackagePos[packageNumber] + i];
    }
    return dataSize;
}

int Encoder::getNextPackage(char * package, size_t len)
{
    if (myPackageNum == myPackageSum) {
        int myPackageNumTemp = myPackageNum;
        myPackageNum = 1;
        return getPackage(package, len, myPackageNumTemp);
    }
    return getPackage(package, len, myPackageNum++);

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
    
    myPackagePointer += 8;

    myPackages[myPackagePointer+3] = myPackageNum & 0xff;
    myPackages[myPackagePointer+2] = (myPackageNum >> 8) & 0xff;
    myPackages[myPackagePointer+1] = (myPackageNum >> 16) & 0xff;
    myPackages[myPackagePointer] = (myPackageNum >> 24) & 0xff;
    myPackagePointer += 4;
    myPackageNum++;
}

// Bitte lager mich aus
unsigned short joinUnsigShort(unsigned char a,unsigned char b)
{
    return (a<<8) + b;
}

void Encoder::splitData(const char *buffer, size_t bufferlen, 
                        const char *vecLayout, size_t vecLayoutlen)
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

Decoder::Decoder(char * buffer, size_t bufferlen)
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

Decoder::Decoder(char * buffer, size_t bufferlen, char * vecLayout, size_t vecLayoutlen,
                char * vecDatatypes, size_t vecDatatypeslen, char *vecComma, size_t vecCommalen)
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

unsigned int Decoder::getPackagePos(char * vecLayout, size_t vecLayoutlen)
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

