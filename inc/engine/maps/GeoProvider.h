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

#ifndef GEOPROVIDER_P_H_
#define GEOPROVIDER_P_H_

#include <tr1/functional>

#include "common/HereMaps_global.h"
#include "common/RestItemHandle.h"
#include "maps/GeoTile.h"

HERE_MAPS_BEGIN_NAMESPACE

class TileKey;
class ErrorBase;
class DrawableBitmap;

/**
 * This class is the base class for provider classes in the Maps API. An example
 * of a derived class is <code>GeoObjectProvider</code>.
 * 
 * \ingroup maps
 */
class GeoProvider
{
public:
    /**
     * This method is the default constructor.
     */
    GeoProvider() {}

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~GeoProvider() {}

    /**
     * This method loads the map tile specified by the caller. The method must
     * be implemented by the derived classes.
     * 
     * @param tileKey A constant reference to an object that specifies a tile
     *        key. 
     *
     * @return A value representing the identifier of the tile request.
     */
    virtual RestItemHandle::RequestId LoadTile(const TileKey& tileKey) = 0;

    /**
     * This method aborts loading of the map tile specified by the caller. The
     * method must be implemented by the derived classes.
     * 
     * @param tile The tile whose loading is to be aborted.
     */
    virtual void AbortTile(const TilePtr& tile) = 0;

    /**
     * This typedef defines a function as a type. The function can be called
     * when the map tile has been loaded. A function of this type accepts a
     * reference to a <code>TileKey</code> object, a pointer to the tile
     * bitmap and a reference to an instance of <code>GeoProvider</code>.
     */
    typedef std::tr1::function<void (const TileKey&, DrawableBitmapPtr, GeoProvider&)> TileLoadedFunc;
    
    /**
     * This method registers a function to be invoked when the tile has loaded.
     * 
     * @param signal A constant reference to a function to be invoked when the
     *        tile has loaded; the function accepts a reference to a
     *        <code>TileKey</code> object and a pointer to the tile bitmap.
     */
    virtual void TileLoaded(const TileLoadedFunc& signal) = 0;
    
    /**
     * This typedef defines a function as a type. The function can be called
     * when an attempt to load a map tile has failed. A function of this type
     * accepts a reference to a <code>TileKey</code> object and a reference to
     * an object containing information about the error that occurred (an
     * instance of <code>ErrorBase</code>).
     */
    typedef std::tr1::function<void (const TileKey&, const ErrorBase&)> TileFailedFunc;

    /**
     * This method sets function to be invoked when an attempt to load a tile
     * has failed.
     *
     * @param signal A constant reference to a function to be invoked when the
     *        tile load has failed; the callback function accepts a reference to
     *        a <code>TileKey</code> object and a reference to an object
     *        encapsulating information about the error that occurred (an
     *        instance of <code>ErrorBase</code>).
     */
    virtual void TileFailed(const TileFailedFunc& signal) = 0;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoProvider);
};

HERE_MAPS_END_NAMESPACE

#endif /* GEOPROVIDER_P_H_ */
