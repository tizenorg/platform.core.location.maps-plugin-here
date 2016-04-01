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

#ifndef GEOTILEDMAP_H
#define GEOTILEDMAP_H

#include <vector>
#include <tr1/functional>

#include "common/HereMaps_global.h"

#ifndef TIZEN_MIGRATION
#include <FUi.h>
#include <FGraphics.h>
#include <FGrpColor.h>
#endif

#include "maps/DrawableBitmap.h"
#ifdef TIZEN_MIGRATION
#include "graphic/Dimension.h"
#include "graphic/Point.h"
#include "graphic/Color.h"
#include <Evas_GL.h>

using namespace Tizen::Maps;
#endif

HERE_MAPS_BEGIN_NAMESPACE

class GeoTile;
class ErrorBase;
class GeoMapObject;
class GeoCoordinates;
class TileFetcherReply;
class GeoProjectionNode;
class GeoMapObjectMarker;
class GeoProviderManager;


/**
 * This class encapsulates a tiled map. The map is composed of square bitmap
 * tiles retrieved from a grid that represents the normalized Mercator
 * projection (see also <code>GeoTile</code>). The class supports a number of
 * map types (for example normal, terrain, satellite, etc.) and provides methods
 * to control the map size, orientation (heading), zoom level, and managing
 * objects such as markers, polylines and polygons that can be superimposed on
 * the map.
 * 
 * \ingroup maps
 */
class EXPORT_API GeoTiledMap
{
public:

    /**
     * This enumeration defines identifiers for supported map types.
     */
    enum MapType
    {
        MT_Normal_Day = 0,              ///< Indicates a normal (street/physical
                                        ///  day map.
        MT_Satellite_Day,               ///< Indicates a satellite day map.
        MT_Terrain_Day,                 ///< Indicates a terrain day map.
        MT_Hybrid_Day,                  ///< Indicates a hybrid day map        
                                        ///  (satellite, with roads and labels).
#ifdef TIZEN_MIGRATION
        MT_Normal_Day_Grey,
        MT_Normal_Day_Transit,
        MT_Normal_Night_Transit,
        MT_Normal_Traffic_Day,
        MT_Normal_Traffic_Night,
        MT_Normal_Day_Custom,
        MT_Normal_Night,
        MT_Normal_Night_Grey,
        MT_Pedestrian_Day,
        MT_Pedestrian_Day_Mobile,
        MT_Pedestrian_Night,
        MT_Pedestrian_Night_Mobile,
        MT_Carnav_Day_Grey,
        MT_Normal_Day_Mobile,
        MT_Normal_Day_Grey_Mobile,
        MT_Normal_Day_Transit_Mobile,
        MT_Normal_Night_Transit_Mobile,
        MT_Normal_Night_Mobile,
        MT_Normal_Night_Grey_Mobile,
        MT_Reduced_Day,
        MT_Reduced_Night,
        MT_Hybrid_Day_Transit,
        MT_Hybrid_Grey_Day,
        MT_Hybrid_Traffic_Day,
        MT_Hybrid_Day_Mobile,
        MT_Terrain_Day_Mobile,
#endif
        MT_Last_Entry_Undefined         ///< Indicates that the map type is not
                                        ///  defined. 
    };

    /**
     * This enumeration defines identifiers for logo color.
     */
    enum LogoColor
    {
        LC_Blue = 0,  ///< Indicates that the color is blue.
        LC_White      ///< Indicates that the color is white.
    };

    /**
     * This method is the default constructor.
     */
    GeoTiledMap();

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~GeoTiledMap();

    /**
     * This method sets the size of the map.
     * 
     * @param size A constant reference to an object specifying the size of the
     *        map in pixels (width and height).
     */
    void SetMapSize(const Tizen::Maps::Dimension& size);

    /**
     * This method retrieves the map size.
     *
     * @return A constant reference to an object containing the width and height
     *        of the map in pixels.
     */
    const Tizen::Maps::Dimension& GetMapSize() const;

    /**
     * This method sets the map zoom level.
     * 
     * @param zoomLevel A value indicating the new zoom level.
     */
    #ifdef TIZEN_MIGRATION
    void SetZoomLevel(double zoomLevel, bool bUpdate=true);
    #else
    void SetZoomLevel(double zoomLevel);
    #endif
    
    /**
     * This method retrieves the map zoom level.
     * 
     * @return A value indicating the new zoom level.
     */
    double GetZoomLevel() const;
    
    /**
     * This method retrieves the minimum map zoom level.
     * 
     * @return A value indicating the minimum map zoom level.
     */
    double GetMinimumZoomLevel() const;
    
    /**
     * This method retrieves the maximum map zoom level.
     * 
     * @return A value indicating the maximum map zoom level.
     */
    double GetMaximumZoomLevel() const;
   
    /**
     * This method pans the map the caller-specified number of pixels
     * horizontally and vertically.
     *
     * @param dx A value indicating the number of pixels to move the map along
     *        the horizontal axis.
     *
     * @param dy A value indicating the number of pixels to move the map along
     *        the vertical axis.
     */
    void Pan(int dx, int dy);

    /**
     * This method sets the coordinates of the map center. 
     * 
     * @param center A constant reference to an object containing the new
     *        geographic coordinates of the map center.
     */
    void SetCenter(const GeoCoordinates& center);

    /**
     * This method retrieves the coordinates of the map center. 
     * 
     * @return A constant reference to an object containing the
     *        geographic coordinates of the map center.
     */
    GeoCoordinates GetCenter() const;

    /**
     * This method renders the given object invalid by resetting the drawable
     * object representing the map and resetting and reinitializing the tile
     * cache.
     */
    void Invalidate();

    /**
     * This method invalidates (discards) all the map objects, including
     * markers. 
     */
    void InvalidateMapObjects();

#ifdef TIZEN_SUPPORT_OPTIMIZATION_OF_REDRAWING
    /**
     * This method invalidates (discards) all the map markers.
     */
    void InvalidateMapMarkers();
#endif

    /**
     * This method invalidates (clears) the cache.
     */
    void ClearCache();

    /**
     * This method clears all the map objects associated with the given tiled
     * map object. 
     */
    void ClearMapObjects();

    /**
     * This method converts the geographic location specified by the caller to
     * screen coordinates, taking into consideration the current zoom level and
     * the view area.
     * 
     * @param coordinate A constant reference to an object containing the
     *        coordinates to convert.
     * 
     * @return An object containing the x and y coordinates defining the screen
     *        location.
     */
    Tizen::Maps::Point CoordinateToScreenPosition(const GeoCoordinates& coordinate) const;

    /**
     * This method converts the screen position specified by the caller to
     * geographic coordinates. The method is called, for example, when a marker
     * is being added to the map.
     * 
     * @param screenPosition An object containing the x and y coordinates
     *        defining the screen location to convert.
     * 
     * @return An object containing the geographic coordinates of corresponding
     *        to the received screen position.
     */
    GeoCoordinates ScreenPositionToCoordinate(const Tizen::Maps::Point& screenPosition) const;

    //map objects support
    /**
     * This method adds an object to the map. The object is a marker, a polygon
     * or polyline, or a group of objects.
     * 
     * @param obj A pointer to an object to add to the map. If the object does
     *        not exist (is <code>NULL</code>), the method has no effect.
     * 
     * @param bTransferOwnership A Boolean value indicating if the ownership of
     *        the map object given in the first parameter should be transferred
     *        to this map instance (<code>true</code>, default) or not
     *        (<code>false</code>). The default behavior transfers the
     *        ownership, which means that the map object becomes responsible for
     *        deleting the markers.
     */
    void AddObject(GeoMapObject* obj, bool bTransferOwnership=true);

    /**
     * This method removes the object specified by the caller from the map. 
     * 
     * @param obj A pointer to the object to remove from the map. If the object
     *        does not exist (is <code>NULL</code>), the method has no effect.
     * 
     * @return Boolean value indicating if the removal of the object was
     *        successful (<code>true</code>) or not (<code>false</code>).
     */
    bool RemoveObject(GeoMapObject* obj);

    /**
     * This method obtains a pointer to the map object located at the screen
     * position indicated by the caller.
     * 
     * @param point A constant reference to an object containing the pixel
     *        coordinates of the screen position from which to get the map object.
     * 
     * @return A pointer to the map object at the specified screen location,
     *        otherwise <code>NULL</code> if no map object is found.
     */
    GeoMapObject* GetObjectAtScreenPosition(const Tizen::Maps::Point& point) const;

    /**
     * This method obtains a count of marker objects in the given tiled map.
     * 
     * @return A value that indicates the number of marker objects.
     */
    size_t GetNumMarkerObjects() const;

    /**
     * This method retrieves a pointer to a marker object at the index specified
     * by the caller.
     * 
     * @param idx A value specifying the index of the marker object to
     *        retrieve. 
     * 
     * @return A pointer to the marker object at the specified index or
     *        <code>NULL</code> if the index is invalid.
     */
    GeoMapObjectMarker* GetMarkerObject(size_t idx) const;

    //draws the map into the current OpenGl context
    /**
     * This method draws (renders and displays) a map image of the size
     * specified by the caller. The displayed map includes the required map
     * tiles as well as any objects such as markers, polygons and polylines.
     * 
     * @param uWidth A value specifying the width of the map image.
     * 
     * @param uHeight A value specifying the height of the map image. 
     * 
     * @return A Boolean, <code>true</code> if the map has been successfully
     *        pained, otherwise <code>false</code>.
     */
    bool PaintMap(unsigned int uWidth, unsigned int uHeight);

    /**
     * This typedef defines a function object as a type. The function object can
     * be called when the map has been updated. A function object of this type
     * returns <code>void</code> and receives no arguments.
     */
#ifdef TIZEN_MIGRATION
    typedef std::tr1::function<void (void *)> UpdateMapSignalFunctor;
#else
    typedef std::tr1::function<void ()> UpdateMapSignalFunctor;
#endif

    /**
     * This method sets a callback to be invoked when the map has
     * been updated. 
     * 
     * @param slot A function object to be called when the map has
     *        been updated. 
     */
     void SetUpdateMapSignal(UpdateMapSignalFunctor slot);

     /**
      * This method sets the map type.
      * 
      * @param aMapType A value indicating the new map type.
      */
    void SetMapType(MapType aMapType);

     /**
      * This method retrieves the map type.
      * 
      * @return A value indicating the current map type.
      */
    MapType GetMapType() const;

    /*
     * Available language options are:
     * L"ara", L"chi", L"cht", L"dut", L"eng", L"ger", L"gle", L"fre", L"ita", L"spa", L"rus", L"pol", L"gre", L"wel"
     */
    /**
     * This method sets the language of the map. 
     * 
     * @param aMapLanguage A constant reference to a string containing a
     *        language code. The value of the string must be one of "ara"
     *        (Arabic), "chi" (Chinese), "cht" (Chinese-Taiwan), "dut" (Dutch),
     *        "eng" (English), "ger" (German), "gle" (Irish), "fre" (French),
     *        "ita" (Italian), "spa" (Spanish), "rus" (Russian), "pol" (Polish),
     *        "gre" (Greek), "wel" (Welsh)
     */
    void SetMapLanguage(const String& aMapLanguage);

    /**
     * This method retrieves the current language of the map. 
     * 
     * @return A constant reference to a string containing the language code,
     *        which is one of "ara" (Arabic), "chi" (Chinese), "cht"
     *        (Chinese-Taiwan), "dut" (Dutch), "eng" (English), "ger" (German),
     *        "gle" (Irish), "fre" (French), "ita" (Italian), "spa" (Spanish),
     *        "rus" (Russian), "pol" (Polish), "gre" (Greek), "wel" (Welsh)
     */
    const String& GetMapLanguage() const;

    /**
     * This method sets the size of the tiles used for rendering the map.
     *
     * @param uTileSizeInPX Specifies the width and the height of the tiles. Note that
     *        only 128 and 256 are supported as valid values.
     */
    void SetTileSize(unsigned int uTileSizeInPx);

    /**
     * This method retrieves the size of the tiles, used for rendering the map.
     * 
     * @return An unsigned integer indicating the size of the map tiles.
     */
    unsigned int GetTileSize() const;

    /**
     * This method changes the background color of the map.
     * The background color is updated after refreshing the map.
     * 
     * @param color A constant reference to an object representing the new map
     *        background color.
     */
    void SetBackgroundColor(const Tizen::Maps::Color& color);

#ifdef TIZEN_CUSTOMIZATION
    /**
     * This method retrieves the root tile, used for rendering the map.
     * 
     * @return An pointer indicating the bitmap of the root tile.
     */
    DrawableBitmapPtr GetRootPixmap();

    /**
     * This method sets a pointer of a structure of the Evas GL API object that
     *        contains the GL APIs to be used in Evas GL.
     * 
     * @param __glapi A pointer to a structure of the Evas GL API object. 
     */
    void SetEvasGlApi(Evas_GL_API *__glapi);

    /**
     * This typedef defines a function object as a type. The function object can
     * be called when the map has been ready after initialized. A function object of
     * this type returns <code>void</code> and receives no arguments.
     */
    typedef void(*ReadyMapSignalFunctor)(void);

    /**
     * This method sets a callback to be invoked when the map has
     * been ready after initialization.
     *
     * @param slot A function object to be called when the map has
     *        been ready after initialization.
     */
    void SetReadyMapSignal(ReadyMapSignalFunctor callback);

    /**
     * This method sets the angle of the map.
     *
     * @param angle The angle of the map [-360~360].
     */
    void SetAngle(double angle);

    /**
     * This method retrieves the angle of the map.
     *
     * @return A value indicating the angle of the map.
     */
    double GetAngle();

    /**
     * This method sets a Boolean value indicating if the scale bar is enabled or not.
     *
     * @param enable <code>true</code> if the given status is enabled,
     *        otherwise <code>false</code>.
     */
    void SetScalebar(bool enable);

    /**
     * This method retrieves a Boolean value indicating if the scale bar is enabled or not.
     *
     * @return <code>true</code> if the scale bar is enabled, otherwise <code>false</code>.
     */
    bool GetScalebar() const;
#endif

#ifdef TIZEN_SUPPORT_TILE_FILE_CACHE
    /**
     * This method invalidates (clears) the file cache for tiles.
     */
    void ClearTileFileCache();
#endif

private:
    bool HandleTileReady(int level, int x, int y, unsigned int uLevelProvider);
    bool DrawLogo(UInt uWidth, UInt uHeight, UInt aMapX = 0, UInt aMapY = 0);

    void UpdateMapSignal();
    void UpdateProjectionNodes();
    float CreateProjectionTree(std::vector<GeoProjectionNode*>& result, GeoProjectionNode* node);
    void InitializeCache();
    void SortMarkers();
    int GetDisplayDPI() const;
    void ClearMarkers();
    void SetRootPixmap(DrawableBitmapPtr rootPixmap);
#ifdef TIZEN_MIGRATION
    void ExtendLimitOfCachedTiles();
    bool DrawScalebar(UInt uWidth, UInt uHeight, UInt aMapX = 0, UInt aMapY = 0);
#endif

private:
    friend class GeoMapObject;
    friend class GeoMapObjectMarker;
    friend class GeoProviderManager;
    friend class TestGeoTiledMap;
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoTiledMap);

    class GeoTiledMapImpl;
    std::auto_ptr<GeoTiledMapImpl> m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif // GEOTILEDMAPDATA_H
