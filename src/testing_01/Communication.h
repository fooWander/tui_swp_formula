class Sender
{
public:
    Sender();
    Sender(Header, Data, Destination);
    ~Sender();

    void addHeader(Header);
    void removeHeader();
    void addData(Data);
    void removeData();
    void setDestination(Destination);
    void resetDestination();
    bool sendPackage();

private:
    Data myData;
    Destination myDestination;
    Header myHeader;
    bool readyToSend;
};

class Receiver
{
public:
    Receiver(Source);
    ~Receiver();

    void setSource(Source);
    Header recvHeader();
    Data recvData();
private:
    Source mySource;
};

class Socket
{
public:
    Socket();
    Socket(unsigned short localPort);
    Socket(unsigned short remoteAddr, unsigned short remotePort);
    ~Socket();

    void setRemoteAddr(unsigned short remoteAddr);
    void setRemotePort(unsigned short remotePort);
    void setLocalPort(unsigned short localPort);
    unsigned short getSocketDescriptor();
    unsigned int * getRemoteAddr();
private:
    unsigned short myRemoteAddr;
    unsigned short myRemotePort;
    unsigned short myLocalPort;
};