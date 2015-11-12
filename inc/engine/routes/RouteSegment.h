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

#ifndef ROUTESEGMENT_H
#define ROUTESEGMENT_H

#include "common/HereMaps_global.h"
#include "common/GeoCoordinates.h"
#include "routes/Maneuver.h"

HERE_MAPS_BEGIN_NAMESPACE

class Maneuver;
class RouteSegmentImpl;

class RouteSegment;

/**
 * This typedef defines a vector of instances of <code>RouteSegment</code> as a
 * type.  
 * 
 * \ingroup routes
 */
typedef std::vector<RouteSegment> RouteSegmentList;


/**
 * This class encapsulates a route segment which is a section of a route between
 * two waypoints. A number of properties define a route segment, including the
 * time required to travel it, its length, path (geometry), and maneuvers.
 * 
 * \ingroup routes
 */
class EXPORT_API RouteSegment
{

public:
    /**
     * This method is the default constructor. It creates an invalid object,
     * with both travel time and distance set to zero. 
     */
    RouteSegment();

    /**
     * This method is a copy constructor that initializes a new instance of the
     * class, using the property values from the object supplied by the caller.
     * 
     * @param rRhs A constant reference to an object whose property values are to
     *        be used to initialize a new instance of <code>RouteSegment</code>.
     */
    RouteSegment(const RouteSegment& rRhs);

    /**
     * This method is the destructor. 
     */
    ~RouteSegment();

    /**
     * This is the assignment operator. 
     * 
     * @param rRhs A constant reference to an object whose property values are to
     *        be copied to the given instance of <code>RouteSegment</code>.
     * 
     * @return A reference to the given instance of the class after the
     *        assignment.
     */
    RouteSegment& operator = (const RouteSegment& rRhs);

    
    /**
     * This method checks if the given instance of the class is valid. A segment
     * is valid if, at a minimum, its path property is defined.
     * 
     * @return <code>true</code> if the object is valid, otherwise
     *        <code>false</code>. 
     */
    bool IsValid() const;

    /**
     * This method sets the route segment travel time. 
     * 
     * @param aSecs A value indicating the length of time required to travel the
     *        length of the route segment in seconds.
     */
    void SetTravelTime(int aSecs);

    /**
     * This method retrieves the route segment travel time. 
     * 
     * @return A value indicating time required to travel the
     *        length of the route segment in seconds.
     */
    int GetTravelTime() const;

    /**
     * This method sets the route segment length. 
     * 
     * @param aDistance A value indicating the length of the
     *        the route segment in meters.
     */
    void SetDistance(double aDistance);

    /**
     * This method retrieves the length of the route segment. 
     * 
     * @return A value indicating the length of the
     *        the route segment in meters.
     */
    double GetDistance() const;

    /**
     * This method sets the path (geometry) of the route segment. 
     * 
     * @param rPath A constant reference to a vector of instances of
     *        <code>GeoCoordinates</code> which defines the path (geometry) of
     *        the route segment.
     */
    void SetPath(const GeoCoordinateList& rPath);

    /**
     * This method retrieves the path (geometry) of the route segment. 
     * 
     * @return A vector of instances of <code>GeoCoordinates</code> which
     *        defines the path (geometry) of the route segment.
     */
    GeoCoordinateList GetPath() const;

    /**
     * This method adds a maneuver to the given route segment.
     * 
     * @param rManeuver A constant reference to an object that defines a route
     *        maneuver.
     */
    void addManeuver(const Maneuver& rManeuver);

    /**
     * This method associates a list of maneuvers with the given route segment.
     * 
     * @param vManeuverList A constant reference to a vector of route maneuver
     *        objects.
     */
    void SetManeuverList(const ManeuverList& vManeuverList);

    /**
     * This method retrieves a list of maneuvers associated with the given route
     * segment. 
     * 
     * @return A vector of route maneuver objects.
     */
    ManeuverList GetManeuverList() const;

private:
    RouteSegmentImpl* m_pImpl;

    friend class RouteSegmentImpl;
};

HERE_MAPS_END_NAMESPACE

#endif /* ROUTESEGMENT_H */
