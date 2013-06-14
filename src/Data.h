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

#ifndef __DATA_H_INCLUDED__
#define __DATA_H_INCLUDED__

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
/*
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
*/

#endif