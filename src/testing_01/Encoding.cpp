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

Encoder::Encoder(const char * buffer, const int bufferlen, const char * vecLayout, const int vecLayoutlen,
                const char * vecDatatypes, const int vecDatatypeslen) 
    : myPackageSum(0), myPackagePointer(0), myPackageNum(0)
{
    myPackageSum = vecLayoutlen/2;
    myPackagePos[myPackageSum];
    splitData(buffer, bufferlen,vecLayout, vecLayoutlen);
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
        return ((myPackagePos[packageNumber - 1] - myPackagePos[packageNumber - 2]) - 1)
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
    return getPackage(package, myPackagePointer++);

}

Encoder::createHeader()
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

}

Decoder::Decoder(char * buffer, const int bufferlen, )