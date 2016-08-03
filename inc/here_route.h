/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LOCATION_HERE_ROUTE_H_
#define _LOCATION_HERE_ROUTE_H_

//plug-in header
#include "here_manager.h"

//maps-service header
#include <maps_route_plugin.h>
#include <maps_route_segment_plugin.h>
#include <maps_route_maneuver_plugin.h>

//map engine header
#include <routes/GeoRouteQuery.h>
#include <routes/GeoRouteQueryListener.h>
#include <routes/GeoRouteReply.h>

HERE_PLUGIN_BEGIN_NAMESPACE

using namespace HERE_MAPS_NAMESPACE_PREFIX;

class HereRoute
: public HereBase
, public GeoRouteQueryListener
{
public:
	/**
	 *This is the default constructor for Route.
	 */

	HereRoute(void *pCbFunc, void *pUserData, int nReqId);

	/**
	 *This is the default destructor for Route.
	 */

	~HereRoute();

	here_error_e PrepareQuery();
	here_error_e PrepareWaypoint(maps_coordinates_h hOrigin, maps_coordinates_h hDestination);
	here_error_e PrepareWaypoint(const maps_coordinates_h* hWaypointList, int nWaypointNum);
	here_error_e PreparePreference(maps_preference_h hPref);

	here_error_e StartRoute(void);

	virtual void OnRouteReply(const GeoRouteReply& Reply);
	virtual void OnRouteFailure(const GeoRouteReply& Reply);

private:
	maps_error_e ProcessSegments(maps_route_h mapsRoute, const RouteSegmentList& hereSegmList);
	maps_error_e ProcessSegmentsPath(maps_route_segment_h mapsSegm, const GeoCoordinateList &herePathList);
	maps_error_e ProcessManeuver(maps_route_segment_h mapsSegm, const ManeuverList& hereManeList);
	const double __convertDistanceUnit(const double dValue);

	maps_distance_unit_e m_eDistanceUnit;
	maps_coordinates_h m_aOriginCoord;
	maps_coordinates_h m_aDestinationCoord;
	GeoRouteQuery* m_pQuery;
};

HERE_PLUGIN_END_NAMESPACE

#endif //_LOCATION_HERE_ROUTE_H_
