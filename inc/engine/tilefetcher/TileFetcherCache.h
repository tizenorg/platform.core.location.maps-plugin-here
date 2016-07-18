//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef TILEFETCHERCACHE_H
#define TILEFETCHERCACHE_H

#include <list>
#include <time.h>
#include <glib.h>
#include "common/HereMaps_global.h"

#include "tilefetcher/TileFetcherQueryListener.h"
#include "common/RestItemHandle.h"
#include "common/TileKey.h"



TIZEN_MAPS_BEGIN_NAMESPACE

class TileCache
{
public:
	int hash;
	long size;
	long hit;
	long timestamp;

	TileCache(int _hash, long _size=0, long _hit=0)
	{
		hash = _hash;
		size = _size;
		hit = _hit;

		time_t _time;
		time(&_time);
		timestamp = _time;
	}
};

typedef std::list<TileCache> TileCacheList;

/**
 * 
 * This class encapsulates a caching system for map tiles based on the file system.
 * 
 */

class TileFetcherCache
{
public:
    /**
     * This method is the default constructor.
     */
	TileFetcherCache();

    /**
     * This method is the (virtual) destructor.
     */
	virtual ~TileFetcherCache();

    /**
     * This method is to get the instance of this class.
     */
	static TileFetcherCache& GetInstance();

    /**
     * This method is to clear caching system.
     */
	void shutdown();

    /**
     * This method is to remove a tile having the hash.
     */
	bool remove(const int hash);

    /**
     * This method is to check if there is a tile having the hash.
     */
	bool isFound(const int hash);

    /**
     * This method is to get the iterator of a tile having the hash.
     */
	TileCacheList::iterator find(const int hash);

    /**
     * This method is to read a tile having the hash from own file system.
     *
     * @param	hash	A value of hash indicating the tile
     * @param	buffer	A buffer to store the map tile
     * @param	size	A size of map tile (bytes)
     */
	unsigned long read(const int hash, unsigned char *&buffer, unsigned long &size);

    /**
     * This method is to write a tile having the hash to own file system.
     *
     * @param	hash	A value of hash indicating the tile
     * @param	buffer	A buffer stored the map tile
     * @param	size	A size of map tile (bytes)
     */
	unsigned long write(const int hash, const unsigned char *buffer, const unsigned long size);

    /**
     * This method is to clear all of cache files.
     */
	void clearCache();

    /**
     * This method is to abort the request to get a tile from the cache.
     */
	void abort(void *pArg);

    /**
     * This method is to request to get a tile from the cache.
     */
	void fire(void *pArg);

private:
	HERE_MAPS_NO_COPY_NO_ASSIGN(TileFetcherCache);

    /**
     * This method is to initialize the cache by scanning and building the list of already cached tiles.
     */
	void __initCache();

    /**
     * This method is to compare hit rates of tiles to decide which one will be removed.
     */
	static bool __compareTileCache(const TileCache& first, const TileCache& second);

    /**
     * This method is to check if more tiles can be stored.
     */
	bool __checkCapacity(void);

    /**
     * This method is to check if more tiles can be stored with only free space.
     */
	bool __isAvailableSpace(void);

    /**
     * This method is to check if more tiles can be stored with only the count of tiles.
     */
	bool __isAvailableCount(void);

    /**
     * This method is to get the path where tile files are stored in.
     */
	bool __getCachePath(char *path, int size);

    /**
     * This method is to get the path of the tile.
     */
	bool __getFilePath(const int hash, char *path, int size);

    /**
     * This method is to get the path of the tile.
     */
	bool __getFilePath(const char *fname, char *path, int size);

    /**
     * This method is to get the hash from the file name.
     */
	int __parseHash(const char *fname);

    /**
     * This method is a timer callback to delay loading time.
     */
	static gboolean __fireTimer(gpointer data);

    /**
     * This method is a timer callback to delay loading time.
     */
	static gboolean __fireIdler(gpointer data);

    /**
     * This method is a timer destroyer.
     */
	static void __timerDestroy(gpointer data);

    /**
     * This method is a timer destroyer.
     */
	static void __idlerDestroy(gpointer data);

	//members
	class TileFetcherCacheImpl;
	TileFetcherCacheImpl* m_pImpl;

	char __cachePath[256];
};

TIZEN_MAPS_END_NAMESPACE

#endif
