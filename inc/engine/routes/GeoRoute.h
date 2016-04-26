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

#ifndef GEOROUTE_H
#define GEOROUTE_H

#include <vector>

#include "common/HereMaps_global.h"
#include "common/GeoCoordinates.h"
#include "routes/GeoRouteQuery.h"
#include "routes/RouteSegment.h"

HERE_MAPS_BEGIN_NAMESPACE

class RouteSegment;
class GeoBoundingBox;

class GeoRoute;

/** 
 * This typedef defines a list (vector) of instances of <code>GeoRoute</code> as
 * a type.
 * 
 * \ingroup routes
 */
typedef std::vector<GeoRoute> GeoRouteList;

/**
 * This class encapsulates a route. Instances of the class are data objects. The
 * information they contain can be used to draw routes on the map. 
 * 
 * A route object contains member variables that represent:
 * <ul>
 * 
 * <li> route segments - sections of the route encapsulated as instances of
 *      <code>RouteSegment</code></li> 
 * 
 * <li> maneuvers - instances of <code>Maneuver</code></li> that contain
 *      navigation instructions for the person following the route, indicating
 *      how to continue from one section of the route to the next</li>
 * 
 * <li> route geometry - a list of instances of <code>GeoCoordinates</code></li>
 *      that contains the point objects with the coordinates of the geographical
 *      locations through which the route passes</li>
 * 
 * <li> duration - the length of time required to travel the route from start
 *      to finish</li>
 * 
 * </ul>
 * 
 * Note that the above list is indicative, rather than comprehensive. 
 */
class EXPORT_API GeoRoute
{
public:

   /**
    * This is the default constructor.
    */
    GeoRoute();

   /**
    * This method is the copy constructor.
    * 
    * @param rRhs An object whose contents are to be copied to the instance
    *        being created.
    */
    GeoRoute(const GeoRoute& rRhs);

   /**
    * This method is the destructor.
    */
    ~GeoRoute();

    /**
     * This method sets the id of the route object.
     * 
     * @param rId A constant reference to a string containing the unique id of
     *        the route object.
     */
    void SetRouteId(const String& rId);

    /**
     * This method retrieves the id of the route object.
     * 
     * @return A string containing the unique id of
     *        the route object.
     */
    String GetRouteId() const;

    /**
     * This method sets class property holding the request used to obtain the
     * route data. 
     * 
     * @param rRequest A constant reference to an object that encapsulates the
     *        query used to obtain the route data.
     */
    void SetRequest(const GeoRouteQuery& rRequest);

    /**
     * This method retrieves the value class property holding the request used
     * to obtain the route data.
     * 
     * @return An object that encapsulates the query used to obtain the route
     *       data.
     */
    GeoRouteQuery GetRequest() const;

    /**
     * This method sets a property that holds the bounding box enclosing
     * the route. The bounding box is defined by the geographic coordinates of
     * its top-left and bottom-right corners.  
     * 
     * @param rBounds A constant reference to an object containing the bounding
     *        box.
     */
    void SetBounds(const GeoBoundingBox& rBounds);

    /**
     * This method retrieves the value of a class property that holds the
     * bounding box enclosing the route. The bounding box is defined by the
     * geographic coordinates of its top-left and bottom-right corners.
     * 
     * @return An object containing the bounding box. 
     */
    GeoBoundingBox GetBounds() const;

    /**
     * This method sets a class property that holds the list of segments of the
     * route.
     * 
     * @param vRouteSegmentList A constant reference to an object that defines
     *        the first segment of the route.
     */
    void SetRouteSegmentList(const RouteSegmentList& vRouteSegmentList);

    /**
     * This method retrieves the value of a class property that holds the list of
     * segments of the route.  
     * 
     * @return An object that defines the list of segments of the route.
     */
     RouteSegmentList GetRouteSegmentList() const;

    /**
     * This method sets a class property that holds the time required to travel
     * the length of the route. 
     * 
     * @param aSecs An integer value specifying the time required to travel the
     *        length of the route in seconds.
     */
    void SetTravelTime(int aSecs);

    /**
     * This method retrieves the value of a class property that holds the time
     * required to travel the length of the route.
     * 
     * @return An integer value specifying the time required to travel the
     *        length of the route in seconds.
     */
    int GetTravelTime() const;

#ifdef TIZEN_MIGRATION
    /**
     * This method sets a class property that holds the time required to traffic
     * the length of the route.
     *
     * @param aSecs An integer value specifying the time required to traffic the
     *        length of the route in seconds.
     */
    void SetTrafficTime(int aSecs);

    /**
     * This method retrieves the value of a class property that holds the time
     * required to traffic the length of the route.
     *
     * @return An integer value specifying the time required to traffic the
     *        length of the route in seconds.
     */
    int GetTrafficTime() const;
#endif

    /**
     * This method sets a class property that holds the length of the route --
     * the total distance to travel between the start and end points of the
     * route.
     * 
     * @param aDistance A value specifying the length of the route in meters. 
     */
    void SetDistance(double aDistance);

    /**
     * This method retrieves the value of a class property that holds the length
     * of the route -- the total distance to travel between the start and end
     * points of the route.
     * 
     * @return A value specifying the length of the route in meters. 
     */
    double GetDistance() const;

    /**
     * This method sets a class property indicating the travel mode for which
     * the route was calculated.
     * 
     * @param aTravelMode A value indicating the mode of travel for the route. 
     */
    void SetTravelMode(GeoRouteQuery::TravelMode aTravelMode);

    /**
     * This method retrieves the value of a class property indicating the travel
     * mode for which the route was calculated.
     * 
     * @return A value indicating the mode of travel for the route. 
     */
    GeoRouteQuery::TravelMode GetTravelMode() const;

    /**
     * This method sets a class property that defines the geometry of the route
     * (it holds the coordinates of the points through which the route passes,
     * the vertices of the route).
     * 
     * @param rPath A constant reference to an object containing the geographic
     *       coordinates of the points through which the route passes (the route
     *       vertices).
     */
    void SetPath(const GeoCoordinateList& rPath);

    /**
     * This method retrieves the value of a class property that defines the
     * geometry of the route (it holds the coordinates of the points through
     * which the route passes, the vertices of the route).
     * 
     * @return An object containing the geographic coordinates of the points
     *       through which the route passes (the route vertices).
     */
    GeoCoordinateList GetPath() const;

    /** 
     * This is the assignment operator.
     * 
     * @param rRhs A constant reference to an object whose properties are to be
     *       copied to the given instance of the class.
     * 
     * @return A reference to the given instance of the class after its member
     *       elements have been updated.
     */ 
    GeoRoute& operator = (const GeoRoute& rRhs);

private:
    class GeoRouteImpl;
    GeoRouteImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif /* GEOROUTE_H */
