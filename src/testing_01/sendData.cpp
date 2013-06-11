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
    while(true) {
        sendPackage(HOST_MABXII, MSG_INFO_REQUEST);
        if(receivePackage(HOST_MABXII, DATA_PACKAGE_INFO)) {
            // TODO: process/check package information??
            break;
        }
    }

    while(true) {
        sendPackage(HOST_VSERVER, MSG_READY);
        if(receivePackage(HOST_VSERVER, DATA_ACK_VSERVER)) {
            // TODO: process/check acknowledgement??
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
}

void receiveData()
{
	receivePackage(HOST_MABXII, DATA_PACKAGE)
}

void processData()
{
	// Is there anything to decode?
	Decoder dec;
	unsigned int packageSum = dec.getPackageSum();

	Encoder enc;

	for (int i = 0; i < packageSum; ++i)
	{
		/* code */
	}

}

int main(int argc, char const *argv[])
{
    initalize();

    while (true) {
        receiveData();
        processData();
        sendData();
    }
}