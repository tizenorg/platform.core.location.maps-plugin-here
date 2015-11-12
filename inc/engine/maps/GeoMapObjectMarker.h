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

#ifndef MAPOBJECTMARKER_H
#define MAPOBJECTMARKER_H

#include "common/HereMaps_global.h"
#ifndef TIZEN_MIGRATION
#include <FGraphics.h>
#endif

#include "maps/GeoMapObject.h"
#ifdef TIZEN_MIGRATION
#include "graphic/Dimension.h"
#include "graphic/Point.h"
#include "graphic/Bitmap.h"
#include "graphic/FloatPoint.h"
#endif

HERE_MAPS_BEGIN_NAMESPACE

class GlTexture;
class GeoCoordinates;

/**
 * This class encapsulates a map marker object that indicates a location 
 * with an image (icon).
 *
 * \ingroup maps
 */
class EXPORT_API GeoMapObjectMarker : public GeoMapObject
{
public:

    /**
     * This method is the default constructor.
     */
    GeoMapObjectMarker();

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~GeoMapObjectMarker();

    /**
     * This method retrieves the object type.
     * 
     * @return A member of the enumerated data type indicating the type of the
     *        given object.
     */
    virtual Type GetType() const;

    /**
     * This method retrieves the object bounding box.
     * 
     * @return An object encapsulating the bounding box of the given object.
     */
    virtual GeoBoundingBox GetBoundingBox() const;

    /**
     * This method sets the position of the given object.
     *
     * @param rCoord A constant reference to an object containing the geographic
     *        coordinates of the position of the given object.
     */
    virtual void SetPosition(const GeoCoordinates& rCoord);

    /**
     * This method retrieves the position of the given object.
     *
     * @return A constant reference to an object containing the geographic
     *        coordinates of the position of the given object.
     */
    const GeoCoordinates& GetPosition() const;

    /**
     * This method sets the marker image (icon).
     * 
     * @param rBitmap A constant reference to an object encapsulating the icon
     *        image.  
     */
    void SetBitmap(const Tizen::Maps::Bitmap& rBitmap);

    /**
     * This method retrieves the width of the bitmap (icon). 
     * 
     * @return A value indicating the width of the bitmap (icon) in pixels.
     */
    unsigned int GetWidth() const;

    /**
     * This method retrieves the height of the bitmap (icon). 
     * 
     * @return A value indicating the height of the bitmap (icon) in pixels.
     */
    unsigned int GetHeight() const;

    /**
     * This method sets a value that defines the point on the marker bitmap that
     * touches the map. The point is calculated relative to the top-left corner
     * of the bitmap.
     * 
     * @param rOrigin A floating point value defining the origin.
     */
    void SetMarkerOrigin(const Tizen::Maps::FloatPoint& rOrigin);

    /**
     * This method retrieves a value that represents the point on the marker
     * bitmap that "touches" the map. The point is calculated relative to the
     * top-left corner of the bitmap.
     * 
     * @return A floating point value defining the bitmap origin.
     */
    Tizen::Maps::FloatPoint GetMarkerOrigin() const;

    /**
     * This method retrieves a value that represents the point on the marker
     * bitmap that "touches" the map. The point is calculated relative to the
     * top-left corner of the bitmap.
     * 
     * @return An object containing the pixel coordinates of the bitmap origin
     *        relative to the top-left corner of the bitmap.
     */
    Tizen::Maps::Point GetMarkerOriginInPx() const;

    /**
     * This method retrieves the marker bitmap as a GL texture.
     * 
     * @return A pointer to the GL texture of the bitmap.
     */
    GlTexture* GetGlTexture() const;

    /**
     * This method checks if the object is valid (it geographic location is
     * defined). 
     *
     * @return visible A Boolean, <code>true</code> if the object is valid,
     *        otherwise <code>false</code>.
     */
    virtual bool IsValid() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoMapObjectMarker);

    class GeoMapObjectMarkerImpl;
    GeoMapObjectMarkerImpl* m_impl;
};

HERE_MAPS_END_NAMESPACE

#endif
