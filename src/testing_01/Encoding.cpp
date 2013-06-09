class Encoding
{
public:
    Encoding(arguments);
    ~Encoding();

    
};

class Encoder : public Encoding
{
public:
    Encoder(char *buffer[], char *vecLayout[], char *vecDatatypes[]);
    ~Encoder();

    char *getPackage(packageNumber);
    unsigned int getPackageSize(packageNumber);

private:
    void createHeader();
    void splitData();
    void compressData();
    char packages[];
    unsigned int packagePos[];
};

class Decoder : public Encoding
{
public:
    Decoder(arguments);
    ~Decoder();

        
};