/**
 * The Locality Sensitive Distributed Hashtable (LSH-DHT) library is
 * part of the SEEKS project and does provide the components of
 * a peer-to-peer pattern matching overlay network.
 * Copyright (C) 2006 Emmanuel Benazera, juban@free.fr
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef LOCATIONTABLE_H
#define LOCATIONTABLE_H

#include "stl_hash.h"
#include "Location.h"

namespace dht
{
   class LocationTable
     {
      private:
	/**
	 * \brief copy-constructor is not implemented.
	 */
	LocationTable(const LocationTable& lt);
	
      public:
	LocationTable();

      private:
	/**
	 * \brief add new location to table.
	 * @param loc location to be added.
	 */
	void addToLocationTable(Location* loc);
	
      public:
	/**
	 * \brief create and add location to table.
	 * @param key identification key to be added,
	 * @param na net address of the location to be added,
	 * @param loc location pointer to be filled with the new location info.
	 * TODO: table cleanup.
	 */
	void addToLocationTable(const DHTKey& key, const NetAddress& na, Location* loc);
	
	/**
	 * \brief - lookup for the key in the hashtable. Replace based on the existing location
	 *          (use up_time in case of a key conflict ?).
	 *        - if nothing is found, create a location object and add it to the table.
	 */
	Location* addOrFindToLocationTable(const DHTKey& key, const NetAddress& na);
	
	/* TODO: find location. */
	//Location* findLocation(const Location& loc);
	Location* findLocation(const DHTKey& dk);
	
	/* TODO: periodic check on dead/useless locations ? */
	
	/* TODO: clean up the dead/unused locations. */
	size_t cleanUpLocations();
	
	/* TODO: max caching size of locations. */
	
	/* TODO: max size of the table, including 'caching' size of unused but known locations. */
	
      private:
	/**
	 * TODO: hashtable of known peers on this system.
	 * TODO: should we add the local virtual nodes to it ? (why not?).
	 */
	hash_map<const DHTKey*, Location*, hash<const DHTKey*>, eqdhtkey> _hlt;
	
	/**
	 * (TODO: table of ranked known peers on this system ?) PatTree ?.
	 */
	
	
	/**
	 * TODO: set of cached peers (locations) ?.
	 */
	
     };
     
} /* end of namespace. */

#endif
