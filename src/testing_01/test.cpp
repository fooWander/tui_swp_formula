#include <iostream>

char myPackages[65535];
int myPackagesPointer = 0;
int myPackageNum = 1212696648;
int myPackagesPos[10];
int myPackagesSum = 0;

unsigned short joinUnsigShort(unsigned char a,unsigned char b)
{
    return (a<<8) + b;
}

void createHeader()
{
    //create ID
    myPackages[myPackagesPointer+3] = myPackageNum & 0xff;
    myPackages[myPackagesPointer+2] = (myPackageNum >> 8) & 0xff;
    myPackages[myPackagesPointer+1] = (myPackageNum >> 16) & 0xff;
    myPackages[myPackagesPointer] = (myPackageNum >> 24) & 0xff;
    myPackagesPointer += 4;
    //myPackageNum++;
}

int getPackage(char * package, unsigned short packageNumber)
{
    int len;
    if (packageNumber == 1)
    {
        len = myPackagesPos[packageNumber] - 1;
        //std::cout << myPackagesPos[packageNumber] - 1 << std::endl;
    } else {
        len = myPackagesPos[packageNumber] - myPackagesPos[packageNumber-1];
        //std::cout << myPackagesPos[packageNumber] << std::endl;
        //std::cout << myPackagesPos[packageNumber - 1] << std::endl;
    }
    for (int i = 0; i < len; ++i)
    {
        package[i] = myPackages[myPackagesPos[packageNumber - 1] + i];
        //std::cout << myPackagesPos[packageNumber - 1 + i] << std::endl;
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
            myPackages[myPackagesPointer] = buffer[j];
            myPackagesPointer++;
        }

        if (pointer == 0)
        {
            myPackagesPos[pointer] = splitPos + 4;
        } else if (pointer != myPackagesSum) {
            myPackagesPos[pointer] = myPackagesPos[pointer-1] + splitPos + 4;
        }


        pointer++;
    }
 
}

int main(int argc, char const *argv[])
{
    char buffer[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int bufferlen = sizeof(buffer);
    char vecLayout[] = {0,5,0,3,0,2,0,10};
    std::cout << vecLayout[0] << std::endl;
    int vecLayoutlen = sizeof(vecLayout);
    myPackagesSum = vecLayoutlen/2;
    //createHeader();
    splitData(buffer,bufferlen,vecLayout,vecLayoutlen);

    for (int i = 0; i < myPackagesPointer; ++i)
    {
        std::cout << "Wert " << i << ":" << myPackages[i] << std::endl;
    }

    for (int i = 0; i < myPackagesSum; ++i)
    {
        std::cout << "Paketposition: " << myPackagesPos[i] << std::endl;
    }

    char package[65535];

    int len = getPackage(package,2);
    package[len] = '\0';

    for (int i = 0; i < len; ++i)
    {
        //std::cout << sizeof(package) << std::endl;
        std::cout << package[i] << std::endl;
    }
}