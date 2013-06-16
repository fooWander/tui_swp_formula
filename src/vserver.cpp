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

//#include "PracticalSocket.h"
//#include "common.h"
//#include "vserver.h"

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
char MSG_ACK[] = {1};

int LOCALPORT = 5001;

Location HOST_EMBPC("127.0.0.1",(short)5000);
Location HOST_MABXII("10.42.0.42",(short)5002);
Location HOST_VSERVER("87.106.17.165",(short)5001);

const int PACKAGESIZE_MAX = 1000;
const int ACK_SIZE_MAX = 20;

char DATA_ACK[ACK_SIZE_MAX];
char DATA_ACK_SIZE;
char DATA_PACKAGE[PACKAGESIZE_MAX];
int DATA_PACKAGE_SIZE = PACKAGESIZE_MAX;
char DATA_PACKAGE_INFO[PACKAGESIZE_MAX];
int DATA_PACKAGE_INFO_SIZE;
char VEC_COMMAS[PACKAGESIZE_MAX];
int VEC_COMMAS_SIZE;

//char DATA_SEND[1000];


void sendPackage(Location remote, char * msg)
{
    UDPSocket sock;
    int msgSize = strlen(msg);
    std::string remoteAddress = remote.getAddress();
    unsigned short remotePort = remote.getPort();
    sock.sendTo(msg, msgSize, remoteAddress, remotePort);
}

int receivePackage(Location remote, void * buffer, int buffersize)
{
    UDPSocket sock(LOCALPORT);
    int recvMsgSize;
    string sourceAddress;
    unsigned short sourcePort;
    //http://www.beej.us/guide/bgnet/output/html/multipage/pollman.html 
    //fuer Polling, gez.Tino
    // TODO: recvFrom() needs to set flag MSG_DONTWAIT to prevent blocking
    std::cout << "called recvFrom" << std::endl;
    recvMsgSize = sock.recvFrom(buffer, buffersize, 
                                sourceAddress, sourcePort);
    std::cout << "recvMsgsize: " << recvMsgSize  << std::endl;
    return recvMsgSize;
}
void initalize()
{

    /*
        TODO: do-while-loops are probably better
    */

    while(true) {
        //sendPackage(HOST_VSERVER, MSG_READY);
        //std::cout << "Receiving ready..." << std::endl;
        std::cout << "Receiving MSG_READY..." << std::endl;
        DATA_ACK_SIZE = receivePackage(HOST_EMBPC, DATA_ACK, ACK_SIZE_MAX);
        std::cout << DATA_ACK_SIZE << std::endl;
        bool equal = true;
        for (int i = 0; i < 3; ++i) {
            if(MSG_READY[i] != DATA_ACK[i]) {
                equal = false;
            }
        }
        if (equal == true) {
            std::cout << "Message correctly received." << std::endl;
            break;
        }

        std::cout << "Wrong Message received:";
        for (int i = 0; i < 3; ++i) {
                //std::cout << MSG_READY[i];
                std::cout << DATA_ACK[i];
        }
        std::cout <<  "trying again..." << std::endl;        
    }

    while(true) {
        std::cout << "Sending ACK..." << std::endl;
        sendPackage(HOST_EMBPC, MSG_ACK);
        std::cout << "Receiving package info..." << std::endl;
        if(receivePackage(HOST_EMBPC, DATA_PACKAGE_INFO, 1)) {
            std::cout << "Packageinfo received..." << std::cout;
            break;
        }
        std::cout << "trying again..." << std::endl;
    }
    std::cout << "sending ACK..." << std::endl;
    sendPackage(HOST_EMBPC, MSG_ACK);
    std::cout << "Decoding..." << std::endl;
    //Decoder dec(DATA_PACKAGE_INFO,100);
}

int receiveData()
{
    return receivePackage(HOST_EMBPC, DATA_PACKAGE, DATA_PACKAGE_SIZE);
}

Decoder processData()
{
    std::cout << "VEC_LAYOUT_SIZE: " << VEC_LAYOUT_SIZE << std::endl;
    for (int i = 0; i < VEC_LAYOUT_SIZE; ++i)
    {
        std::cout << VEC_LAYOUT[i];
    }
    std::cout << std::endl;
    Decoder dec(DATA_PACKAGE, DATA_PACKAGE_SIZE, VEC_LAYOUT, VEC_LAYOUT_SIZE, 
                VEC_DATATYPES, VEC_DATATYPES_SIZE, VEC_COMMAS, VEC_COMMAS_SIZE);
    return dec;
}

int main(int argc, char const *argv[])
{
    initalize();
    std::cout << "init done." << std::endl;
    while (true) {
        /*
            TODO: add timeout
        */
        std::cout << "receiving data..." << std::endl;
        DATA_PACKAGE_SIZE = receiveData();
        std::cout << "received data." << std::endl;
        /*
            TODO: add timeout
        */
        //processData();
        for (int i = 0; i < DATA_PACKAGE_SIZE; ++i)
        {
            std::cout << DATA_PACKAGE[i];
        }
        std::cout << std::endl;
        std::cout << "Decoding data... " << std::endl;
        Decoder dec = processData();
        usleep(250000);
        //sendData(enc);
    }
}
