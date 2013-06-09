class Encoding
{
public:
    Encoding(arguments);
    ~Encoding();

    // Don't know whether this makes sense
    
};

class Encoder : public Encoding
{
public:
    /* Constructor creates an Encoder object from data stored in buffer.
    According to vecLayout and vecDatatypes the data gets divided into 
    different packages and compressed. The result is stored in myPackages
    and the layout of myPackages in myPackagePos.
    */
    Encoder(char *buffer[], char *vecLayout[], char *vecDatatypes[]);
    ~Encoder();
    /* Return a 
    */
    char *getPackage(packageNumber);
    unsigned int getPackageSize(packageNumber);
    unsigned int getPackageSum();

private:
    void createHeader();
    void splitData();
    void compressData();
    char myPackages[];
    unsigned int myPackagePos[];
    unsigned int myPackageSum;
};

class Decoder : public Encoding
{
public:
    Decoder(char *buffer[], char *vecLayout[], char *vecDatatypes[], char *vecComma[]);
    ~Decoder();
    Data getNextData();
    unsigned int getPackageNum();
    unsigned int getTimestamp();
private:
    unsigned int myDataLength;
    unsigned int myTimestamp;
    unsigned int myPackageNum;
        
};