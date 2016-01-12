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

#ifndef GEOROUTEQUERY_H
#define GEOROUTEQUERY_H

#include <map>

#include "common/HereMaps_global.h"
#include "common/BaseQuery.h"
#include "common/GeoCoordinates.h"
#include "common/GeoBoundingBox.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoRouteReply;
class QueryListener;
class GeoRouteQueryListener;

/**
 * This class encapsulates a query that requests a route calculation. The
 * required calculation is specified in terms of route features, including the
 * start and end points, waypoints (the locations through which the route must
 * pass), areas to include and to avoid, mode of travel, route features with
 * weighting, required optimization, etc.
 * 
 * \ingroup routes
 */
class EXPORT_API GeoRouteQuery : public BaseQuery
{
public:

    /**
     * This enumeration defines identifiers for the supported modes of travel. 
     */
    enum TravelMode {
        TM_CarTravel = 0x0001,           ///< Indicates that the route is to be
                                         ///  traveled by car.
        TM_PedestrianTravel = 0x0002,    ///< Indicates that the route is for a pedestrian.
        TM_PublicTransitTravel = 0x0008, ///< Indicates that the route is to be
                                         ///  traveled using public transport.
    };

    /**
     * This enumeration defines identifiers for the supported route feature
     * types, feature types that can be favored or excluded by the route
     * calculation.  
     */
    enum FeatureType {
        FT_NoFeature = 0x00000000,            ///< Indicates no route features (are selected).
        FT_TollFeature = 0x00000001,          ///< Indicates toll roads (toll gates/booths).
        FT_MotorwayFeature = 0x00000002,      ///< Indicates motorway(s).
        FT_BoatFerryFeature = 0x00000004,     ///< Indicates a boat ferry.
        FT_RailFerryFeature = 0x00000008,     ///< Indicates rail (train) ferry.
        FT_PublicTransitFeature = 0x00000010, ///< Indicates public transport.
        FT_TunnelFeature = 0x00000020,        ///< Indicates tunnel.   
        FT_DirtRoadFeature = 0x00000040,      ///< Indicates dirt road.
        FT_ParksFeature = 0x00000080,         ///< Indicates park. 
        FT_HOVLane = 0x00000100,              ///< Indicates a high-occupancy vehicle lane. 
        FT_Stairs = 0x00000200                ///< Indicates stairs.
    };                                             

    /** 
     * This enumeration defines identifiers for the supported route feature weighting. 
     */
    enum FeatureWeight {
        FW_NormalFeatureWeight = 0x00000000,       ///< Indicates normal weighting.
        FW_PreferFeatureWeight = 0x00000001,       ///< Indicates that a feature is preferred.
        FW_AvoidFeatureWeight = 0x00000002,        ///< Indicates that a feature is to be avoided. 
        FW_SoftExcludeFeatureWeight = 0x00000004,  ///< Indicates that soft-exclude applies to the feature.
        FW_StrictExcludeFeatureWeight = 0x00000008 ///< Indicates that the feature is to be strictly excluded. 
    };

    /**
     * This typedef defines a map of route feature types and weighting as a type.
     */
    typedef std::map< GeoRouteQuery::FeatureType, GeoRouteQuery::FeatureWeight > FeaturesMap;

    /** 
     * This enumeration defines identifiers for the supported route optimizations. 
     */
    enum RouteOptimization {
        RO_ShortestRoute = 0x0001,    ///< Indicates the shortest route.
        RO_FastestRoute = 0x0002,     ///< Indicates the fastest route.
    };

    /** 
     * This enumeration defines identifiers for route segment detail specifiers. 
     */
    enum SegmentDetail {
        SD_NoSegmentData = 0x0000,    ///< Indicates that no route segment data are to be included.
        SD_BasicSegmentData = 0x0001  ///< Indicates that basic route segment data are to be included.
    };

    /** 
     * This enumeration defines identifiers for route maneuver specifiers. 
     */
    enum ManeuverDetail {
        MD_NoManeuvers = 0x0000,      ///< Indicates that manuevers are to be included int he route.
        MD_BasicManeuvers = 0x0001    ///< Indicates that basic maneuvers are to be included in the route calculation.
    };

#ifdef TIZEN_CUSTOMIZATION
    /** 
     * This enumeration defines identifiers for route MetricSystem specifiers.
     */
    enum MetricSystem {
        DIST_metric = 0x0000,        ///< Indicates that MetricSystem is m & km
        DIST_imperial = 0x0001       ///< Indicates that MetricSystem is miles
    };
#endif

    /**
     * This method is a constructor that initializes a new instance of the
     * class, using the list of waypoints supplied by the caller.
     * 
     * @param rWaypoints A constant reference to a vector of instances of
     *        <code>GeoCoordinates</code> that define the route waypoints.
     */
    GeoRouteQuery(const GeoCoordinateList &rWaypoints = GeoCoordinateList());

    /**
     * This method is a constructor that initializes a new instance of the
     * class, using the objects representing the route origin and destination
     * supplied by the caller.
     * 
     * @param rOrigin A constant reference to an object that defines the point
     *        of origin for the route.
     * 
     * @param rDestination A constant reference to an object that defines the 
     *        destination for the route.
     */
    GeoRouteQuery(const GeoCoordinates &rOrigin, const GeoCoordinates &rDestination);

    /**
     * This method is a copy constructor that initializes a new instance of the
     * class by copying the values of the properties of the object supplied by
     * the caller.
     * 
     * @param rRhs A constant reference to an object whose property values are
     *        to be used to initialize a new instance of the class.
     */
    GeoRouteQuery(const GeoRouteQuery &rRhs);

    /** 
     * This method is the destructor for objects of this class.
     */
    ~GeoRouteQuery();

    /** 
     * This is the assignment operator.
     * 
     * @param rRhs A constant reference to an object whose property values are
     *        to be copied to the given instance.
     */
    GeoRouteQuery& operator = (const GeoRouteQuery &rRhs);

    /**
     * This method sets route waypoints, using the list of objects supplied by
     * the caller.
     * 
     * @param rWaypoints A constant reference to a vector of instances of
     *        <code>GeoCoordinates</code> that define the route waypoints.
     */
    void SetWaypoints(const GeoCoordinateList &rWaypoints);

    /**
     * This method retrieves the route waypoints.
     * 
     * @return A vector of instances of <code>GeoCoordinates</code> that define
     *        the route waypoints.
     */
    GeoCoordinateList GetWaypoints() const;

    /** 
     * This method sets areas through which the route must not pass, using a
     * list of bounding box objects supplied by the caller.
     * 
     * @param rAreas A constant reference to a list of bounding box objects that
     *        define the areas the route must avoid.
     */
    void SetExcludeAreas(const GeoBoundingBoxList &rAreas);

    /** 
     * This method retrieves a list of bounding boxes that defines areas through
     * which the route must not pass. 
     * 
     * @return A list of bounding box objects that define the areas the route
     *        must avoid.
     */
    GeoBoundingBoxList GetExcludeAreas() const;

    // defaults to TravelByCar
    /**
     * This method sets the travel mode to be used in the route query.
     * 
     * @param aTravelModes A value indicating the travel mode to use in the
     *        query.
     */
    void SetTravelModes(TravelMode aTravelModes);

    /**
     * This method retrieves the travel mode used in the route query.
     * 
     * @return A value indicating the travel mode used in the
     *        query.
     */
    TravelMode GetTravelModes() const;

    /**
     * This method associates weighting with a feature to be used in the route
     * query.  
     * 
     * @param aFeatureType A value indicating the feature type to which the
     *        weighting is to apply.
     *  
     * @param aFeatureWeight A value indicating the weighting to apply.
     */
    void SetFeatureWeight(FeatureType aFeatureType, FeatureWeight aFeatureWeight);

    /**
     * This method retrieves the weighting for the feature type specified by the
     * caller.  
     * 
     * @param aFeatureType A value indicating the feature type for which to 
     *        retrieve weighting.
     *  
     * @return A value indicating the weighting associated with the named route
     *        feature.
     */
    FeatureWeight GetFeatureWeight(FeatureType aFeatureType) const;

    /**
     * This method retrieves a map of route feature types specified for the
     * given query.
     * 
     * @return An object containing a map of route feature types specified for
     *         the given query.
     */
    FeaturesMap GetFeatureTypes() const;

    // defaults to OptimizeFastes)
    /**
     *  This method sets the route optimization option for the given query.
     * 
     * @param aOptimization A value indicating the route optimization option to
     *        set for the given query.
     */
    void SetRouteOptimization(RouteOptimization aOptimization);

    /**
     *  This method retrieves the route optimization selector set for the given
     *  query.
     * 
     * @return A value indicating the route optimization selector set for the
     *        given query.
     */
    RouteOptimization GetRouteOptimization() const;

    // defaults to BasicSegmentData
    /**
     * This method sets the segment detail selector for the given query.
     * 
     * @param aSegmentDetail A value indicating the segment detail selector for
     *        the given query.
     */
    void SetSegmentDetail(SegmentDetail aSegmentDetail);

    /**
     * This method retrieves the segment detail selector for the given query.
     * 
     * @return A value indicating the segment detail selector set for the given
     *        query.
     */
    SegmentDetail GetSegmentDetail() const;

    // defaults to BasicManeuvers
    /**
     * This method sets the maneuver detail selector for the given
     * query. 
     * 
     * @param aManeuverDetail A value indicating the maneuver detail selector for
     *        the given query.
     */
    void SetManeuverDetail(ManeuverDetail aMneuverDetail);

    /**
     * This method retrieves the maneuver detail selector set for the given
     * query. 
     * 
     * @return A value indicating the maneuver detail selector for
     *        the given query.
     */
    ManeuverDetail GetManeuverDetail() const;

#ifdef TIZEN_CUSTOMIZATION
    /**
     * This method sets the MetricSystem selector for the given
     * query. 
     *
     * @param aMetricSystem A value indicating the MetricSystemselector for
     *        the given query.
     */
    void SetMetricSystem(GeoRouteQuery::MetricSystem aMetricSystem);

    /**
     * This method retrieves the MetricSystem selector set for the given query.
     *
     * @return A value indicating the MetricSystem selector for
     *        the given query.
     */
    GeoRouteQuery::MetricSystem GetMetricSystem(void);

    /**
     * This method sets the bounding area for the given query.
     *
     * @param aMetricSystem A value indicating the bounding area for
     *        the given query.
     */
    void SetViewBounds(GeoBoundingBox aViewBounds);

    /**
     * This method retrieves the bounding area set for the given query.
     *
     * @return A value indicating the bounding area for
     *        the given query.
     */
    GeoBoundingBox GetViewBounds(void);
#endif

    /**
     * This method attempts to establish a connection with the server and then,
     * if the connection has been established, it builds and submits a query.
     * 
     * @rListener rListener A reference to an object that is to be notified when
     *        the reply to the query has arrived from the server.
     * 
     * @param pUserData A pointer to user data to be passed back within the
     *        corresponding reply object.
     *
     * @return A vaur representing the identifier of issued request.
     */
    RestItemHandle::RequestId Execute(GeoRouteQueryListener& rListener, Tizen::Maps::HereObject* pUserData = NULL) const;

    /**
     * This static method returns the base URI to be used for all subsequent
     * geo route queries.
     *
     * @return A string containing the base URI.
     */
    static String GetBaseUri();

    /**
     * This static method returns the base URI to be used for all subsequent
     * geo route queries.
     *
     * @param sUri A constant reference to a string containing the base URI.
     */
    static void SetBaseUri(const String& sUri);

private:
    bool CreateBaseUrl(const String& sService, String& sDst) const;

    String CreateUri() const;

private:
    class GeoRouteQueryImpl;
    GeoRouteQueryImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif /* GEOROUTEQUERY_H */
