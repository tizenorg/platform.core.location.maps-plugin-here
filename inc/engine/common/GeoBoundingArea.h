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

#ifndef GEOBOUNDINGAREA_H
#define GEOBOUNDINGAREA_H

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoCoordinates;

/**
 * This class encapsulates a bounding area defined in terms of the geographic
 * coordinates of its top left and bottom right corners.
 *
 * The virtual methods of the class must be implemented by derived classes.
 */
class EXPORT_API GeoBoundingArea
{
public:
    /**
     * This enumeration defines identifiers for types of bounding areas. 
     */
    enum AreaType
    {
        AT_BoxType,   ///< Indicates that the bounding area is a box.
        AT_CircleType ///< Indicates that the bounding area is a circle.
    };

    /**
     * This method is a (virtual) destructor.
     */
    virtual ~GeoBoundingArea()
    {
    }

    /**
     * This method retrieves a value indicating what type of area the given
     * object represents.
     *
     * @return A value indicating the area type.
     */
    virtual AreaType GetType() const = 0;

    /**
     * This method checks if the given bounding area contains the location
     * whose coordinates are provided by the caller.
     * 
     * @param rCoordinate An object containing the geographic coordinates of the
     *        location to check.
     *
     * @return <code>true</code> if the location lies within the given bounding
     *        box, otherwise <code>false</code>.
     */
    virtual bool Contains(const GeoCoordinates& rCoordinate) const = 0;
};

HERE_MAPS_END_NAMESPACE

#endif /* GEOBOUNDINGAREA_H */