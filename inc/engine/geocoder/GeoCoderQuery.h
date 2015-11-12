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

#ifndef GEOCODERQUERY_H_
#define GEOCODERQUERY_H_

#include "common/HereMaps_global.h"

#include "geocoder/GeoCoderQueryBase.h"

HERE_MAPS_BEGIN_NAMESPACE

class Address;
class GeoCoderReply;
class GeoBoundingBox;
class ApplicationContext;
class GeoCoderQueryListener;

/**
 * This class represents a geocoding query.
 *
 * Instances of this class are used to obtain the geographic coordinates of
 * locations on the basis of an address (complete or partial) and/or a free text
 * search string.
 * 
 * @ingroup geocoding
 */
class EXPORT_API GeoCoderQuery : public GeoCoderQueryBase
{
public:

    /**
     * This is the default constructor. 
     */
    GeoCoderQuery();

    /**
     * This method is a constructor.
     * 
     * @param rAddress A constant reference to an object providing the details
     *        of an address to use in the query.
     */
    GeoCoderQuery(const Address& rAddress);

    /**
     * This method is a constructor.
     * 
     * @param rAddress A constant reference to an object that provides the details
     *        of an address to use in the query.
     * 
     * @param sSearch A constant reference to a string containing the search
     *        text to use in the query. 
     */
    GeoCoderQuery(const Address& rAddress, const String& sSearch);

    /**
     * This method is a constructor.
     * 
     * @param sSearch A constant reference to a string containing the search
     *        text to use in the query. 
     */
    GeoCoderQuery(const String& sSearch);

    /**
     * This method is a virtual destructor.
     */
    virtual ~GeoCoderQuery();

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
     * This method sets the address to be used in the query. 
     * 
     * @param rAddress A constant reference to an object providing the details
     *        of an address to use in the query.
     */
    void SetAddress(const Address& rAddress);

    /**
     * This method sets the search text to be used in the query.
     * 
     * @param sSearch A constant reference to a string containing the search
     *        text to use in the query. 
     */
    void SetSearchtext(const String& sSearch);

    /**
     * This method sets the map view using the bounding box object provided by
     * the caller. The map view is a soft filter, which means that the
     * response includes relevant results from within the map view, but also
     * possibly from a wider area, and even relevant global results are
     * also returned.
     *
     * @param rMapView A constant reference to a bounding box object that
     *        defines the map view in terms of the geographic coordinates of
     *        the top-left and bottom-right corners.
     */
    void SetMapView(const GeoBoundingBox& rMapView);

    /**
     * This method sets the bounding box to be used in the query. The bounding
     * box is a hard filter in that the response includes relevant results from
     * within the area it defines. 
     * 
     * @param A constant reference to an instance of
     *        <code>GeoBoundingBox</code>, representing a geographic area within
     *        which to perform the search.
     */
    void SetBoundingBox(const GeoBoundingBox& rBoundingBox);

    /**
     * This method sets the location identifier to be used in the query. 
     * 
     * @param sID a constant reference to a string containing the location
     *        identifier. 
     */

    void SetLocationId(const String& sId);

    /**
     * This method attempts to establish a connection
     * with the server and then, if the connection has been established, it
     * builds and submits a query.     
     * 
     * @param rListener A reference to an object that is to be notified when
     *        the reply to the query has arrived from the server.
     * 
     * @param pUserData A pointer to user data to be passed back within the
     *        corresponding reply object.
     *
     * @return Identifier of issued request.
     */
    RestItemHandle::RequestId Execute(GeoCoderQueryListener& rListener, Tizen::Maps::HereObject* pUserData = NULL) const;

    /**
     * This method returns the base URI to be used for all subsequent
     * geo coder queries.
     *
     * @return A string containing the base URI.
     */
    String GetBaseUri() const;

    /**
     * This method returns the base URI to be used for all subsequent
     * geo coder queries.
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
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoCoderQuery);

    class GeoCoderQueryImpl;
    GeoCoderQueryImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif /* GEOCODERQUERY_H_ */
