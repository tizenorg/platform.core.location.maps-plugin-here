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

#ifndef MAPOBJECTPOLYLINE_H
#define MAPOBJECTPOLYLINE_H

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
 * This class encapsulates a map polyline object. A polyline is a line that
 * connects a number of points on the map. Its properties include stroke color
 * and thickness.
 *
 * \ingroup maps
 */
class EXPORT_API GeoMapObjectPolyline : public GeoMapObject
{
public:

    /**
     * This method is the default constructor.
     */
    GeoMapObjectPolyline();

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~GeoMapObjectPolyline();

    /**
     * This method sets the path of the polyline, which is a list of locations
     * that the polyline connects. 
     * 
     * @param path A constant reference to an object containing a list of
     *        locations defined in terms of their geographic coordinates.
     */
    void SetPath(const GeoCoordinateList& path);

    /**
     * This method appends the location of a new vertex to the polyline path.
     * 
     * @param aCoord A constant reference to an object specifying the geographic
     *        coordinates of a new vertex to be added to the path.
     */
    void AppendToPath(const GeoCoordinates& aCoord);

    /**
     * This method retrieves the path of the polyline, which is a list of
     * locations that the polyline connects.
     * 
     * @return A reference to an object containing a list of locations defined
     *        in terms of their geographic coordinates.
     */
    GeoCoordinateList GetPath() const;

    /**
     * This typedef defines a function object as a type. The function object can
     * be called when the polyline path has changed. A function object of this
     * type returns <code>void</code> and receives a constant reference to a
     * <code>GeoMapObject</code> as an argument.
     */
    typedef std::tr1::function<void (const GeoMapObject&)> PathChangedFunctor;

    /**
     * This method sets a callback to be invoked when the polyline path has
     * changed. 
     * 
     * @param pathChanged A function object to be called when the path has
     *        changed. 
     */
    void SetPathChangedNotifier(PathChangedFunctor pathChanged);

    /**
     * This method retrieves the current value of the polyline stroke color.
     * 
     * @return An object encapsulating the stroke color.
     */
    Tizen::Maps::Color GetStrokeColor() const;

    /**
     * This method sets the value of the polyline stroke color.
     * 
     * @param strokeColor A constant reference to an object encapsulating the
     *        stroke color. 
     */
    void SetStrokeColor(const Tizen::Maps::Color& strokeColor);

    /**
     * This typedef defines a function object as a type. The function object can
     * be called when the polyline stroke color has changed. A function object
     * of this type returns <code>void</code> and receives a constant reference
     * to a <code>GeoMapObject</code> as an argument.
     */
    typedef std::tr1::function<void (const GeoMapObject&)> StrokeColorChangedFunctor;

    /**
     * This method sets a callback to be invoked when the polyline stroke color
     * has changed.
     * 
     * @param strokeColorChanged A function object to be called when the polyline
     *        stroke color has changed.
     */
    void SetStrokeColorChangedNotifier(StrokeColorChangedFunctor strokeColorChanged);
    
    /**
     * This method retrieves a value indicating the polyline stroke thickness in
     * pixels.
     * 
     * @return A value indicating the stroke thickness in pixels.
     */
    int GetStrokeThickness() const;
    
    /**
     * This method sets a value indicating the polyline stroke thickness in
     * pixels.
     * 
     * @strokeThickness A value indicating the stroke thickness in pixels.
     */
    void SetStrokeThickness(int strokeThickness);

    /**
     * This typedef defines a function object as a type. The function object can
     * be called when the polyline stroke thickness has changed. A function
     * object of this type returns <code>void</code> and receives a constant
     * reference to a <code>GeoMapObject</code> as an argument.
     */
    typedef std::tr1::function<void (const GeoMapObject&)> StrokeThicknessChangedFunctor;

    /**
     * This method sets a callback to be invoked when the polyline stroke
     * thickness has changed.
     * 
     * @param strokeThicknessChanged A function object to be called when the polyline
     *        stroke thickness has changed.
     */
    void SetStrokeThicknessChangedNotifier(StrokeThicknessChangedFunctor strokeThicknessChanged);

    /**
     * This method retrieves the bounding box of the polyline.
     * 
     * @return An object encapsulating the bounding box of the given polyline
     *        object. 
     */
    GeoBoundingBox GetBoundingBox() const;

    /**
     * This method retrieves the object type of the given polyline.
     * 
     * @return A member of the enumerated data type indicating the type of the
     *        given polyline object.
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
    * This method checks if the object was built with legal input. A valid
    *  polyline must have a path that contains of at least two vertices.
    *
    * @return visible A Boolean, <code>true</code> if the object is valid,
    *        otherwise <code>false</code>.
    */
    virtual bool IsValid() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoMapObjectPolyline);

    class GeoMapObjectPolylineImpl;
    std::auto_ptr<GeoMapObjectPolylineImpl> m_impl;
};

HERE_MAPS_END_NAMESPACE

#endif
