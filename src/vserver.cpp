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
#include "common.h"
#include <string>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "unistd.h"

//extern char VEC_LAYOUT[];
//#include "cstring.h"

int LOCALPORT = VSERVER_PORT;

Location HOST_EMBPC(EMBPC_IP,EMBPC_PORT);
Location HOST_MABXII(MABXII_IP,MABXII_PORT);
Location HOST_VSERVER(VSERVER_IP,VSERVER_PORT);

char DATA_PACKAGE[PACKAGE_SIZE_MAX];
int DATA_PACKAGE_SIZE = PACKAGE_SIZE_MAX;
char DATA_PACKAGE_INFO[PACKAGE_SIZE_MAX];
int DATA_PACKAGE_INFO_SIZE;
char VEC_COMMAS[PACKAGE_SIZE_MAX];
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
    //std::cout << "called recvFrom" << std::endl;
    std::cout << "receiving..." << std::endl;
    //try
    //{
    recvMsgSize = sock.recvFrom(buffer, buffersize, 
                                sourceAddress, sourcePort);
    //}
    //catch(SocketException ex)
    //{
    //    std::cout << "Exception geworfen" << std::endl;
    //}
    std::cout << "recvMsgsize: " << recvMsgSize  << std::endl;
    return recvMsgSize;
}
void initalize()
{

    /*
        TODO: do-while-loops are probably better
    */
    std::cout << "Initializing..." << std::endl;

    if(receivePackage(HOST_EMBPC, DATA_PACKAGE_INFO, PACKAGE_SIZE_MAX)) {
        std::cout << "Packageinfo received..." << std::cout;
    }
    std::cout << "trying again..." << std::endl;
    //bla
    //Decoder dec(DATA_PACKAGE_INFO,100);
}

int receiveData()
{
    int recvMsgSize;
    DATA_PACKAGE_SIZE = PACKAGE_SIZE_MAX;
    recvMsgSize = receivePackage(HOST_EMBPC, DATA_PACKAGE, DATA_PACKAGE_SIZE);
    std::cout << recvMsgSize << std::endl;
    return recvMsgSize;
}

Decoder processData()
{
    //std::cout << "VEC_LAYOUT_SIZE: " << VEC_LAYOUT_SIZE << std::endl;
    /*
    for (int i = 0; i < VEC_LAYOUT_SIZE; ++i)
    {
        std::cout << VEC_LAYOUT[i];
    }
    */
    std::cout << std::endl;
    Decoder dec(DATA_PACKAGE, DATA_PACKAGE_SIZE, VEC_LAYOUT, VEC_LAYOUT_SIZE, 
                VEC_DATATYPES, VEC_DATATYPES_SIZE, VEC_COMMAS, VEC_COMMAS_SIZE);
    return dec;
}

int main(int argc, char const *argv[])
{
    while (true) {
        //initalize();
        std::cout << "init done." << std::endl;

        while (true) {
            try
            {
                DATA_PACKAGE_SIZE = receiveData();
            }
            catch(SocketException ex)
            {
                std::cout << "Exception thrown." << std::endl;
                break;
            }
            if (DATA_PACKAGE_SIZE < 0) {
                break;
            }
            Decoder dec = processData();
            if (dec.getTimestampStatus() < 0) {
                std::cout << "Paket zu alt!" << std::endl;
                continue;
            }
            usleep(250000);
            //sendData(dec);
            std::cout << "Paket verarbeitet!!!!!" << std::endl;
        }
        
    }
}