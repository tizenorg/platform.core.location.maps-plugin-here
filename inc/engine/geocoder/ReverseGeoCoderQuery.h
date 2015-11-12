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

#ifndef REVERSEGEOCODERQUERY_H
#define REVERSEGEOCODERQUERY_H

#include "common/HereMaps_global.h"

#include "geocoder/GeoCoderQueryBase.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoCoderReply;
class GeoCoordinates;
class GeoCoderQueryListener;

/**
 * This class represents a reverse geocoding query.
 *
 * Instances of the class are used to obtain an address (or a set of addresses)
 * corresponding to a set of geographic coordinates. 
 * 
 * @ingroup geocoding
 */
class EXPORT_API ReverseGeoCoderQuery : public GeoCoderQueryBase
{
public:
    /** 
     * This enumeration defines identifiers for reverse geocoding modes. A mode
     * indicates whether addresses are to be returned or 
     * administrative area names (such as city, county, state, country).
     */ 
    enum ReverseMode
    {
        RM_RetrieveAreas,    ///< Indicates that administrative area names are to be retrieved. 
        RM_RetrieveAddresses ///< Indicates that addresses are to be retrieved. 
    };

    /** 
     * This method is the default constructor. 
     */
    ReverseGeoCoderQuery();

    /** 
     * This method is a constructor that initializes the query with the location
     * to reverse-geocode and the mode. 
     * 
     * @param rCoordinate A constant reference to an object containing the geographic
     *        coordinates of the location to reverse-geocode.
     * 
     * @param aMode A value indicating the reverse geocoding mode to use.
     */
    ReverseGeoCoderQuery(const GeoCoordinates& rCoordinate, ReverseMode aMode);

    /** 
     * This method is a constructor that initializes the query with the location
     * to reverse-geocode, the mode and the radius within which to conduct the
     * search.  
     * 
     * @param rCoordinate A constant reference to an object containing the geographic
     *        coordinates of the location to reverse-geocode.
     * 
     * @param aMode A value indicating the reverse geocoding mode to use.
     * 
     * @param fRadius A float value indicating the radius (in meters) within
     *        which to search.
     */
    ReverseGeoCoderQuery(const GeoCoordinates& rCoordinate, ReverseMode aMode, float fRadius);

    /**
     * This method is the (virtual) destructor.
     */ 
    virtual ~ReverseGeoCoderQuery();

    /**
     * This method sets the properties defining a circular area within which a
     * search is to be conducted. The area is defined in terms of its center and
     * radius.
     *
     * @param rCoord A constant reference to an object containing the latitude
     *        and longitude of the center of the proximity area (search center).
     *
     * @param rRadius A value specifying the radius of the search area in meters.
     */
    void SetProximity(const GeoCoordinates& rCoord, float fRadius = 0);

    /**
     * This method detects whether coordinates/proximity (the center of search area
     * set or not).
     *
     * @return <code>true</code> if the proximity was set,
     *        otherwise <code>false</code>
     */
    bool HasProximity() const;

    /** 
     * This method sets the reverse geocoding mode to apply to the query.
     * 
     * @param aMode A value indicating the reverse geocoding mode to use.
     */
    void SetMode(ReverseMode aMode);

    /**
     * This method attempts to establish a connection
     * with the server and then, if the connection has been established, it
     * builds and submits a query.     
     * 
     * @param rListener A shared pointer to an object that is to be notified when
     *        the reply to the query has arrived from the server.
     * 
     * @param pUserData A pointer to user data to be echoed in the reply object.
     *
     * @return A value representing the identifier of the issued request.
     */
    RestItemHandle::RequestId Execute(GeoCoderQueryListener& rListener, Tizen::Maps::HereObject* pUserData = NULL) const;

    /**
     * This method returns the base URI to be used for all subsequent
     * reverse geocoder queries.
     *
     * @return A string containing the base URI.
     */
    String GetBaseUri() const;

    /**
     * This method returns the base URI to be used for all subsequent
     * reverse geocoder queries.
     *
     * @param sUri A constant reference to a string containing the base URI.
     */
    void SetBaseUri(const String& sUri);

private:
    /**
     * This method creates the URI for the request.
     *
     * @return URI request string.
     */
    String CreateUri() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(ReverseGeoCoderQuery);

    class ReverseGeoCoderQueryImpl;
    ReverseGeoCoderQueryImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
