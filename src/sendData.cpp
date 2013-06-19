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


void sendPackage(const Location remote, const void * msg)
{
    UDPSocket sock;
    int msgSize = strlen(msg);
    sock.sendTo(msg, msgSize, remote.getAddress(), remote.getPort());
}

void receivePackage(const Location remote, void * buffer)
{
    UDPSocket sock;
    int recvMsgSize;

    // TODO: recvFrom() needs to set flag MSG_DONTWAIT to prevent blocking
    recvMsgSize = sock.recvFrom(buffer, PACKAGESIZE_MAX, 
                                remote.getAddress(), remote.getPort());
}

void initalize()
{

    /*
        TODO: do-while-loops are probably better
    */

    while(true) {
        sendPackage(HOST_VSERVER, MSG_READY);
        if(receivePackage(HOST_VSERVER, DATA_ACK_VSERVER)) {
            // TODO: process/check acknowledgement??
            break;
        }        
    }

    while(true) {
        sendPackage(HOST_MABXII, MSG_INFO_REQUEST);
        if(receivePackage(HOST_MABXII, DATA_PACKAGE_INFO)) {
            // TODO: process/check package information??
            break;
        }
    }

    while(true) {
        sendPackage(HOST_VSERVER, DATA_PACKAGE_INFO);
        if(receivePackage(HOST_VSERVER, DATA_ACK_VSERVER)) {
            // TODO: process/check acknowledgement??
            break;
        }      
    }

    Decoder dec(DATA_PACKAGE_INFO);
}

void receiveData()
{
    receivePackage(HOST_MABXII, DATA_PACKAGE);
}

void sendData(Encoder enc) {
    int packageSum = enc.getPackageSum();
    for (int i = 0; i < packageSum; ++i) {
        sendPackage(HOST_VSERVER,enc.getPackage(i));
    }
}

Encoder  processData()
{
    Encoder enc(DATA_PACKAGE, VEC_LAYOUT, VEC_DATATYPES);
    return enc;
}

int main(int argc, char const *argv[])
{
    initalize();

    while (true) {
        receiveData();
        Encoder enc = processData();
        sendData(enc);
    }
}