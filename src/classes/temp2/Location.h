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

#ifndef __LOCATION_H_INCLUDED__
#define __LOCATION_H_INCLUDED__

#include <string>

/**
 *	Datenstruktur, die Netzwerkdaten bestimmter Teilnehmer speichert.
 */

class Location
{
public:

	/**
     *  Erzeugt einen Teilnehmer.
     *	\param address IP-Adresse des Teilnehmers.
     *	\param port Port-Nummer des Teilnehmers.
     */

    Location(std::string address, short port);
   // ~Location();

    /**
     *  \return Gibt die Adresse zurück.
     */

    std::string getAddress();

    /**
     *  \return Gibt die Portnummer zurück.
     */

    int getPort();

private:
    std::string myAddress; 
    int myPort;
};

#endif