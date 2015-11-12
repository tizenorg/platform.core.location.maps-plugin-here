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

#ifndef GEOOBJECTPROVIDER_H
#define GEOOBJECTPROVIDER_H

#include "common/HereMaps_global.h"
#include "maps/GeoProvider.h"
#ifdef TIZEN_MIGRATION
#include "graphic/Dimension.h"
#include "graphic/Point.h"
#endif

HERE_MAPS_BEGIN_NAMESPACE

class GeoMapObject;
class GeoProjection;

/**
 * This class encapsulates a map object provider which manages all the objects
 * to be displayed in any of the tiles that make up the visible map. The
 * provider object can load tiles, add and remove objects to them, and retrieve
 * objects from a specific pixel location.
 *
 * \ingroup maps
 */
class GeoObjectProvider: public GeoProvider
{
public:
    
    /**
     * This method is a constructor.
     * 
     * @param projection A Pointer to the projection to use.
     * 
     * @param tileSize a value indicating the size of the map tile to use. 
     */
    GeoObjectProvider(GeoProjection* projection, int tileSize);

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~GeoObjectProvider();

    /**
     * This method loads the tile specified by the caller.
     * 
     * @param tileKey A constant reference to an object that specifies a tile
     *        key. 
     *
     * @return A value representing the identifier of the issued request.
     */
    RestItemHandle::RequestId LoadTile(const TileKey& tileKey);

    /**
     * This method aborts loading of the tile specified by the caller.
     * 
     * @param tile A constant reference to an object encapsulating the tile
     *        whose loading is to be aborted.
     */
    void AbortTile(const TilePtr& tile);
    
    /**
     * This method sets a function to be invoked when the tile has loaded.
     * 
     * @param signal A constant reference to a function to be invoked when the
     *        tile has loaded; the function accepts a reference to a
     *        <code>TileKey</code> object and a pointer to the tile bitmap (see
     *        also <code>GeoProvider</code>).
     */
    void TileLoaded(const TileLoadedFunc& signal);

    /**
     * This method sets function to be invoked when loading the tile failed.
     *
     * @param signal A constant reference to a function to be invoked when the
     *        tile load failed; the function accepts a reference to the
     *        corresponding <code>ErrorBase</code> object
     *        <code>GeoProvider</code>). 
     */
    void TileFailed(const TileFailedFunc& signal);

    /**
     * This method adds an object specified by the caller.
     * 
     * @param obj A pointer to the object to add. 
     */
    void AddObject(GeoMapObject* obj, bool transferOwnership);

    /**
     * This method removes an object specified by the caller. The objects
     * are also deleted if we have ownership (see AddObject)
     * 
     * @param obj A pointer to the object to remove. 
     * @return Boolean value indicating if the removal of the object was successful
     */
    bool RemoveObject(GeoMapObject* obj);

    /**
     * This method removes all objects specified by the caller. The objects
     * are also deleted if we have ownership (see AddObject)
     *
     * @param obj A pointer to the object to remove.
     * @return Boolean value indicating if the removal of the object was successful
     */
    bool RemoveAllObjects();

    /**
     * This method retrieves an object at the screen position specified by the
     * caller. 
     * 
     * @param point A constant reference to an object specifying the screen
     *        coordinates of a location from which to retrieve an object.
     */
    GeoMapObject* GetObjectAtScreenPosition(const Tizen::Maps::Point& point);

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoObjectProvider);

    class GeoObjectProviderImpl;
    std::auto_ptr<GeoObjectProviderImpl> m_impl;
};

HERE_MAPS_END_NAMESPACE

#endif // GEOOBJECTPROVIDER_H
