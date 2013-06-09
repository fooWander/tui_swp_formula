class Data
{
public:
    Data(int value, unsigned int datatype, unsigned int position);
    //~Data();
    
    int getValue();
    unsigned int getDatatype();
    unsigned int getPosition();

private:
    int myValue;
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