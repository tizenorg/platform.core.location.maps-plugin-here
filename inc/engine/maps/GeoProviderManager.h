/*
 * Copyright (C) 2013 HERE Global B.V. All rights reserved.
 * This software, including documentation, is protected by copyright controlled by
 * HERE Global B.V. (“Software”). All rights are reserved. Copying, including reproducing,
 * storing, adapting or translating, any or all of this material requires the prior
 * written consent of HERE Global B.V. You may use this
 * Software in accordance with the terms and conditions defined in the
 * HERE Location Platform Services Terms and Conditions, available at
 * http://developer.here.com/terms-conditions-base
 *
 * As an additional permission to the above, you may distribute Software,
 * in object code format as part of an Application, according to, and subject to, terms and
 * conditions defined in the Tizen Software Development kit (“SDK”) License Agreement.
 * You may distribute such object code format Application under terms of your choice,
 * provided that the header and source files of the Software have not been modified.
 */

#ifndef GEOPROVIDERMANAGER_P_H_
#define GEOPROVIDERMANAGER_P_H_

#include <vector>

#include "common/HereMaps_global.h"

#include "maps/GeoTile.h"
#include "maps/GeoProvider.h"

#ifdef TIZEN_MIGRATION
#include "base/Timer.h"
#endif

HERE_MAPS_BEGIN_NAMESPACE

class GeoTiledMap;
class QueryListener;

/**
 * This class encapsulates management of all the providers of tiles and map
 * objects. It registers providers and requests tiles and objects on their
 * behalf, eventually compositing each tile in the map to ensure the tiles
 * contain not only the map tile bitmaps, but also any markers, polylines and
 * polygons that must be drawn on top of the bitmaps.
 * 
 * The virtual methods defined on this class require implementation by derived
 * classes. 
 * 
 * \ingroup maps
 */
class GeoProviderManager : public Tizen::Maps::ITimerEventListener
{
public:
    /**
     * This method retrieves an object representing the key for a tile on the
     * basis of the zoom level and coordinates of the tile in the tile grid at
     * that zoom level.
     * 
     * @param level A value indicating the zoom level.
     * 
     * @param x A value representing the x-coordinate in the tile grid.
     * 
     * @param y A value representing the y-coordinate in the tile grid.
     * 
     * @return An object representing the tile key.
     */
    TileKey GetKey(int level, int x, int y);

    /**
     * This method is the default constructor.
     */
    GeoProviderManager();

    /**
     * This method is a constructor.
     *
     * @param rMap A reference to the tile map whose tiles are processed by the
     *        given manager object.
     */
    GeoProviderManager(GeoTiledMap& rMap);

    /**
     * This method is the (virtual) destructor.  
     */
    virtual ~GeoProviderManager();

    /**
     * This method is invoked when the timer expires.
     * 
     * @param timer A reference to the timer object.
     */
    virtual void OnTimerExpired(Tizen::Maps::Timer& timer);

    /**
     * This method checks if a previously requested tile is available.  
     * 
     * @param level A value indicating the zoom level.
     * 
     * @param x A value representing the x-coordinate in the tile grid.
     * 
     * @param y A value representing the y-coordinate in the tile grid.
     * 
     * @return A pointer to the tile object (which is <code>NULL</code> if the
     *         tile is not available). 
     */
    TilePtr PeekTile(int level, int x, int y);

    /**
     * This method checks if a previously requested tile is available.  
     * 
     * @param key An object representing the key that identifies the tile to check.
     * 
     * @return A pointer to the tile object (which is <code>NULL</code> if the
     *         tile is not available). 
     */
    TilePtr PeekTile(const TileKey& key);

    /**
     * This method requests a tile.
     * 
     * @param level A value indicating the zoom level.
     * 
     * @param x A value representing the x-coordinate in the tile grid.
     * 
     * @param y A value representing the y-coordinate in the tile grid.
     * 
     * @return A pointer to the tile object (which is <code>NULL</code> if the
     *         tile is not available). 
     */
    TilePtr RequestTile(int level, int x, int y);

    /**
     * This method removes the tile specified by the caller from the cache.
     * 
     * @param tile A constant reference to the tile object to remove from the cache. 
     */
    void RemoveCachedTile(const TilePtr& tile);

    /**
     * This method clears the map tile cache.
     */
    void ClearCache();

    /**
     * This method clears any map objects from the cache.
     * 
     * @param bClearAndRequest A Boolean indicating if the map objects should be
     *        rerequested when they have been cleared (<code>true</code>,
     *        default) or not <code>fault</code>.
     */
    void ClearCachedMapObjectsOnly(bool bClearAndRequest=true);

    /**
     * This method retrieves a count of cached map tiles.
     * 
     * @return A value indicating the number of cached map tiles.
     */
    size_t GetNumCachedTiles() const;

    /**
     * This method adds a provider to those managed by the given manager instance.
     * 
     * @param provider A pointer to a provider object to add.
     */
    void AddProvider(GeoProvider* provider);

    /**
     * This method removes the provider identified by the caller to those
     * managed by the given manager instance.
     * 
     * @param provider A pointer to a provider object to remove.
     */
    bool RemoveProvider(GeoProvider* pProvider);

    /**
     * This method retrieves a provider matching the index supplied by the caller.
     * 
     * @param idx A value of the index from which to retrieve the provider. 
     * 
     * @return A pointer to the provider object or <code>NULL</code> if the
     *         supplied index is invalid. 
     */
    GeoProvider* GetProvider(size_t idx) const;

    /**
     * This method obtains the count of providers managed by the given
     * instance of <code>GeoProviderManager</code>.
     * 
     * @return A value representing the count of providers.
     */
    size_t GetNumProviders() const;
    
    /**
     * This method is invoked when a tile has been loaded. It adds the
     * tile to the list of loaded files, removes it from the list of loading
     * tiles and the cache, and ensures it is displayed. 
     * 
     * @param rKey A constant reference to a key object that identifies the
     *        loaded tile.  
     * 
     * @param image A pointer to the tile image object.
     *
     * @param rProvider The provider for which the tile has been acquired.
     */
    void HandleTileLoaded(const TileKey& rKey, DrawableBitmapPtr image, GeoProvider& rProvider);

    /**
     * This method is invoked when a tile has been loaded. It adds the
     * tile to the list of loaded files, removes it from the list of loading
     * tiles and the cache, and ensures it is displayed. 
     * 
     * @param rKey A constant reference to a key object that identifies the
     *        tile.  
     * 
     * @param rError A constant reference to an object containing information
     *        about the error that occurred.
     */
    void HandleTileFailed(const TileKey& rKey, const ErrorBase& rError);

    /**
     * This method starts the process of loading the next requested file. 
     */
    void StartNextTileLoad();

    /**
     * This method sets a value indicating the maximum number of pending
     * requests.
     * 
     * @param uLimit A value indicating the maximum number of pending requests.
     */
    void SetPendingRequestsLimit(size_t uLimit);

    /**
     * This method retrieves a value indicating the maximum number of pending
     * requests.
     * 
     * @return A value indicating the maximum number of pending requests.
     */
    size_t GetPendingRequestsLimit() const;

    /**
     * This method retrieves a value indicating the count of pending
     * requests.
     * 
     * @return A value indicating how many requests are pending.
     */
    size_t GetNumPendingRequests() const;

    /**
     * This method sets a value indicating the maximum number of tiles that can
     * be cached.
     * 
     * @param uLimit A value indicating the maximum number of cached tiles.
     */
    void SetCachedTilesLimit(size_t uLimit);

    /**
     * This method retrieves a value indicating the maximum number of tiles that
     * can be cached.
     * 
     * @return A value indicating the maximum number of cached tiles.
     */
    size_t GetCachedTilesLimit() const;

private:
    void LoadTile(const TilePtr tile, unsigned int uProviderLevel);
    void AbortTile(const TilePtr tile);
    void LogTile(const String& text,const TilePtr& tile);
    void LogTile(const String& text,int level,int x,int y);

    void BeginMarking();
    void EndMarking();

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoProviderManager);
    friend class GeoTiledMap;
    friend class TestGeoProviderManager;
    class GeoProviderManagerImpl;
    GeoProviderManagerImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
