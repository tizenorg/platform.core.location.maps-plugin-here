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

#ifndef LOCATION_H
#define LOCATION_H

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

class Address;
class GeoCoordinates;
class GeoBoundingBox;

/** 
 *  This class represents the standard set of basic location information.
 *
 *  This includes the address, coordinates and map view.
 *
 */
class EXPORT_API GeoLocation
{
public:
    /**
     * This enumeration defines identifiers for location types.
     */
    enum LocationType
    {
        LT_Unknown = -1, ///< Indicates an unknown location type.
        LT_Point,        ///< Indicates that the location is a point.
        LT_Area,         ///< Indicates that the location is an area.
        LT_Line          ///< Indicates that the location is a line. 
    };

    /**
     * This method is the default constructor.
     */
    GeoLocation();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs A constant reference to an instance of
     *        <code>GeoLocation</code> whose contents are to be copied into
     *        the object being created.
     */
    GeoLocation(const GeoLocation& rRhs);

    /**
     * This method is the destructor.
     */
    ~GeoLocation();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs A constant reference to an instance of
     *        <code>GeoLocation</code> whose contents are to be copied into
     *        the given instance.
     */
    GeoLocation& operator=(const GeoLocation& rRhs);

    /**
     * This method sets the address of the location. 
     *
     * @param rAddress A constant reference to an object containing an address.
     */
    void SetAddress(const Address& rAddress);

    /**
     * This method retrieves the address of the location. 
     *
     * @return A constant reference to an object containing an address.
     */
    const Address& GetAddress() const;

    /**
     * This method sets the label for the location. 
     *
     * @param sLabel A constant reference to an object containing the value of
     *        the label.
     */
    void SetLabel(const String& sLabel);

    /**
     * This method retrieves the label for the location. 
     *
     * @return A constant reference to an object containing the value of
     *        the label.
     */
    const String& GetLabel() const;

    /**
     * This method sets the display position of the location. The display
     * position contains the coordinates at which to place a marker indicating
     * the given location on the map. 
     *
     * @param rCoord A constant reference to an object containing the geographic
     *        coordinates of the display position.
     */
    void SetDisplayPosition(const GeoCoordinates& rCoord);

    /**
     * This method retrieves the display position of the location. The display
     * position contains the coordinates at which to place a marker indicating
     * the given location on the map. 
     *
     * @return A constant reference to an object containing the geographic
     *        coordinates of the display position.
     */
    const GeoCoordinates& GetDisplayPosition() const;

    /**
     * This method appends the navigation position. A navigation position
     * contains the coordinates of a potential route waypoint. It is used for
     * routes that pass through the given location. 
     *
     * @param rCoord A constant reference to an object containing the geographic
     *        coordinates of the navigation position.
     */
    void AppendNavigationPosition(const GeoCoordinates& rCoord);

    /**
     * This method retrieves the number of navigation positions that have been set. 
     *
     * @return An integer indicating the number of navigation positions.
     */
    size_t GetNumNavigationPositions() const;

    /**
     * This method retrieves the navigation position from the index specified by
     * the caller. A navigation position contains the coordinates of a potential
     * route waypoint. It is used for routes that pass through the given
     * location.
     * 
     * @param idx A value specifying the index into an array of navigation
     *        positions. 
     *
     * @return A constant pointer to an object containing the geographic
     *        coordinates of the display position.
     */
    const GeoCoordinates* GetNavigationPosition(size_t idx) const;

    /**
     * This method sets the map view of the location. 
     *
     * @param rBbox A constant reference to an object that defines the map view
     *        as a bounding box.
     */
    void SetMapView(const GeoBoundingBox& rBbox);

    /**
     * This method retrieves the map view of the location. 
     *
     * @return A constant reference to an object that defines the map view
     *        as a bounding box.
     */
    const GeoBoundingBox& GetMapView() const;

    /**
     * This method sets the id of the location. 
     *
     * @param sLocationId A constant reference to a string containing the
     *        location id.
     */
    void SetLocationId(const String& sLocationId);

    /**
     * This method retrieves the id of the location. 
     *
     * @return A constant reference to a string containing the
     *        location id.
     */
    const String& GetLocationId() const;

    /**
     * This method sets the location type. 
     *
     * @param aType A numeric value indicating the location type.
     */
    void SetLocationType(LocationType aType);

    /**
     * This method sets the location type. 
     *
     * @param sType A constant reference to string identifying the location
     *        type. The supported values are "area", "point", and "line".
     */
    void SetLocationType(const String& sType);

    /**
     * This method retrieves the location type. 
     *
     * @return A numeric value indicating the location type.
     */
    LocationType GetLocationType() const;

private:
    class GeoLocationImpl;
    GeoLocationImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
