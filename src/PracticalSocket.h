/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __PRACTICALSOCKET_INCLUDED__
#define __PRACTICALSOCKET_INCLUDED__

#include <string>            // For string
#include <exception>         // For exception class
#include "common.h"
using namespace std;

/**
 *   Zeigt ein Problem mit der Ausf\"uhrung eines Socketaufrufs an.
 */
class SocketException : public exception {
public:
    /**
     *   Erzeugt eine "SocketException" mit einem erkl\"arenden Hinweistext.
     *   @param message Nachricht die den Fehlern beschreibt
     *   @param incSysMsg true falls eine Systemnachricht (von strerror(errno))
     *   sollte zu der f\"ur den User bereitgestellten Nachricht hinzugef\"ugt werden.
     */
    SocketException(const string &message, bool inclSysMsg = false) throw();

    /**
     *   Nur bereitgestellt um zu gew\"ahrleisten, dass keine Exceptions zur\"uckgeworfen / zur\"uckgegeben 
     *   werden.
     */
    ~SocketException() throw();

    /**
     *   Holt die Exception-Nachricht.
     *   @return Exception-Nachricht.
     */
    const char *what() const throw();

private:
    string userMessage;  // Exception message
};

/**
 *   Basisklasse, welche den Endpunkt der grundlegenden Kommunikation darstellt.
 */
class Socket {
public:
    /**
     *   Schließt und dealloziert diesen Socket.
     */
    ~Socket();

    /**
     *   Holt die lokale Adresse.
     *   @return local Adresse des Sockets.
     *   @exception Wirft SocketException falls das Holen fehlschl\"agt.
     */
    string getLocalAddress() throw(SocketException);

    /**
     *   Holt den lokalen Port.
     *   @return Lokalen Port des Sockets.
     *   @exception SocketException wird geworfen falls das Holen fehlschl\"agt.
     */
    unsigned short getLocalPort() throw(SocketException);

    /**
     *   Setzt den lokalen Port zu einem gew\"ahlten Port und die lokale Adresse zu einer beliebigen 
     *   Schnittstelle.
     *   @param localPort Lokaler Port
     *   @exception SocketException wird geworfen wenn das Setzen des lokalen Ports fehlschl\"agt.
     */
    void setLocalPort(unsigned short localPort) throw(SocketException);

    /**
     *   Setzt den lokalen Port und die lokale Adresse.
     *   Wenn kein Port angegeben wird, wird ein zuf\"alliger gew\"ahlt.
     *   @param localAddress Lokale Adresse.
     *   @param localPort Lokaler Port.
     *   @exception SocketException wird geworfen falls das Setzen des lokalen Ports oder der Adresse fehlschl\"agt.
     */
    void setLocalAddressAndPort(const string &localAddress, 
        unsigned short localPort = 0) throw(SocketException);

    /**
     *   Ermittelt den spezifizierten Service f\"ur das angegebene Protokoll.
     *   @param service Zu ermittelnde Service (e.g., "http").
     *   @param protocol Protokoll des zu ermittelnden Service. Standard ist "tcp".
     */
    static unsigned short resolveService(const string &service,
                                                                             const string &protocol = "tcp");

private:
    // Prevent the user from trying to use value semantics on this object
    Socket(const Socket &sock);
    void operator=(const Socket &sock);

protected:
    int sockDesc;              // Socket descriptor
    Socket(int type, int protocol) throw(SocketException);
    Socket(int sockDesc);
};

/**
 *   Socket der in der Lage ist sich zu verbinden, zu senden und zu empfangen.
 */
class CommunicatingSocket : public Socket {
public:
    /**
     *   Baut eine Verbindung \"uber Sockets zu einem bestimmten Teilnehmer.
     *   @param foreignAddress Adresse des Teilnehmers (IP Adresse oder Name).
     *   @param foreignPort Portnummer des Teilnehmers.
     *   @exception SocketException wird geworfen wenn die Verbindung fehlschl\"agt.
     */

    void connect(const string &foreignAddress, unsigned short foreignPort)
        throw(SocketException);

    /**
     *   Schreibt den \"ubergebenen Buffer in den Socket.  Vor send() muss collect() aufgerufen werden.
     *   @param buffer Speicher in den geschrieben werden soll.
     *   @param bufferLen Anzahl der Bytes die geschrieben werden sollen.
     *   @exception SocketException wird geworfen wenn keine Daten gesendet werden k\"onnen.
     */
    void send(const void *buffer, int bufferLen) throw(SocketException);

    /**
     *   Ließt eine Nachricht in den \"ubergebenen Buffer ein.
     *   connect() muss vorher aufgerufen werden.
     *   @param buffer Speicher in den die Nachricht geschrieben werden soll.
     *   @param bufferLen Maximale Anzahl an Bytes die empfangen werden sollen.
     *   @return Gibt die Anzahl der gelesenen Bytes zur\"uck. 0 wenn EOF und -1 im Fehlerfall.
     *   @exception SocketException wird geworfen falls keine Daten emfpangen werden k\"onnen.
     */
    int recv(void *buffer, int bufferLen) throw(SocketException);

    /**
     *   Holt die Zieladresse.
     *   @return Zieladresse.
     *   @exception SocketException wird geworfen falls das Holen fehlschl\"agt.
     */
    string getForeignAddress() throw(SocketException);

    /**
     *   Holt den Zielport.  Call connect() before calling recv()
     *   @return Zielportnummer.
     *   @exception SocketException wird geworfen falls das Holen fehlschl\"agt.
     */
    unsigned short getForeignPort() throw(SocketException);

protected:
    CommunicatingSocket(int type, int protocol) throw(SocketException);
    CommunicatingSocket(int newConnSD);
};

/**
 *   TCP-Socket f\"ur die Kommunikation mit anderen TCP-Sockets.
 */
class TCPSocket : public CommunicatingSocket {
public:
    /**
     *   Erzeugt einen TCP-Socket mit keiner Verbindung.
     *   @exception SocketException wird geworfen falls die Erzeugung fehlschl\"agt.
     */
    TCPSocket() throw(SocketException);

    /**
     *   Erzeugt einen TCP-Socket mit einer Verbindung zu einer bestimmten Adresse und einem bestimmten Port.
     *   @param foreignAddress foreign address (IP address or name)
     *   @param foreignPort foreign port
     *   @exception SocketException wird geworfen falls die Erzeugung fehlschl\"agt.
     */
    TCPSocket(const string &foreignAddress, unsigned short foreignPort) 
            throw(SocketException);

private:
    // Access for TCPServerSocket::accept() connection creation
    friend class TCPServerSocket;
    TCPSocket(int newConnSD);
};

/**
 *   TCP-Socket Klasse f\"ur Server.
 */
class TCPServerSocket : public Socket {
public:
    /**
     *   Erzeugt einen TCP-Socket f\"ur die Nutzung mit dem Server, welcher zu 
     *   einer beliebigen Schnittstelle auf dem vereinbarten Port Verbindungen zul\"asst.
     *   @param localPort Lokaler Port des Server.
     *   @param queueLen Maximale Warteschlangenl\"ange f\"ur ausstehende Verbindungsanfragen. (default 5)
     *   @exception SocketException wird geworfen falls es nicht m\"oglich ist einen Socket zu erzeugen.
     */
    TCPServerSocket(unsigned short localPort, int queueLen = 5) 
            throw(SocketException);

    /**
     *   Erzeugt einen TCP-Socket f\"ur die Nutzung mit dem Server, welcher zu 
     *   einer beliebigen Schnittstelle zu einer vereinbarten Adresse Verbindungen zul\"asst.
     *   @param localAddress Lokales Interface (Adresse) des Server-Sockets.
     *   @param localPort Lokaler Port des Servers.
     *   @param queueLen Maximale Warteschlangenl\"ange f\"ur ausstehende Verbindungsanfragen. (default 5)
     *   @exception SocketException wird geworfen falls es nicht m\"oglich ist einen Socket zu erzeugen.
     */
    TCPServerSocket(const string &localAddress, unsigned short localPort,
            int queueLen = 5) throw(SocketException);

    /**
     *   Blockiert solange bis eine neue Verbindung auf diesem Socket etabliert wurde oder ein Fehler auftritt.
     *   @return Neue Socketverbindung
     *   @exception SocketException wird geworfen falls der Versuch eine neue Verbindung zu erzeugen fehlschl\"agt.
     */

    TCPSocket *accept() throw(SocketException);

private:
    void setListen(int queueLen) throw(SocketException);
};

/**
    *   UDP-Socket Klasse
    */
class UDPSocket : public CommunicatingSocket {
public:
    /**
     *   Erzeugt einen UDP-Socket.
     *   @exception SocketException wird geworfen falls die Erzeugung fehlschl\"agt.
     */
    UDPSocket() throw(SocketException);

    /**
     *   Erzeugt einen UDP-Socket mit einem spezifischen Port.
     *   @param localPort Lokaler Port
     *   @exception SocketException wird geworfen falls die Erzeugung fehlschl\"agt.
     */
    UDPSocket(unsigned short localPort) throw(SocketException);

    /**
     *   Erzeugt einen UDP-Socket mit einer spezifischen Adresse und einem gegebenen Port.
     *   @param localAddress Lokale Adresse.
     *   @param localPort Lokaler Port.
     *   @exception SocketException wird geworfen falls die Erzeugung fehlschl\"agt.
     */
    UDPSocket(const string &localAddress, unsigned short localPort) 
            throw(SocketException);

    /**
     *   Setze Adresse und Port zur\"uck.
     *   @return true falls kein Fehler auftrat.
     *   @exception SocketException wird geworfen falls eine Trennung fehlschl\"agt.
     */
    void disconnect() throw(SocketException);

    /**
     *   Sendet einen Buffer als UDP-Datagramm an eine bestimmte Adresse und Portnummer.
     *   @param buffer Buffer der gesendet werden soll.
     *   @param bufferLen Anzahl der Bytes die geschrieben werden sollen.
     *   @param foreignAddress Adresse an die versendet werden soll.
     *   @param foreignPort Portnummer an die versendet werden soll.
     *   @return true falls Versandt geklappt hat.
     *   @exception SocketException wird geworfen falls das Senden fehlschl\"agt.
     */
    void sendTo(const void *buffer, int bufferLen, const string &foreignAddress,
                        unsigned short foreignPort) throw(SocketException);

    /**
     *   Empf\"angt eine Nachricht an einem UDP-Socket.
     *   @param buffer Buffer in den gelesen werden soll.
     *   @param bufferLen Maximale Anzahl an Bytes die empfangen werden sollen.
     *   @param sourceAddress Adresse von der die Nachricht stammt.
     *   @param sourcePort Portnummer des Senders.
     *   @return Anzahl der Bytes die empfangen wurden, -1 falls ein Fehler auftrat.
     *   @exception SocketException wird geworfen falls das Empfangen fehlschl\"agt.
     */
    int recvFrom(void *buffer, int bufferLen, string &sourceAddress, 
                             unsigned short &sourcePort) throw(SocketException);

    /**
     *   Setzt Multicast TTL.
     *   @param multicastTTL Multicast TTL.
     *   @exception SocketException wird geworfen falls das Setzen fehlschl\"agt.
     */
    void setMulticastTTL(unsigned char multicastTTL) throw(SocketException);

    /**
     *   Tritt der angegebenen Multicast-Gruppe bei.
     *   @param multicastGroup Adresse der Mutlicast-Gruppe.
     *   @exception SocketException wird geworfen falls das Beitreten fehlschl\"agt.
     */
    void joinGroup(const string &multicastGroup) throw(SocketException);

    /**
     *   Verlasse die angegebene Multicast-Gruppe.
     *   @param multicastGroup Zu verlassende Multicast-Gruppe.
     *   @exception SocketException wird geworfen falls das Verlassen fehlschl\"agt.
     */
    void leaveGroup(const string &multicastGroup) throw(SocketException);

private:
    void setBroadcast();
    void setTimeout();
};

#endif
