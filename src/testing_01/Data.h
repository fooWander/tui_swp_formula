class Data
{
public:
    Data(double value, unsigned int datatype, unsigned int position);
    //~Data();
    
    double getValue();
    unsigned int getDatatype();
    unsigned int getPosition();

private:
    double myValue;
    unsigned int myDatatype;
    unsigned int myPosition;
};

class Message
{
public:
    Message(arguments);
    ~Message();

    void setMessage(char *data, unsigned int bufferSizeData);
    char *getMessageData();
private:
    unsigned int myBufferSizeData;
    char myData[bufferSizeData];
};

class Location
{
public:
    Location(arguments);
    ~Location();

    /* data */
};