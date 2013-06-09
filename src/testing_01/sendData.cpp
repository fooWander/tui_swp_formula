int main(int argc, char const *argv[])
{
    unsigned short localPort = atoi(argv[1]);

    unsigned int maxBufferSize = 64; // Maximal size of an UDP-package
    UDPSocket sock(localPort);                
    char buffer[maxBufferSize];
    int recvMsgSize;                  // Size of received message
    string sourceAddress;             // Address of datagram source
    unsigned short sourcePort;        // Port of datagram source
    for (;;) {  // Run forever
        // Block until receive message from a client
        recvMsgSize = sock.recvFrom(buffer, maxBufferSize, sourceAddress, 
                                    sourcePort);
    }
    buffer[recvMsgSize] = '\0';     // terminate string after received data

    Decoder dec;
    Data package;
    package = dec.decode(*buffer);

    Encoder enc;
    enc.encode(*package);   // encode data (compress, add timestamp and ID, etc.)

    UDPSocket sock2;

    for (int i = 0; i < packageNum; ++i)
    {
        //send each package to vServer
        sock2.sendTo(enc.getData(i), sizeof(enc.getData(i)), servAddress, servPort);
    }

    return 0;
}