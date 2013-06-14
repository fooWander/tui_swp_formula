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

#include "Location.h"
#include "Data.h"
#include "Encoding.h"
#include "PracticalSocket.h"
#include <string>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "unistd.h"

//extern char VEC_LAYOUT[];
//#include "cstring.h"

char MSG_INFO_REQUEST[] = {96};
char MSG_READY[] ="144"; //={144}

int LOCALPORT = 5000;

Location HOST_EMBPC("10.42.0.55",(short)5000);
Location HOST_MABXII("10.42.0.42",(short)5002);
Location HOST_VSERVER("87.106.17.165",(short)5000);

//const int PACKAGESIZE_MAX = 100;

char DATA_ACK_VSERVER[] = {1}; 
char DATA_PACKAGE[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
char DATA_PACKAGE_INFO[100];

void sendPackage(Location remote, char * msg)
{
    UDPSocket sock;
    int msgSize = strlen(msg);
    std::string remoteAddress = remote.getAddress();
    unsigned short remotePort = remote.getPort();
    sock.sendTo(msg, msgSize, remoteAddress, remotePort);
}

int receivePackage(Location remote, void * buffer)
{
    UDPSocket sock(LOCALPORT);
    int recvMsgSize;
    string sourceAddress;
    unsigned short sourcePort;
    //http://www.beej.us/guide/bgnet/output/html/multipage/pollman.html 
    //fuer Polling, gez.Tino
    // TODO: recvFrom() needs to set flag MSG_DONTWAIT to prevent blocking
    recvMsgSize = sock.recvFrom(buffer, 100, 
                                sourceAddress, sourcePort);
    return recvMsgSize;
}

void initialize()
{

    /*
        TODO: do-while-loops are probably better
    */
    
    while(true) {
        std::cout << "Sending READY..." << std::endl;
        sendPackage(HOST_VSERVER, MSG_READY);
        std::cout << "Receiving ACK..." << std::endl;
        if(receivePackage(HOST_VSERVER, DATA_ACK_VSERVER)) {
            // TODO: process/check acknowledgement??
            break;
        }       
    }

    while(true) {
        std::cout << "Sending READY..." << std::endl;
        sendPackage(HOST_MABXII, MSG_INFO_REQUEST);
        std::cout << "Receiving ACK..." << std::endl;
        if(receivePackage(HOST_MABXII, DATA_PACKAGE_INFO)) {
            // TODO: process/check package information??
            break;
        }
    }

    while(true) {
        std::cout << "Sending READY..." << std::endl;
        sendPackage(HOST_VSERVER, DATA_PACKAGE_INFO);
        std::cout << "Receiving ACK..." << std::endl;
        if(receivePackage(HOST_VSERVER, DATA_ACK_VSERVER)) {
            // TODO: process/check acknowledgement??
            break;
        }      
    }

    Decoder dec(DATA_PACKAGE_INFO,100);
}

int receiveData()
{
    int recv = receivePackage(HOST_MABXII, DATA_PACKAGE);
    return recv;
}

void sendData(Encoder enc) {
    int packageSum = enc.getPackageSum();
    for (int i = 0; i < packageSum; ++i) {
        enc.getPackage(DATA_PACKAGE,i);
        sendPackage(HOST_VSERVER,DATA_PACKAGE);
    }
}

Encoder  processData()
{
    Encoder enc(DATA_PACKAGE, 20, VEC_LAYOUT, 8,VEC_DATATYPES, 100);
    return enc;
}

int main(/*int argc, char const *argv[]*/)
{
    std::cout << "Initializing..." << std::endl;
    //initialize();
    int i = 0;
    while (true) {
        std::cout << "Receiving data..." << std::endl;
        int recv;
        //recv = receiveData();
        std::cout << "Encoding..." << std::endl;
        Encoder enc = processData();
        std::cout << "Sending data... " << i << std::endl;
        i++;
        sendData(enc);
        usleep(250000);
    }
    return(-1);
}
