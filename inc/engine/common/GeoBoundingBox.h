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

#ifndef GEOBOUNDINGBOX_H
#define GEOBOUNDINGBOX_H

#include <vector>

#include "common/HereMaps_global.h"
#include "common/GeoBoundingArea.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoCoordinates;

class GeoBoundingBox;

/**
 * This typedef defines a vector of instances of <code>GeoBoundingBox</code> as
 * a type. 
 */
typedef std::vector<GeoBoundingBox> GeoBoundingBoxList;

/**
 * This class encapsulates a bounding box defined in terms of the geographic
 * coordinates of its top-left and bottom-right corners. 
 */
class EXPORT_API GeoBoundingBox : public GeoBoundingArea
{
public:
    /**
     * This method is the default constructor. 
     */
    GeoBoundingBox();

    /**
     * This method is a copy constructor. 
     * 
     * @param rRhs A constant reference to an object whose contents are to be
     *        used to populate the new instance of this class. 
     */
    GeoBoundingBox(const GeoBoundingBox& rRhs);

    /**
     * This method is a constructor that creates a new instance, using the
     * coordinates of the top-left and bottom=right corners provided by the
     * caller.
     * 
     * @param rTopLeft A constant reference to an object providing the
     *        geographic coordinates of the top-left corner of the given
     *        bounding box.
     * 
     * @param rBottomRight A constant reference to an object providing the
     *        geographic coordinates of the bottom-right corner of the given
     *        bounding box.
     */
    GeoBoundingBox(const GeoCoordinates& rTopLeft, const GeoCoordinates& rBottomRight);

    /**
     * This method constructs a rectangle from the coordinates of its boundaries.
     *
     * If <code>west</code> is larger than <code>east</code>, then the new
     * rectangle lies on the opposite side of the globe, i.e. +180 meridian.
     *
     * @param west A value indicating the minimum longitude.
     * @param east A value indicating the maximum longitude.
     * @param south A value indicating the minimum latitude.
     * @param north A value indicating the the maximum latitude.
     */
    GeoBoundingBox( double west, double east, double south, double north );

    /**
     * This method is the destructor. 
     */
    ~GeoBoundingBox();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs A constant reference to an object whose contents
     *        are to be copied to the given instance of the class.
     * 
     * @return A reference to the given instance of the class after the
     *        assignment. 
     */
    GeoBoundingBox& operator=(const GeoBoundingBox& rRhs);

    /**
     * This method sets the coordinates of the top-left corner of the given
     * instance of <code>GeoBoundingBox</code>.
     * 
     * @param A constant reference to an object containing the new geographic
     *        coordinates of the top-left corner of the bounding box.
     */
    void SetTopLeft(const GeoCoordinates& rCoord);

    /**
     * This method retrieves the coordinates of the top-left corner of the given
     * instance of <code>GeoBoundingBox</code>.
     * 
     * @return A constant reference to an object containing the geographic
     *        coordinates of the top-left corner of the bounding box.
     */
    const GeoCoordinates& GetTopLeft() const;

    /**
     * This method sets the coordinates of the bottom-right corner of the given
     * instance of <code>GeoBoundingBox</code>.
     * 
     * @param A constant reference to an object containing the new geographic
     *        coordinates of the bottom-right corner of the bounding box.
     */
    void SetBottomRight(const GeoCoordinates& rCoord);

    /**
     * This method retrieves the coordinates of the bottom-right corner of the
     * given instance of <code>GeoBoundingBox</code>.
     * 
     * @return A constant reference to an object containing the geographic
     *        coordinates of the bottom-right corner of the bounding box.
     */
    const GeoCoordinates& GetBottomRight() const;

    /**
     * This method calculates a bounding box that represents the union of the
     * given <code>GeoBoundingBox</code> and the instance provided by the
     * caller.
     * 
     * @param A constant reference to an object for which to calculate a union
     *        with the given instance of <code>GeoBoundingBox</code>.
     *
     * @return An object representing the union of two instances of
     *        <code>GeoBoundingBox</code>.
     */
    GeoBoundingBox Union(const GeoBoundingBox& rOther);

    /**
     * This method retrieves a value indicating the area type represented by the
     * given object.
     * 
     * @return A value indicating the area type. 
     */
    AreaType GetType() const;

    /**
     * This method checks if the given bounding box contains the location
     * provided by the caller.
     * 
     * @param rCoordinate An object containing the geographic coordinates of the
     *        location to check. 
     * 
     * @return <code>true</code> if the location lies within the given bounding
     *        box, otherwise <code>false</code>. 
     */
    bool Contains(const GeoCoordinates& rCoordinate) const;

    /**
     * This method checks if the coordinates of the given instance of
     * <code>GeoBoundingBox</code> are valid.
     *
     * @return Value <code>true</code> if the coordinates of the top-left and
     *        bottom-right corners are valid, otherwise <code>false</code>.
     */
    bool IsValid() const;

private:
    class GeoBoundingBoxImpl;
    GeoBoundingBoxImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
