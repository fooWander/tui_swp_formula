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
#include "common.h"
#include <string>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "unistd.h"

//extern char VEC_LAYOUT[];
//#include "cstring.h"

int LOCALPORT = EMBPC_PORT;

Location HOST_EMBPC(EMBPC_IP,EMBPC_PORT);
Location HOST_EMBPC_INFO(EMBPC_IP, EMBPC_INFO_PORT);
Location HOST_MABXII(MABXII_IP,MABXII_PORT);
Location HOST_MABXII_INFO(MABXII_IP,MABXII_INFO_PORT);
Location HOST_VSERVER(VSERVER_IP,VSERVER_PORT);
Location HOST_VSERVER_INFO(VSERVER_IP,VSERVER_INFO_PORT);


//const int PACKAGE_SIZE_MAX = 100;

char DATA_PACKAGE[PACKAGE_SIZE_MAX];
int DATA_PACKAGE_SIZE = PACKAGE_SIZE_MAX;
char DATA_PACKAGE_INFO[PACKAGE_SIZE_MAX];
int DATA_PACKAGE_INFO_SIZE = PACKAGE_SIZE_MAX;
char DATA_SEND[PACKAGE_SIZE_MAX];
int DATA_SEND_SIZE = PACKAGE_SIZE_MAX;

/**
 *  Sendet ein Paket an einen bestimmten Teilnehmer.
 *  \param remote Teilnehmer an den die Nachricht geschickt werden soll.
 *  \param msg Nachricht die übertragen werden soll.
 *  \param msgSize Länge der Nachricht @a msg.
 */

void sendPackage(Location remote, char * msg, int msgSize)
{
    UDPSocket sock;
    std::string remoteAddress = remote.getAddress();
    unsigned short remotePort = remote.getPort();
    sock.sendTo(msg, msgSize, remoteAddress, remotePort);
}

int receivePackage(Location remote, void * buffer, int bufferLen)
{
    UDPSocket sock(remote.getPort());
    int recvMsgSize;
    string sourceAddress;
    unsigned short sourcePort;
    //http://www.beej.us/guide/bgnet/output/html/multipage/pollman.html 
    //fuer Polling, gez.Tino)
    // TODO: recvFrom() needs to set flag MSG_DONTWAIT to prevent blocking
    std::cout << "receiving..." << std::endl;
    recvMsgSize = sock.recvFrom(buffer, bufferLen, 
                                sourceAddress, sourcePort);
    std::cout << "received something..." << std::endl;
    return recvMsgSize;
}

void initialize()
{

    /*
        TODO: do-while-loops are probably better
    */
    
    while(true) {
        try
        {
            std::cout << sizeof(DATA_PACKAGE_INFO) << std::endl;
            DATA_PACKAGE_INFO_SIZE = receivePackage(HOST_VSERVER_INFO, DATA_PACKAGE_INFO, PACKAGE_SIZE_MAX);
            for (int i = 0; i < DATA_PACKAGE_INFO_SIZE; ++i)
            {
                std::cout << DATA_PACKAGE_INFO[i] << " ";
            }
            std::cout << std::endl;
            std::cout << "received something" << std::endl;
            std::cout << "length: " << DATA_PACKAGE_INFO_SIZE << std::endl;
            break;
        }
        catch(SocketException ex)
        {
            std::cout << "SocketException thrown." << std::endl;
            continue;
        }       
    }
    std::cout << "Decoding..." << std::endl;
    Decoder dec(DATA_PACKAGE_INFO,DATA_PACKAGE_INFO_SIZE);
}

int receiveData()
{
    int recv = receivePackage(HOST_MABXII, DATA_PACKAGE, PACKAGE_SIZE_MAX);
    return recv;
}

void sendData(Encoder enc) {
    int packageSum = enc.getPackageSum();
    for (int i = 0; i < packageSum; ++i) {
        int size = enc.getPackage(DATA_SEND,sizeof(DATA_SEND),i);
        //std::cout << std::endl;
        //std::cout << "======START_PACKAGE " << i << "=======" << std::endl;
        /*
        for (int j = 0; j < size; ++j)
        {
            if (j % 25 == 0)
            {
                //std::cout << std::endl;
            }
            std::cout << DATA_SEND[j];
        }
        std::cout << std::endl;
        std::cout << "========END_PACKAGE=========" << std::endl;
        std::cout << std::endl << std::endl << std::endl << std::endl; 
        */
        sendPackage(HOST_VSERVER,DATA_SEND,size);
        usleep(250000);
    }
}

Encoder  processData()
{
    Encoder enc(DATA_PACKAGE, 802, VEC_LAYOUT, 10,VEC_DATATYPES, 100);
    return enc;
}

int main(int argc, char const *argv[])
{
    std::cout << "Generating test data..." << std::endl;

    for (int i = 0; i < 20; ++i)
    {
        if (i % 2 == 0)
        {
            DATA_PACKAGE[i] = 80;
        } else {
            DATA_PACKAGE[i] = 80;
        }
    }
    for (int i = 20; i < 802; ++i)
    {
        DATA_PACKAGE[i] = rand() % 100;
        //std::cout << "Value " << i << ": " << DATA_PACKAGE[i] << std::endl;
    }
    while (true) {
        std::cout << "Initializing..." << std::endl;
        initialize();
        int i = 0;
        while (true) {
            try
            {
                std::cout << "receiving data..." << std::endl;
                std::cout << DATA_PACKAGE_SIZE << std::endl;
                DATA_PACKAGE_SIZE = receiveData();
                std::cout << DATA_PACKAGE_SIZE << std::endl;
            }
            catch(SocketException ex)
            {
                std::cout << "SocketException thrown." << std::endl;
                break;
            }
            
            Encoder enc = processData();
            std::cout << "Sending data... " << i << std::endl;
            i++;
            sendData(enc);
        }
        
    }
    return(-1);
}
