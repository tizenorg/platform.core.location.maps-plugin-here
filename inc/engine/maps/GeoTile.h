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

#ifndef GEOTILE_H
#define GEOTILE_H

#include <tr1/memory>
#include "common/HereMaps_global.h"

#ifndef TIZEN_MIGRATION
#include <FGraphics.h>
#include <FGraphicsOpengl2.h>
#endif

#include "common/RestItemHandle.h"
#include "maps/DrawableBitmap.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoProviderManager;

#if 0 //note: this class has been moved to a separate file
/**
 * This class encapsulates a bitmap that can be drawn in a graphics context (on
 * the map, whether the bitmap can represent a tile). 
 *
 * A map tile supports two layers, the map tile layer and a map objects layer,
 * (which overlays the map tile layer). The latter may be
 * <code>NULL</code> if no objects have been added to the map. 
 * 
 * \ingroup maps
 */
class DrawableBitmap
{
public:
    /**
     * This typedef defines a render handle as a type.
     */
    typedef UInt RenderHandle;

    
    /**
     * This method is a constructor. It initiates a new instance using the
     * bitmap pointer supplied by the caller.
     * 
     * @param bitmap A pointer to a bitmap object.
     */
    DrawableBitmap(std::auto_ptr<Tizen::Graphics::Bitmap>& bitmap)
    : m_bitmap(bitmap)
    , m_renderHandle(0)
    {
    }

    /**
     * This method is the destructor. It destroys the given instance and rests
     * the render handle.
     */
    ~DrawableBitmap()
    {
        ResetRenderHandle();
    }

    /**
     * This method resets the render handle for the given bitmap instance. 
     */
    void ResetRenderHandle()
    {
        if (m_renderHandle)
        {
            Tizen::Graphics::Opengl::glDeleteTextures(1, &m_renderHandle);
        }
        m_renderHandle = 0;
    }

    /**
     * This method obtains a pointer to the bitmap.
     * 
     * @return A pointer to the bitmap.
     */
    Tizen::Graphics::Bitmap* GetBitmap() const
    {
        return m_bitmap.get();
    }

    /**
     * This method sets the render handle for the given bitmap instance to the
     * value provided by the caller.
     * 
     * @param aRenderHandle A new value for the render handle.
     */
    void SetRenderHandle(RenderHandle aRenderHandle)
    {
        m_renderHandle = aRenderHandle;
    }

    /**
     * This method retrieves the current render handle.
     * 
     * @return A unsigned integer representing the render handle.
     */
    RenderHandle GetRenderHandle() const
    {
        return m_renderHandle;
    }

private:
    std::auto_ptr<Tizen::Graphics::Bitmap> m_bitmap;
    RenderHandle m_renderHandle;
};

//-----------------------------------------------------------------------------

typedef std::tr1::shared_ptr<DrawableBitmap> DrawableBitmapPtr;

#endif

class TileKey;


/**
 * This class encapsulates a map tile. A map tile is a square bitmap that is
 * fetched from a grid representing the normalized Mercator projection. The
 * position of the tile in this grid depends on the map zoom level and is
 * defined by the x and y coordinates. At the lowest zoom level, there is only
 * one tile. At the next higher zoom level, the grid is 2 x 2. With each zoom
 * level above that, the x-size and the y-size of the grid increase by a power
 * of two.
 * 
 * \ingroup maps
 */
class GeoTile
{
public:

    /**
     * This enumeration defines identifiers for event types.
     */
    enum EventType
    {
        ET_OnTileFetcherReply = 0, ///< Indicates an event fired when a reply to
                                   ///  a tile fetch request arrives.
        ET_OnFailure               ///< Indicates an event fired on failure.
    };

    
    /**
     * This property holds a value representing the tile size. 
     */
    static int size;

    /**
     * This method is a contructor. It initializes a new instance of the class
     * using the manager reference and the tile key provided by the caller.
     * 
     * @param rKey A constant reference to a key object that identifies the tile.
     */
    GeoTile(const TileKey& rKey);

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~GeoTile();

    /**
     * This method retrieves the tile key.
     * 
     * @return A constant reference to the tile key object for the given tile.
     */
    const TileKey& GetKey() const;

    /**
     * This method sets a flag to indicate whether the given map tile has been
     * requested for display.
     * 
     * @param b A Boolean indcating if the given map tile has been requested
     *(       <code>true</code>) or not (<code>false</code>).
     */
    void SetMarked(bool b);

    /**
     * This method checks whether the given map tile has been
     * requested for display.
     * 
     * @return A Boolean indcating if the given map tile has been requested
     *(       <code>true</code>) or not (<code>false</code>).
     */
    bool IsMarked() const;

    /**
     * This method retrieves a point to the tile image.
     * 
     * @return A pointer to the tile image.
     */
    DrawableBitmapPtr GetImage() const;

    /**
     * This method sets the tile image.
     * 
     * @param image A pointer to the tile image.
     */
    void SetImage(DrawableBitmapPtr image);

    /**
     * This method retrieves an object that represents a pending tile request to
     * the REST server.
     * 
     * @return A value representing the identifier of the issued request.
     */
    const RestItemHandle::RequestId GetPendingRequest() const;

    /**
     * This method marks a tile request to the REST server as pending.
     * 
     * @aRequestId An identifier representing a tile request.
     */
    void SetPendingRequest(RestItemHandle::RequestId aRequestId);

    /**
     * This method sets/creates the map object layer. 
     * 
     * A tile supports two layers, the map tile layer on which the tile is
     * drawn, and a layer superimposed on top of the map tile layer, which
     * contains the map objects that may have been added/created. If no objects
     * have been added/created, the map object layer is <code>NULL</code>.
     * 
     * @param layer A pointer to an instance of <code>DrawableBitmap</code> that
     *        constitutes the object layer.
     */
    void SetMapObjectLayer(DrawableBitmapPtr layer);

    /**
     * This method retrieves a pointer to the map object layer. 
     * 
     * A tile supports two layers, the map tile layer on which the tile is
     * drawn, and a layer superimposed on top of the map tile layer, which
     * contains the map objects that may have been added/created. If no objects
     * have been added/created, the map object layer is <code>NULL</code>.
     * 
     * @return A pointer to an instance of <code>DrawableBitmap</code> that
     *        constitutes the object layer.
     */
    DrawableBitmapPtr GetMapObjectLayer() const;

    /**
     * This method removes the map object layer. 
     * 
     * A tile supports two layers, the map tile layer on which the tile is
     * drawn, and a layer superimposed on top of the map tile layer, which
     * contains the map objects that may have been added/created. If no objects
     * have been added/created, the map object layer is <code>NULL</code>.
     */
    void RemoveMapObjectLayer();

    /**
     * This methods aborts loading of the given tile.
     */
    void AbortLoading();

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoTile);

    class GeoTileImpl;
    GeoTileImpl* m_pImpl;
};

typedef std::tr1::shared_ptr<GeoTile> TilePtr;

HERE_MAPS_END_NAMESPACE

#endif
