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

#ifndef GEOCOORDINATES_H
#define GEOCOORDINATES_H

#include <vector>

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoCoordinates;
typedef std::vector<GeoCoordinates> GeoCoordinateList;

/**
 * This class represents a geographic location defined in terms of WGS84
 * coordinates. The coordinates (latitude, longitude and altitude) are stored
 * as doubles.
 */
class EXPORT_API GeoCoordinates
{
public:
    static const double LATITUDE_RANGE;
    static const double LONGITUDE_RANGE;

    /**
     * This method is the default constructor.
     */
    GeoCoordinates();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs A constant reference to an instance of
     *        <code>GeoCoordinates</code> whose contents are to be copied into
     *        the object being created.
     */
    GeoCoordinates(const GeoCoordinates& rRhs);

    /**
     * This method is a constructor.
     *
     * @param fLatitude A value specifying WGS84 latitude in degrees.
     * 
     * @param fLongitude A value specifying WGS84 longitude in degrees.
     * 
     * @param fAltitude A value specifying the altitude in meters, 
     *        as height above the WGS84 geoid; optional, the default
     *        is 0.
     */
    GeoCoordinates(double fLatitude, double fLongitude, double fAltitude = 0.);

    /**
     * This method is the destructor.
     */
    ~GeoCoordinates();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs A constant reference to an instance of
     *        <code>GeoCoordinates</code> whose contents are to be copied into
     *        the given instance.
     */
    GeoCoordinates& operator=(const GeoCoordinates& rRhs);
    
    /**
     * This method sets the value of longitude. 
     *
     * @param fValue A value specifying WGS84 longitude in degrees.  
     */
    void SetLongitude(double fValue);
    
    /**
     * This method retrieves the value of longitude. 
     *
     * @return A value specifying WGS84 longitude in degrees.  
     */
    double GetLongitude() const;

    /**
     * This method sets the value of latitude. 
     *
     * @param fValue A value specifying WGS84 latitude in degrees.  
     */
    void SetLatitude(double fValue);

    /**
     * This method retrieves the value of latitude. 
     *
     * @return A value specifying WGS84 latitude in degrees.  
     */
    double GetLatitude() const;

    /**
     * This method sets the value of altitude. 
     *
     * @param fValue  A value representing altitude as height above
     *        the WGS84 geoid in meters.
     */
    void SetAltitude(double fValue);

    /**
     * This method retrieves the value of altitude. 
     *
     * @return  A value representing altitude as height above
     *        the WGS84 geoid in meters.
     */
    double GetAltitude() const;
    
    /** 
     * This method checks if the given object is valid. 
     * 
     * The object is valid if the latitude and longitude have been set,
     * latitude is in the range [-85.015113..85.015113] (degrees) and longitude is
     * in the range [-180..180] (degrees).
     * 
     * @return <code>true</code> if the object is valid, otherwise
     *        <code>false</code>.
     */
    bool IsValid() const;

    /**
     * This operator checks if the given object is identical to the right-hand
     * object. 
     * 
     * @param other A constant reference to an object which is to be compared to
     *        the given instance. 
     * 
     * @return <code>true</code> if the two objects are identical, otherwise
     *        <code>false</code>. 
     */
    bool operator == (const GeoCoordinates& other) const;

    /** 
     * This operator checks if the given object differs (is not equal to) the
     * right-hand object.
     * 
     * @param other A constant reference to an object which is to be compared to
     *        the given instance. 
     * 
     * @return <code>true</code> if the two objects are different, otherwise
     *        <code>false</code>. 
     */
    bool operator != (const GeoCoordinates& other) const;    

private:
    class GeoCoordinatesImpl;
    GeoCoordinatesImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
