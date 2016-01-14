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

class TileFetcherCache
{
public:
	TileFetcherCache();

	virtual ~TileFetcherCache();

	static TileFetcherCache& GetInstance();

	void shutdown();

	bool remove(const int hash);

	bool isFound(const int hash);

	TileCacheList::iterator find(const int hash);

	unsigned long read(const int hash, unsigned char *&buffer, unsigned long &size);

	unsigned long write(const int hash, const unsigned char *buffer, const unsigned long size);

	void clearCache();

	Here::Maps::RestItemHandle::RequestId load(const Here::Maps::TileKey &rKey, Here::Maps::TileFetcherQueryListener &rListener);

	void abort(void *pArg);

	void fire(void *pArg);

private:
	HERE_MAPS_NO_COPY_NO_ASSIGN(TileFetcherCache);

	void __initCache();

	static bool __compareTileCache(const TileCache& first, const TileCache& second);

	bool __checkCapacity(void);

	bool __isAvailableSpace(void);

	bool __isAvailableCount(void);

	bool __getCachePath(char *path, int size);

	bool __getFilePath(int hash, char *path, int size);

	static gboolean __fireTimer(gpointer data);

	static gboolean __fireIdler(gpointer data);

	static void __timerDestroy(gpointer data);

	static void __idlerDestroy(gpointer data);

	//members
	class TileFetcherCacheImpl;
	TileFetcherCacheImpl* m_pImpl;

	char __cachePath[256];
};

TIZEN_MAPS_END_NAMESPACE

#endif
