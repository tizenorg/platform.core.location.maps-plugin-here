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

#ifndef GEOBOUNDINGCIRCLE_H
#define GEOBOUNDINGCIRCLE_H

#include "common/HereMaps_global.h"
#include "common/GeoBoundingArea.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoCoordinates;

/**
 * This class encapsulates a bounding circle defined in terms of the geographic
 * coordinates of its center and a radius. 
 */
class EXPORT_API GeoBoundingCircle : public GeoBoundingArea
{
public:
    /**
     * This method is the default constructor. 
     */
    GeoBoundingCircle();

    /**
     * This method is a copy constructor. 
     * 
     * @param rRhs A constant reference to an object whose contents are to be
     *        used to set the properties of a new instance of this class. 
     */
    GeoBoundingCircle(const GeoBoundingCircle& rRhs);

    /**
     * This method is a constructor that creates a new instance, using the
     * coordinates of the center of the circle and the length of its radius.
     * 
     * @param rCenter A constant reference to an object providing the
     *        geographic coordinates of the center of the given
     *        bounding circle.
     * 
     * @param rRadius A value providing the length of the radius in meters.
     */
    GeoBoundingCircle(const GeoCoordinates& rCenter, double rRadius);

    /**
     * This method is the destructor. 
     */
    ~GeoBoundingCircle();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs A constant reference to the right-hand object whose contents
     *        are to be copied to the given instance of the class.
     * 
     * @return A reference to the given instance of the class after the
     *        assignment. 
     */
    GeoBoundingCircle& operator = (const GeoBoundingCircle& rRhs);

    /**
     * This method sets the coordinates of the center of the given
     * instance of <code>GeoBoundingCircle</code>.
     * 
     * @param A constant reference to an object containing the new geographic
     *        coordinates of the center of the bounding circle.
     */
    void SetCenter(const GeoCoordinates& rCenter);

    /**
     * This method retrieves the coordinates of the center of the given
     * instance of <code>GeoBoundingCircle</code>.
     * 
     * @return A constant reference to an object containing the geographic
     *        coordinates of the center of the bounding circle.
     */
    const GeoCoordinates& GetCenter() const;

    /**
     * This method sets the radius of the given
     * instance of <code>GeoBoundingCircle</code>.
     * 
     * @param rRadius A value providing the length of the radius in meters.
     */
    void SetRadius(double aRadius);

    /**
     * This method retrieves the radius of the given
     * instance of <code>GeoBoundingCircle</code>.
     * 
     * @return A value providing the length of the radius in meters.
     */
    double GetRadius() const;


    /**
     * This method retrieves a value indicating the area type applicable to the
     * given object.
     * 
     * @return A value indicating the area type. 
     */
    AreaType GetType() const;

    /**
     * This method checks if the given bounding circle contains the location
     * defined by the object provided by the caller.
     * 
     * @param rCoordinate An object containing the geographic coordinates of the
     *        location to check. 
     * 
     * @return <code>true</code> if the location lies within the given bounding
     *        box, otherwise <code>false</code>. 
     */
    bool Contains(const GeoCoordinates& rCoordinate) const;

private:
    class GeoBoundingCircleImpl;
    GeoBoundingCircleImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif /* GEOBOUNDINGCIRCLE_H */
