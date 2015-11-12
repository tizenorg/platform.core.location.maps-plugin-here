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

#ifndef GEOMAPOBJECT_H
#define GEOMAPOBJECT_H

#include "common/HereMaps_global.h"
#include "common/GeoBoundingBox.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoTiledMap;
class GeoCoordinates;

/**
 * This class encapsulates the common aspects of objects such as markers,
 * polygons and polylines (or groups of such objects) that can be placed on the
 * map. 
 *
 * \ingroup maps
 */
class GeoMapObject
{
public:
    /**
     * This enumeration defines identifiers for types of objects that can be
     * placed on the map.
     */
    enum Type
    {
        GMO_Marker,   ///< Indicates a marker.
        GMO_Polyline, ///< Indicates a polyline.
        GMO_Polygon,  ///< Indicates a polygon.
    };

    /**
     * This method is the default constructor.
     */
    GeoMapObject();

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~GeoMapObject();

    /**
     * This method retrieves the object type.
     * 
     * @return A member of the enumerated data type indicating the type of the
     *        given object.
     */
    virtual Type GetType() const = 0;

    /**
     * This method retrieves the object bounding box.
     * 
     * @return An object encapsulating the bounding box of the given object.
     */
    virtual GeoBoundingBox GetBoundingBox() const = 0;

    /**
     * This method checks if the given object is visible.
     * 
     * @return <code>true</code> if the object is visible, otherwise
     *        <code>false</code>. 
     */
    bool IsVisible() const;
 
    /**
     * This method sets a flag to indicate if the given object is visible.
     * 
     * @return visible A Boolean, <code>true</code> if the object is visible,
     *        otherwise <code>false</code>.
     */
    virtual void SetVisible(bool visible);

   /**
    * This method checks if the object can be rendered on the map.
    *
    * @return A Boolean, <code>true</code> if the object can be rendered,
    *        otherwise <code>false</code>.
    */
    virtual bool IsValid() const = 0;

protected:

   /**
    * This method updates the map.
    */
    void UpdateMap();

   /**
    * This method retrieves the parent object of the map, which is in effect the
    * GL context in which the map is drawn.
    * 
    * @return A pointer to an object encapsulating the parent map.  
    */
    GeoTiledMap* GetParentMap() const;

private:
    friend class GeoTiledMap;
    friend class GeoMapObjectGroup;
    void SetParentMap(GeoTiledMap& rMap);
    void ResetParentMap();

    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoMapObject);

    class GeoMapObjectImpl;
    std::auto_ptr<GeoMapObjectImpl> m_impl;
};

HERE_MAPS_END_NAMESPACE

#endif // GEOMAPOBJECT_H
