	

    #include <iostream>
    #include <math.h>
    #include "PracticalSocket.h"
    #include <string>
    #include <cstdlib>
     
    char myPackages[65535];
    int myPackagePointer = 0;
    int myPackageNum = 1212696648;
    int myPackagePos[10];
    int myPackageSum = 0;
    char VEC_DATATYPES[1604];
    char VEC_LAYOUT[802];
    char VEC_COMMA[802];
    int VEC_DATATYPES_SIZE = 0;
    int VEC_LAYOUT_SIZE = 0;
    int VEC_COMMA_SIZE = 0;
     
    unsigned short joinUnsigShort(unsigned char a,unsigned char b)
    {
        return (a<<8) + b;
    }
     
    void decodePackageInfo(char * buffer, const int bufferlen) {
        VEC_DATATYPES_SIZE = joinUnsigShort(buffer[0],buffer[1]);
        VEC_LAYOUT_SIZE = joinUnsigShort(buffer[2],buffer[3]);
        VEC_COMMA_SIZE = joinUnsigShort(buffer[4],buffer[5]);
     
        int border_0 = 6 + 2*(VEC_DATATYPES_SIZE);
        int border_1 = border_0 + 2*(VEC_LAYOUT_SIZE);
        int border_2 = border_1 + 2*(VEC_COMMA_SIZE);
     
        int j = 0;
        for (int i = 6; i < border_0; i=i+2) {
            VEC_DATATYPES[j] = joinUnsigShort(buffer[i],buffer[i+1]);
            std::cout << "VEC_DATATYPES" << std::endl;
            std::cout << VEC_DATATYPES[j] << std::endl;
            j++;
        }
     
        j = 0;
        for (int i = border_0 ;i < border_1; i=i+2) {
            VEC_LAYOUT[j] = joinUnsigShort(buffer[i],buffer[i+1]);
            std::cout << "VEC_LAYOUT" << std::endl;
            std::cout << VEC_LAYOUT[j] << std::endl;
            j++;
        }
     
        j = 0;
        for (int i= border_1;i < border_2; i=i+2) {
            VEC_COMMA[j] = joinUnsigShort(buffer[i],buffer[i+1]);
            std::cout << "VEC_COMMA" << std::endl;
            std::cout << VEC_COMMA[j] << std::endl;
            j++;
        }
    }
     
    void createHeader()
    {
        //create ID
        myPackages[myPackagePointer+3] = myPackageNum & 0xff;
        myPackages[myPackagePointer+2] = (myPackageNum >> 8) & 0xff;
        myPackages[myPackagePointer+1] = (myPackageNum >> 16) & 0xff;
        myPackages[myPackagePointer] = (myPackageNum >> 24) & 0xff;
        myPackagePointer += 4;
        //myPackageNum++;
    }
     
    int getPackage(char * package, unsigned short packageNumber)
    {
        int len;
        if (packageNumber == 1) {
            len = myPackagePos[packageNumber] - 1;
            //std::cout << myPackagePos[packageNumber] - 1 << std::endl;
        } else {
            len = myPackagePos[packageNumber] - myPackagePos[packageNumber-1];
            //std::cout << myPackagePos[packageNumber] << std::endl;
            //std::cout << myPackagePos[packageNumber - 1] << std::endl;
        }
        for (int i = 0; i < len; ++i) {
            package[i] = myPackages[myPackagePos[packageNumber - 1] + i];
            //std::cout << myPackagePos[packageNumber - 1 + i] << std::endl;
        }
        return len;
    }
     
    void splitData(const char *buffer, const int bufferlen, const char *vecLayout, const int vecLayoutlen)
    {
        myPackages[0] = 0;
        int pointer = 1;
        int splitPos;
        for (int i = 0; i < vecLayoutlen; i=i+2) {
            createHeader();
            splitPos = joinUnsigShort(vecLayout[i],vecLayout[i+1]);
            for (int j = 0; j < splitPos; ++j) {
                myPackages[myPackagePointer] = buffer[j];
                myPackagePointer++;
            }
     
            if (pointer == 0) {
                myPackagePos[pointer] = splitPos + 4;
            } else if (pointer != myPackageSum) {
                myPackagePos[pointer] = myPackagePos[pointer-1] + splitPos + 4;
            }
     
            pointer++;
        }
     
    }
     
    int main(int argc, char const *argv[])
    {
        char buffer[65535];
        int bufferlen = sizeof(buffer);
     
     
     	std::cout << "Creating socket..." << std::endl;
        UDPSocket sock(5000);                    // Size of received message
        string sourceAddress;             // Address of datagram source
        unsigned short sourcePort;
        int recvMsgSize;        // Port of datagram source
	std::cout << "Receiving message..." << std::endl;
        recvMsgSize = sock.recvFrom(buffer, bufferlen, sourceAddress,
                                          sourcePort);
     
        //char buffer[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        //int bufferlen = sizeof(buffer);
        char vecLayout[] = {0,5,0,3,0,2,0,100};
        std::cout << vecLayout[0] << std::endl;
        int vecLayoutlen = sizeof(vecLayout);
        myPackageSum = vecLayoutlen/2;
        //createHeader();
        std::cout << "Erzeuge Paket..." << std::endl;
        splitData(buffer,recvMsgSize,vecLayout,vecLayoutlen);
     
        std::cout << "=======================Paket======================" << std::endl;
     
        for (int i = 0; i < 100; ++i) {
            if (i < 10) {
                std::cout << 0;
            }
            std::cout << i << ":" << myPackages[i] << std::endl;
        }
     
        std::cout << "=================Paketpositionen==================" << std::endl;
     
        for (int i = 0; i < myPackageSum; ++i) {
            std::cout << "Paket " << i+1 << ": " << myPackagePos[i] << std::endl;
        }
     
        char package[65535];
     
        std::cout << "==================================================" << std::endl;
     
        std::cout << "Hole Paket Nummer 2..." << std::endl;
        int len = getPackage(package,2);
        package[len] = '\0';
     
        for (int i = 0; i < len; ++i) {
            //std::cout << sizeof(package) << std::endl;
            std::cout << package[i] << std::endl;
        }
     
        std::cout << "Pakete insgesamt: " << myPackageSum << std::endl;
     
        std::cout << "=================Infopaket==================" << std::endl;
     
        char buffer_packageinfo[] = {0,6, 0,4, 0,3, 0,1,0,2,0,3,0,4,0,5,0,6, 0,97,0,98,0,99,0,100, 0,101,0,102,0,103};
        int buffer_packageinfolen = sizeof(buffer_packageinfo);
        decodePackageInfo(buffer_packageinfo,buffer_packageinfolen);
        for (int i = 0; i < 10; ++i)
        {
            std::cout << (char)i << std::endl;
        }
     
        for (int i = 0; i < 4; ++i)
        {
            std::cout << myPackages[i] << std::endl;
        }
     
        std::cout << (myPackages[3] & 0xff) + ((myPackages[2] << 8) & 0xff00)
                                            + ((myPackages[1] << 16) & 0xff0000)
                                            + ((myPackages[0] << 24) & 0xff000000);
        /*myPackages[myPackagePointer+2] = (PACKAGE_COUNTER >> 8) & 0xff;
        myPackages[myPackagePointer+1] = (PACKAGE_COUNTER >> 16) & 0xff;
        myPackages[myPackagePointer] = (PACKAGE_COUNTER >> 24) & 0xff;
        myPackagePointer += 4;*/
     
        //std::cout << exp10(2);
    }


