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
#include <iostream>

//const int PACKAGESIZE_MAX;


char VEC_COMMA[];
int VEC_COMMA_SIZE;
char VEC_DATATYPES[];
int VEC_DATATYPES_SIZE;
char VEC_LAYOUT[] = {0,5,0,3,0,2,0,10};
int VEC_LAYOUT_SIZE;

int PACKAGE_COUNTER;
unsigned int TIME_THRESHOLD=5;
int LOCAL_TIMESTAMP;

int exp10(int exp)
{
    int res = 1;
    for (int i = 1; i <= exp; ++i)
    {
        res = res / 10;
    }

    return res;
}


Encoder::Encoder(const char * buffer, const int bufferlen, const char * vecLayout, const int vecLayoutlen,
                const char * vecDatatypes, const int vecDatatypeslen) 
    : myPackageSum(0), myPackagePointer(0), myPackageNum(1)
{
    myPackageSum = vecLayoutlen/2;
    //myPackagePos[myPackageSum];
    std::cout << "Spliting data..." << std::endl;
    splitData(buffer, bufferlen,vecLayout, vecLayoutlen);
    std::cout << "Data splitted..." << std::endl;
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
    int len;
    if (packageNumber == 1)
    {
        len = myPackagePos[packageNumber] - 1;
        //std::cout << myPackagePos[packageNumber] - 1 << std::endl;
    } else {
        len = myPackagePos[packageNumber] - myPackagePos[packageNumber-1];
        //std::cout << myPackagePos[packageNumber] << std::endl;
        //std::cout << myPackagePos[packageNumber - 1] << std::endl;
    }
    for (int i = 0; i < len; ++i)
    {
        package[i] = myPackages[myPackagePos[packageNumber - 1] + i];
        //std::cout << myPackagePos[packageNumber - 1 + i] << std::endl;
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
    // add timestamp
    myPackages[myPackagePointer+3] = PACKAGE_COUNTER & 0xff;
    myPackages[myPackagePointer+2] = (PACKAGE_COUNTER >> 8) & 0xff;
    myPackages[myPackagePointer+1] = (PACKAGE_COUNTER >> 16) & 0xff;
    myPackages[myPackagePointer] = (PACKAGE_COUNTER >> 24) & 0xff;
    myPackagePointer += 4;
    PACKAGE_COUNTER++;

    // create ID
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

void Encoder::splitData(const char *buffer, const int bufferlen, 
                        const char *vecLayout, const int vecLayoutlen)
{
    int pointer = 0;
    unsigned short splitPos = 0;
    for (int i = 0; i < vecLayoutlen; i=i+2) {
        std::cout << "Spliting package " << i << std::endl;
        std::cout << "Creating header..." << std::endl;
        createHeader();
        splitPos = joinUnsigShort(vecLayout[i],vecLayout[i+1]);
        for (int j = 0; j < splitPos; ++j) {
            myPackages[myPackagePointer] = buffer[j];
            myPackagePointer++;
        }

        if (pointer == 0) {
            myPackagePos[pointer] = splitPos + 8;
        } else if (pointer != myPackageSum) {
            myPackagePos[pointer] = myPackagePos[pointer-1] + splitPos + 8;
        }

        pointer++;
    }
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
    decodeHeader(buffer, bufferlen);
    checkTimestamp();
    myPackagePos = getPackagePos(vecLayout, vecLayoutlen);
    //decompress();
}

/*
    Decode header of currently processed package (timestamp and ID (myPackageNum)).
*/
void Decoder::decodeHeader(char * buffer, const int bufferLen)
{
    myTimestamp = (buffer[3] & 0xff)  
                + ((buffer[2] << 8) & 0xff00)
                + ((buffer[1] << 16) & 0xff0000)
                + ((buffer[0] << 24) & 0xff000000);

    myPackageNum = (buffer[7] & 0xff)  
                + ((buffer[6] << 8) & 0xff00)
                + ((buffer[5] << 16) & 0xff0000)
                + ((buffer[4] << 24) & 0xff000000);
}

void Decoder::checkTimestamp()
{
    if ((LOCAL_TIMESTAMP - myTimestamp) > TIME_THRESHOLD) {  //###
        //getNextPackage();   Fuktion muss noch definiert werden
    } else {
        return;
    }
}

unsigned int Decoder::getPackagePos(char * vecLayout, const int vecLayoutlen)
{
    myPackagePos = joinUnsigShort(vecLayout[myPackageNum-1],vecLayout[myPackageNum]);
    return(myPackagePos);
}

Data Decoder::getNextData(char * buffer, /*const*/ unsigned int bufferlen)
{
    
    /* 
        double value = joinUnsigShort(buffer[myDataPos],buffer[myDataPos+1] 
                                * exp10(VEC_COMMA[myPackagePos+myDataPos]));
    */
    
    // value and UPPER_LIMIT_DATATYPE must be int because the UPPER-LIMIT of int16
    // int UPPER_LIMIT_DATATYPE = 32767;    --> globale variable
    // -32768 bis +32767                    --> Zahl 0 zählt positiv
    
    int value = joinUnsigShort(buffer[myDataPos],buffer[myDataPos+1];  
  
    if(value >= obereGrenzepositivDatantyp){
    value = value - UPPER_LIMIT_DATATYPE;
}

    
    int datatype = joinUnsigShort(VEC_DATATYPES[myDataPos],VEC_DATATYPES[myDataPos+1]);
    int pos = myDataPos;
    
    if ((myDataPos + 1) == bufferlen) //###   --> Vergleich bufferlen muss unsigned int sein
    {
       Data datEnd(-1.0,-1,-1); //###
        return datEnd;
    }
    Data dat(value,datatype,pos);
    myDataPos++;
    return dat;
}

