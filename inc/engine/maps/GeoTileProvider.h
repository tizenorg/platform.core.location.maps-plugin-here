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

#ifndef GEOTILEPROVIDER_H
#define GEOTILEPROVIDER_H

#include "common/HereMaps_global.h"
#include "maps/GeoProvider.h"

HERE_MAPS_BEGIN_NAMESPACE

class DrawableBitmap;
class TileKey;

/**
 * This class encapsulates a map tile provider which is responsible
 * for loading map tiles.
 *
 * \ingroup maps
 */
class GeoTileProvider : public GeoProvider
{
public:
    /**
     * This method is the default constructor.
     */
    GeoTileProvider();

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~GeoTileProvider();

    /**
     * This method loads the map tile specified by the caller.
     * 
     * @param tileKey A constant reference to an object that specifies a tile
     *        key. 
     *
     * @return A value representing the identifier of request to load the tile.
     */
    RestItemHandle::RequestId LoadTile(const TileKey& tileKey);

    /**
     * This method aborts loading of the map tile specified by the caller. 
     * 
     * @param tile A constant reference to an object representing the tile whose
     *        loading is to be aborted.
     */
    void AbortTile(const TilePtr& tile);
    
    /**
     * This method registers a callback function to be invoked when the tile has loaded.
     * 
     * @param signal A constant reference to a function to be invoked when the
     *        tile has loaded; the function accepts a reference to a
     *        <code>TileKey</code> object and a pointer to the tile bitmap (see
     *        also \ref GeoProvider).
     */
    void TileLoaded(const TileLoadedFunc &signal);

    /**
     * This method registers a callback function to be invoked when an attempt
     * to load a map tile has failed.
     * 
     * @param signal A constant reference to a function to be invoked when an
     *        attempt to load a tile has failed; the function accepts a
     *        reference to a <code>TileKey</code> object and a reference to an
     *        object containing information about the error that occurred (an
     *        instance of <code>ErrorBase</code>).
     */
    void TileFailed(const TileFailedFunc& signal);

private:
    class GeoTileProviderImpl;
    std::auto_ptr<GeoTileProviderImpl> m_impl;
};

HERE_MAPS_END_NAMESPACE

#endif // GEOTILEPROVIDER_H
