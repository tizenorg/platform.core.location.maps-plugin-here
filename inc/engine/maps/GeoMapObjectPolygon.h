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

#ifndef MAPOBJECTPOLYGON_H
#define MAPOBJECTPOLYGON_H

#include "common/HereMaps_global.h"
#include "maps/GeoMapObject.h"
#include "common/GeoCoordinates.h"
#include <tr1/functional>

#ifdef TIZEN_MIGRATION
#include "graphic/Color.h"
#else
namespace Tizen { namespace Graphics { class Color; } }
#endif

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates a map polygon object. A polygon is a closed polyline,
 * therefore, in addition to a polyline, its properties include a fill color.
 *
 * \ingroup maps
 */
class EXPORT_API GeoMapObjectPolygon : public GeoMapObject
{
public:

    /**
     * This method is the default constructor.
     */
    GeoMapObjectPolygon();

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~GeoMapObjectPolygon();

    /**
     * This method sets the path of the polygon, which is a list of locations
     * that the path (line) connects. 
     * 
     * @param path A constant reference to an object containing a list of
     *        locations defined in terms of their geographic coordinates.
     *        Paths representing self-intersecting polygons are not supported.
     *        Such paths are not rendered on the map.
     */
    void SetPath(const GeoCoordinateList& path);

    /**
     * This method appends the location of a new vertex to the polyline path.
     *
     * Note that self-intersecting polygons are not supported, therefore, if the
     * given polygon should become self-intersecting as a result of this
     * operation, it cannot be rendered on the map.
     * 
     * @param rCoord A constant reference to an object specifying the geographic
     *        coordinates of a new vertex to be added to the path.
     */
    void AppendToPath(const GeoCoordinates& rCoord);

    /**
     * This method retrieves the path of the polygon, which is a list of
     * objects containing the geographic coordinates of its vertices.
     * 
     * @return A reference to an object containing a list of vertices defined
     *        in terms of their geographic coordinates.
     */
    GeoCoordinateList GetPath() const;

    /**
     * This typedef defines a function object as a type. The function object can
     * be called when the path of the polygon has changed. A function object of
     * this type returns <code>void</code> and receives a constant reference to
     * a <code>GeoMapObject</code> as an argument.
     */
    typedef std::tr1::function<void (const GeoMapObject&)> PathChangedFunctor;

    /**
     * This method sets a callback to be invoked when the polygon path has
     * changed. 
     * 
     * @param pathChanged A function object to be called when the path has
     *        changed. 
     */
    void SetPathChangedNotifier(PathChangedFunctor pathChanged);

    /**
     * This method retrieves the bounding box of the polygon.
     * 
     * @return An object encapsulating the bounding box of the given polygon
     *        object. 
     */
    GeoBoundingBox GetBoundingBox() const;

    /**
     * This method retrieves the current value of the polygon fill color.
     * 
     * @return An object encapsulating the fill color.
     */
    Tizen::Maps::Color GetFillColor() const;

    /**
     * This method sets the current value of the polygon fill color.
     * 
     * @param fillColor An object encapsulating the fill color.
     */
    void SetFillColor(const Tizen::Maps::Color& fillColor);

    /**
     * This typedef defines a fill-color-changed function object as a
     * type. The function object can be called when the polygon fill color
     * has changed. A function object of this type returns <code>void</code> and
     * receives a constant reference to a <code>GeoMapObject</code> as an
     * argument.
     */
    typedef std::tr1::function<void (const GeoMapObject&)> FillColorChangedFunctor;

    /**
     * This method sets a callback to be invoked when the polygon fill color
     * has changed.
     * 
     * @param fillColorChanged A function object to be called when the polygon
     *        fill color has changed.
     */
    void SetFillColorChangedNotifier(FillColorChangedFunctor fillColorChanged);

    /**
     * This method retrieves the object type of the given polygon.
     * 
     * @return A member of the enumerated data type indicating the type of the
     *        given polygon object.
     */
    Type GetType() const;

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
   virtual bool IsValid() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoMapObjectPolygon);

    class GeoMapObjectPolygonImpl;
    GeoMapObjectPolygonImpl* m_impl;
};

HERE_MAPS_END_NAMESPACE

#endif
