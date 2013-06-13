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

/*class Encoding
{
public:
    Encoding(arguments);
    ~Encoding();

    // Don't know whether this makes sense
    
};
*/

#include "Data.h"

class Encoder
{
public:
    /* 
        Constructor creates an Encoder object from data stored in buffer.
        According to vecLayout and vecDatatypes the data gets divided into 
        different packages and compressed. The result is stored in myPackages
        and the layout of myPackages in myPackagePos.
    */
    Encoder(const char *buffer, const int bufferlen, const char *vecLayout, const int vecLayoutlen,
            const char *vecDatatypes, const int vecDatatypeslen);
    ~Encoder();
    /*
        After getPackage() returns package contains the specified package (packageNumber).
        The return value is the size of written data.
    */
    int getPackage(char * package, unsigned short packageNumber);
    /*
        Works just like getPackage but instead of specifing a packageNumber each call
        returns the next package (1,2,3,1,2,3,1,...).
    */
    int getNextPackage(char * package);
    /*
        Returns the size of the specified package (packageNumber).
    */
    unsigned int getPackageSize(unsigned short packageNumber);
    /*
        Returns the amount total amount of packages as written in vecLayout.
    */
    unsigned int getPackageSum();

private:

    /*
        Creates a 8byte header consisting of a timestamp and an ID.
    */
    void createHeader();
    /*
        Splits an array of elements according to a specific layout.
    */
    void splitData();
    /*
        Compresses a data package.
    */
    void compressData();

    /*
        Packages which are ready to be send.
    */
    char myPackages[];
    /*
        Position of each package in myPackages.  
    */
    unsigned short myPackagePos[];
    /*
        Total sum of packages.
    */
    unsigned short myPackageSum;
    /*
        Points to the next free space in myPackages.
    */
    int myPackagesPointer;
    /*
        Points to the next to be processed package. (1,...,myPackageSum)
    */
    int myPackageNum;
    /*
    char myBuffer;
    int myBufferlen;
    char MyVecLayout;
    int myVecLayoutlen;
    char MyVecDatatypes;
    */
    const char * buffer; // delete
};

class Decoder
{
public:
    /*
        Creates a Decoder object that is used to decode PACKAGE_INFO
    */
    Decoder(char *buffer, const int bufferlen);
    /*
        Create a Decoder object that decodes a buffer according to the information stored in vecLayout, 
        vecDatatypes and vecComma. 
    */
    Decoder(char *buffer, const int bufferlen, char *vecLayout, const int vecLayoutlen, 
            char *vecDatatypes, const int vecDatatypeslen, char *vecComma, const int vecCommalen);
    ~Decoder();
    /*
        With getNextData you get a Data object containing the postion ("name"), value and datatype.
    */
    Data getNextData();
    /*
        Returns the number of the currently decoded package.
    */
    unsigned int getPackageNum();
    /*
        Returns the timestamp of the currently processed package.
    */
    unsigned int getTimestamp();
private:
    unsigned int myDataLength;
    unsigned int myTimestamp;
    /*
        Number of currently processed package.
    */
    unsigned int myPackageNum;
    /*
        Position of package in original data stream.
    */
    unsigned int myPackagePos;
    unsigned int myDataPos;
    void checkTimestamp();
    void decodeHeader();
};