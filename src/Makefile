#
#   A wrapper for C++ sockets on Unix and Windows
#   Copyright (C) 2002
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -g -Wno-long-long -Wno-sign-compare 

ifeq ($(shell uname),SunOS)
  LIBS = -lsocket -lnsl
endif

all: TCPEchoClient TCPEchoServer UDPEchoClient UDPEchoServer TCPEchoServer-Thread \
BroadcastSender BroadcastReceiver MulticastSender MulticastReceiver

embpc: embpc.cpp ./classes/PracticalSocket.cpp ./classes/PracticalSocket.h ./classes/Encoding.cpp ./classes/Encoding.h ./classes/Data.cpp ./classes/Data.h ./classes/Location.cpp ./classes/Location.h
	$(CXX) $(CXXFLAGS) -o ../bin/embpc embpc.cpp ./classes/PracticalSocket.cpp ./classes/PracticalSocket.h 
						./classes/Encoding.cpp ./classes/Encoding.h ./classes/Data.cpp ./classes/Data.h 
						./classes/Location.cpp ./classes/Location.h
vserver: vserver.cpp ./classes/PracticalSocket.cpp ./classes/PracticalSocket.h ./classes/Encoding.cpp ./classes/Encoding.h ./classes/Data.cpp ./classes/Data.h ./classes/Location.cpp ./classes/Location.h ./classes/Insert.cpp ./classes/DBPacketInsert.cpp ./classes/DatatypeDaemon.cpp
	$(CXX) $(CXXFLAGS) -I/usr/include/cppconn -o ../bin/vserver vserver.cpp ./classes/PracticalSocket.cpp ./classes/PracticalSocket.h ./classes/Encoding.cpp ./classes/Encoding.h ./classes/Data.cpp ./classes/Data.h ./classes/Location.cpp ./classes/Location.h  ./classes/dbData.cpp ./classes/Insert.cpp ./classes/DBPacketInsert.cpp ./classes/DatatypeDaemon.cpp -lmysqlcppconn

clean:
	$(RM) TCPEchoClient TCPEchoServer UDPEchoClient UDPEchoServer TCPEchoServer-Thread \
        BroadcastSender BroadcastReceiver MulticastSender MulticastReceiver
