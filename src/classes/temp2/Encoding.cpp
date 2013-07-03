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
char VEC_LAYOUT[] = {0,0, 20, 0, 25, 0, 30,0, 100,0};
int VEC_LAYOUT_SIZE = 10;

int PACKAGE_COUNTER = 80;
int64_t TIME_THRESHOLD=50000000000;
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
    //int test;
    //std::cout << "VLAL" << std::endl;
    clock_gettime(CLOCK_REALTIME, &timestamp);
    //std::cout << "TIME: " << test << std::endl;
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
    std::cout << "SUMME_1 " << myPackageSum << std::endl;
    for (int i = 0; i < sizeof(myPackagePos)/sizeof(int16_t); ++i) {
        myPackagePos[i] = -1;
    }
    splitData(buffer, bufferlen,vecLayout, vecLayoutlen);
    std::cout << "TEST" << std::endl;
    //compressData();
    
}

int Encoder::getPackageSum()
{
    std::cout << "getPackageSum called: " << myPackageSum << std::endl;
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

int Encoder::getPackage(char * package, int len, unsigned short packageNumber)
{
    std::cout << "packageNumber = " << packageNumber << std::endl;
    //std::cout << "==========myPackages===========" << std::endl;
    for (int i = 0; i < 100; ++i) {
        //std::cout << myPackages[i];
    }
    //std::cout << "==========/myPackages===========" << std::endl;
    
    int dataSize;
    
    dataSize = myPackagePos[packageNumber+1] - myPackagePos[packageNumber];
    //dataSize = getPackageSize(packageNumber);
    std::cout << myPackagePos[packageNumber + 1] << std::endl;
    std::cout << myPackagePos[packageNumber] << std::endl;
    std::cout << "DATASIZE:" << dataSize << std::endl;

    if (dataSize > len) {
        return -1;
    }

    for (int i = 0; i < dataSize; ++i)
    {
        package[i] = myPackages[myPackagePos[packageNumber] + i];
    }
    return dataSize;
}

int Encoder::getNextPackage(char * package, int len)
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
    //std::cout << "================Creating header ================" << std::endl;
    int64_t timestamp = getTimestamp();
    //std::cout << "Zeistempel: " << timestamp << std::endl;
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
    int startPos = 0;
    int endPos = 0;
    /*
    std::cout << "vecLAYOUT: " << std::endl;
    for (int j = 0; j < vecLayoutlen; j=j+2) {
        if (j % 25 == 0) {
            std::cout << std::endl;
        }
        std::cout << joinUnsigShort(vecLayout[j+1],vecLayout[j]) << " ";
    }
    std::cout << std::endl;
    */
    for (int i = 0; i < vecLayoutlen; i=i+2) {
        if (pointer >= ((vecLayoutlen/2 * 12) + bufferlen))
        {
            break;
        }
        myPackagePos[pointer] = myPackagePointer;

        //std::cout << "myPackagePointer: " << myPackagePointer << std::endl;
        //std::cout << "pointer: " << pointer << std::endl;

        createHeader();

        startPos = joinUnsigShort(vecLayout[i+1],vecLayout[i]);

        if (startPos >= bufferlen) {
            std::cout << "ERROR" << std::endl;
        }

        //std::cout << "STARTPOS: " << startPos << std::endl;
        if (i+2 > vecLayoutlen || i+3 > vecLayoutlen) {
            endPos = 401;
        } else {
            endPos = joinUnsigShort(vecLayout[i+3], vecLayout[i+2]);
            std::cout << "ENDPOS: " << endPos << std::endl;
        }

        if (endPos >= bufferlen) {
            std::cout << "ERROR" << std::endl;;
        }

        
        //std::cout << "myPackagePointer " << myPackagePointer << std::endl;
        for (int j = 2*startPos; j < 2*endPos; ++j) {
            myPackages[myPackagePointer] = buffer[j];
            //std::cout << "POS: " << myPackagePos[pointer] << ":" << pointer << ":" << j << std::endl;
            //std::cout << j << std::endl;
            //std::cout << "POINTER: " << myPackagePointer << std::endl;
            //std::cout << joinUnsigShort(myPackages[myPackagePointer+1],myPackages[myPackagePointer]) << std::endl;
            
            myPackagePointer++;
        }  
        pointer++;
        //std::cout << "SUM: " << myPackageSum << std::endl;    
    }
    std::cout << "POINTER: " << myPackagePointer << std::endl;
    myPackagePos[pointer] = myPackagePointer;
    /*
    std::cout << "PACKAGES: " << std::endl;
    for (int j = 0; j < bufferlen; j=j+2)
        {
            if (j % 25 == 0)
            {
                std::cout << std::endl;
            }
            //std::cout << (int)DATA_SEN D[j] << " ";
            std::cout << joinUnsigShort(myPackages[j+1],myPackages[j]) << " ";
        }
    std::cout << std::endl;
    */
    /*
    std::cout << "==========PACKAGESPOS===========" << std::endl;
    for (int i = 0; i < pointer; ++i)
    {
        std::cout << myPackagePos[i] << std::endl;
    }
    std::cout << "==========PACKAGEPOS END============" << std::endl;
    */
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
    VEC_DATATYPES_SIZE = joinUnsigShort(buffer[1],buffer[0]);
    VEC_LAYOUT_SIZE = joinUnsigShort(buffer[3],buffer[2]) * 2;
    VEC_COMMA_SIZE = joinUnsigShort(buffer[5],buffer[4]);
    /*
    VEC_DATATYPES_SIZE = 401;
    VEC_LAYOUT_SIZE = 5;
    VEC_COMMA_SIZE = 401;
    */
    std::cout << VEC_DATATYPES_SIZE << std::endl;
    std::cout << VEC_LAYOUT_SIZE << std::endl;
    std::cout << VEC_COMMA_SIZE << std::endl;

    //int border_0 = 6 + 2*(VEC_DATATYPES_SIZE);
    int border_0 = (VEC_DATATYPES_SIZE) + 6;
    int border_1 = border_0 + (2 * VEC_LAYOUT_SIZE);
    int border_2 = border_1 + (VEC_COMMA_SIZE);

    int j = 0;

    std::cout << "=========VEC_DATATYPES==========" << std::endl;
    for (int i = 6; i < border_0; ++i) {
        VEC_DATATYPES[j] = buffer[i];
        std::cout << (int)VEC_DATATYPES[j] << " ";
        if (j % 32 == 0 && j != 0)
        {
            std::cout << std::endl;
        }
        j = j+2;
    }

    j = 0;

    for (int i = border_0 ;i < border_1; ++i) {
        //std::cout << "TEST" << std::endl;
        VEC_LAYOUT[j] = buffer[i];
        
        //std::cout << "TEST" << std::endl;
        //std::cout << VEC_LAYOUT[j] << std::endl;
        j++;
    }
    std::cout << "=========VEC_LAYOUT=============" << std::endl;
    for (int i = 0; i < VEC_LAYOUT_SIZE; i=i+2)
    {
        std::cout << joinUnsigShort(VEC_LAYOUT[i+1],VEC_LAYOUT[i]) << " ";
        if (i % 32 == 0 && i != 0)
        {
            std::cout << std::endl;
        }
    }
    j = 0;
    
    std::cout << std::endl << "=========VEC_COMMA==============" << std::endl;
    for (int i= border_1 -10;i < border_2-10; ++i) {
        VEC_COMMA[j] = buffer[i];
        std::cout << (int)VEC_COMMA[j] << " ";
        if (j % 32 == 0 && j != 0)
        {
            std::cout << std::endl;
        }
        j = j+2;
    }

    std::cout << "TEST" << std::endl;
}

Decoder::Decoder(char * buffer, size_t bufferlen, char * vecLayout, size_t vecLayoutlen,
                char * vecDatatypes, size_t vecDatatypeslen, char *vecComma, size_t vecCommalen)
    : /*myDataPos(8),myPackagePos(0),myTimestamp(0),*/myDataLength(0)
{
    myDataPos = 12;
    myTimestampStatus = 1;
    myPackage = buffer;
    myPackagelen = bufferlen;
    std::cout << "Decoding header..." << std::endl;
    decodeHeader();
    std::cout << "Checking timestamp..." << std::endl;
    checkTimestamp();
    std::cout << "Decode package positions..." << std::endl;
    std::cout << myPackageNum << std::endl;
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
    //std::cout << myTimestamp << std::endl;

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
        myTimestampStatus = -1;
        return;
    } else {
        myTimestampStatus = 1;
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
    myPackagePos = joinUnsigShort(vecLayout[(2 * myPackageNum)+1],
                                    vecLayout[(2 * myPackageNum)]);
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

int Decoder::getTimestampStatus() 
{
    return myTimestampStatus;
}

