
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

#ifndef __ENCODING_H_INCLUDED__
#define __ENCODING_H_INCLUDED__

//#include "common.h"
#include "Data.h"
#include <sys/types.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include "common.h"

//extern const int PACKAGESIZE_MAX;

extern char VEC_COMMA[401];
extern int VEC_COMMA_SIZE;
extern char VEC_DATATYPES[401];
extern int VEC_DATATYPES_SIZE;
extern char VEC_LAYOUT[100];
extern int VEC_LAYOUT_SIZE;
 
extern int PACKAGE_COUNTER;
extern int64_t TIME_THRESHOLD; //###
extern int64_t LOCAL_TIMESTAMP;


unsigned short joinUnsigShort(unsigned char a,unsigned char b);
/**
 *  Service, der aus einem kompletten Satz Fahrzeugdaten mehrere Pakete erzeugt
 *  und komprimiert. Die Komprimierung ist noch nicht implementiert.
 */ 

class Encoder
{
public:
    
    /**
     *  Erzeugt einen Encoder.
     *  
     *  \param buffer Die zu bearbeitenden Daten. Dabei muss es sich um einen Datenstrom
     *  handeln, in dem jeweils 2 Byte einen Fahrzeugwert entsprechen.
     *  \param bufferlen Die Länge der zu bearbeitenden Daten.
     *  \param vecLayout Gibt an, wie die Daten geteilt werden sollen. 
     *  \n [Anfangsbyte Paket 1, Anfangsbyte Paket 2, ..., Anfangsbyte Paket n]
     *  \param vecLayoutlen Die Länge von @a vecLayout.
     *  \param vecDatatypes Gibt an, um welchen Datentyp es sich jeweils handelt.
     *  \param vecDatatypeslen Die Länge von @a vecDatatypes.
     */

    Encoder(const char *buffer, size_t bufferlen, const char *vecLayout, size_t vecLayoutlen,
            const char *vecDatatypes, size_t vecDatatypeslen);
    //~Encoder();
    /**
     *  Holt ein Paket mit einer speziellen Paketnummer.
     *  \param package Speicher in den das Paket geschrieben werden soll.
     *  \param len Länge von @a package.
     *  \param packageNumber Paketnummer des gewünschten Pakets.
     *  \return Die Länge des Pakets oder -1 falls Paket mit @a packageNumber
     *  nicht vorhanden oder @a len zu klein.
     */

    int getPackage(char * package, int len, unsigned short packageNumber);
    
    /**
     *  Holt das jeweils nächste Paket. (1,2,...,n,1,2,...)
     *  \param package Speicher in den das Paket geschrieben werden soll.
     *  \param len Länge von @a package.
     *  \return Die Länge des Pakets oder -1 falls @a len zu klein.
     */

    int getNextPackage(char * package, int len);
    
    /**
     *  Gibt die Paketgröße eines speziellen Pakets zurück.
     *  \param packageNumber Paketnummer dessen Größe gesucht ist.
     *  \return Größe des Pakets oder -1 falls Paket mit @a packageNumber
     *  nicht vorhanden.
     */

    int getPackageSize(unsigned short packageNumber);
    /**
     *  Gibt die Anzahl der Pakete zurück.
     *  \return Anzahl der Pakete.
     */
    int getPackageSum();

private:

    /**
     *  Erzeugt einen Header bestehend aus einem 8 Byte großen Zeitstempel
     *  und einer 4 Byte großen Identifikationsnummer (hier: Paketnummer).
     */
    void createHeader();

    /**
     *  Teilt ein Paket in mehrere kleinere auf. Das Ergebnis steht anschließend
     *  in @a myPackages
     *  \param buffer Datenstrom der geteilt werden sollen.
     *  \param bufferlen Länge des Datenstroms @a buffer.
     *  \param vecLayout Gibt an wie die Daten geteilt werden sollen. 
     *  \n [Anfangsbyte Paket 1, Anfangsbyte Paket 2, ..., Anfangsbyte Paket n]
     *  \param vecLayoutlen Länge von @a vecLayout.
     */

    void splitData(const char * buffer, size_t bufferlen,
			const char * vecLayout, size_t vecLayoutlen);
    
    /**
     *  Komprimiert ein Paket. (bisher noch nicht implementiert)
     */

    void compressData();

    /**
     *  Speichert die geteilten Pakete und deren Header.
     */

    char myPackages[PACKAGE_SIZE_MAX];
    
    /**
     *  Speichert die Postion der einzelnen Pakete in @a myPackages.
     */

    short myPackagePos[1000];
    
    /**
     *  Speichert die Anzahl der Pakete.
     */

    short myPackageSum;
    
    /**
     *  Zeiger der für die Ermittlung der Paketpostion verwendet wird.
     */

    int myPackagePointer;

    /**
     *  Speichert das nächste Paket das von @a getNextPackage() geholt wird.
     */

    int myPackageNum;

    
    /*
    char myBuffer;
    int myBufferlen;
    char MyVecLayout;
    int myVecLayoutlen;
    char MyVecDatatypes;
    */
    //const char * buffer; // delete
};

class Decoder
{
public:
    
    /**
     *  Erzeugt einen Dekoder, der zum Dekodieren der Paketinformation dient.
     *  \param buffer Speicher, der die Paketinformationen enthält.
     *  [Layout,Datentypen,Kommasetzung]
     *  \param bufferlen Länge von @a buffer.
     */

    Decoder(char *buffer, size_t bufferlen);
    
    /**
     *  Erzeugt einen Dekoder der ein Datenpaket anhand der übergebenen Informationen
     *  dekodiert.
     *  \param buffer Speicher des Datenpakets.
     *  \param buffernlen Länge von @a buffer.
     *  \param vecLayout Aufteilung des ursprünglichen Datenstroms, die aus den Paketinformationen
     *  dekodiert wurden. Dient zur Ermittlung der konkreten Datensätze.
     *  \param vecLayoutlen Länge von @a vecLayout.
     *  \param vecDatatypes Beinhaltet die Informationen zu den Datentypen der jeweiligen
     *  Datensätze.
     *  \param vecDatatypeslen Länge von @a vecDatatypes.
     *  \param vecComma Beinhaltet die Kommasetzung sämtlicher Datensätze.
     *  \param vecCommalen Länge von @a vecComma. 
     */

    Decoder(char *buffer, size_t bufferlen, char *vecLayout, size_t vecLayoutlen, 
            char *vecDatatypes, size_t vecDatatypeslen, char *vecComma, size_t vecCommalen);
    //~Decoder();
    
    /**
     *  Holt den nächsten Datensatz aus den empfangenen Daten.
     *  \return Gibt ein Datenobjekt \ref Data zurück das sämtlich Informationen 
     *  über den Datensatz enthält.
     */

    Data getNextData(); //###
    
    /**
     *  Holt die Paketnummer des akutell bearbeiteten Pakets.
     *  \return Paketnummer das aktuellen Pakets
     */

    unsigned int getPackageNum();
    
    /**
     *  Holt die Position des aktuellen Pakets im ursprünglichen Datensatz.
     *  \param vecLayout Aufteilung des ursprünglichen Datenstroms die aus den Paketinformationen
     *  dekodiert wurden.
     *  \param vecLayoutlen Länge von @a vecLayout.
     */

    unsigned int getPackagePos(char * vecLayout, size_t vecLayoutlen);

    /**
     *  Gibt Auskunft über die Aktualität eines Pakets.
     *  \return -1 falls veraltet, sonst aktuell.
     */
     int getTimestampStatus();

private:
    unsigned int myDataLength;
    int64_t myTimestamp;
	//unsigned int TIME_THRESHOLD=5;
    char * myPackage;
    unsigned int myPackagelen;
    int myTimestampStatus;

    /*
        Number of currently processed package.
    */
    unsigned int myPackageNum;
    /*
        Position of package in original data stream.
    */
    unsigned int myPackagePos; 	//### =0
    unsigned int myDataPos; 	//### =8
    void checkTimestamp();
    void decodeHeader();
};

#endif