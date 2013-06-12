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

class Encoding
{
public:
    Encoding(arguments);
    ~Encoding();

    // Don't know whether this makes sense
    
};

class Encoder : public Encoding
{
public:
    /* Constructor creates an Encoder object from data stored in buffer.
    According to vecLayout and vecDatatypes the data gets divided into 
    different packages and compressed. The result is stored in myPackages
    and the layout of myPackages in myPackagePos.
    */
    Encoder(const char *buffer, const int bufferlen, const char *vecLayout, const int vecLayoutlen,
            const char *vecDatatypes, const int vecDatatypeslen);
    ~Encoder();
    /* Return a 
    */
    int getPackage(char * package, unsigned short packageNumber);
    int getNextPackage(char * package);
    unsigned int getPackageSize(unsigned short packageNumber);
    unsigned int getPackageSum();

private:
    void createHeader();
    void splitData();
    void compressData();
    char myPackages[];
    unsigned short myPackagePos[];
    unsigned short myPackageSum;
    int myPackagesPointer;
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

class Decoder : public Encoding
{
public:
    Decoder(char *buffer, const int bufferlen);
    Decoder(char *buffer, const int bufferlen, char *vecLayout, const int vecLayoutlen, 
            char *vecDatatypes, const int vecDatatypeslen, char *vecComma, const int vecCommalen);
    ~Decoder();
    Data getNextData(unsigned int pos);
    unsigned int getPackageNum();
    unsigned int getTimestamp();
private:
    unsigned int myDataLength;
    unsigned int myTimestamp;
    unsigned int myPackageNum;
        
};