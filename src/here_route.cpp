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

#include "here_route.h"

HERE_PLUGIN_BEGIN_NAMESPACE

HereRoute::HereRoute(void *pCbFunc, void *pUserData, int nReqId)
{
	m_pQuery = NULL;

	m_pCbFunc = pCbFunc;
	m_pUserData = pUserData;
	m_nReqId = nReqId;

	m_eDistanceUnit = MAPS_DISTANCE_UNIT_M;
}

HereRoute::~HereRoute()
{
	if (m_pQuery)
	{
		delete m_pQuery;
		m_pQuery = NULL;
	}
}

here_error_e HereRoute::PrepareQuery()
{
	if (m_pQuery)
		return HERE_ERROR_PERMISSION_DENIED;

	GeoCoordinates origCoord, destCoord;
	m_pQuery = new (std::nothrow) GeoRouteQuery(origCoord, destCoord);

	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;
	else
		return HERE_ERROR_NONE;
}

here_error_e HereRoute::PrepareWaypoint(maps_coordinates_h hOrigin, maps_coordinates_h hDestination)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hOrigin || !hDestination)
		return HERE_ERROR_INVALID_PARAMETER;


	const int nWaypointNum = 2;
	maps_coordinates_h hWaypointList[nWaypointNum];
	hWaypointList[0] = hOrigin;
	hWaypointList[1] = hDestination;

	return PrepareWaypoint(hWaypointList, nWaypointNum);
}

here_error_e HereRoute::PrepareWaypoint(const maps_coordinates_h* hWaypointList, int nWaypointNum)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hWaypointList || nWaypointNum <= 0)
		return HERE_ERROR_INVALID_PARAMETER;

	GeoCoordinateList hereCoordList;
	GeoCoordinates hereCoord;
	double dLatitude, dLongitude;

	for (int index = 0; index < nWaypointNum; index++)
	{
		if (hWaypointList[index] != NULL) {
			maps_coordinates_get_latitude(hWaypointList[index], &dLatitude);
			maps_coordinates_get_longitude(hWaypointList[index], &dLongitude);

			//MAPS_LOGD("Waypoint --> Lat : %f, Long : %f", dLatitude, dLongitude);

			hereCoord = GeoCoordinates(dLatitude, dLongitude);

			if (!HereUtils::IsValid(hereCoord))
				return HERE_ERROR_INVALID_PARAMETER;

			hereCoordList.push_back(hereCoord);
		}
	}

	m_pQuery->SetWaypoints(hereCoordList);

	return HERE_ERROR_NONE;
}

here_error_e HereRoute::PreparePreference(maps_preference_h hPref)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hPref)
		return HERE_ERROR_NONE;

/*
	SegmentDetail aSegmentDetail;
	ManeuverDetail aMneuverDetail;
	m_pQuery->SetSegmentDetail(aSegmentDetail);
	m_pQuery->SetManeuverDetail(aMneuverDetail);
*/

	/* transport mode */
	maps_route_transport_mode_e eTransMode;
	if (maps_preference_get_route_transport_mode(hPref, &eTransMode) == MAPS_ERROR_NONE)
	{
		m_pQuery->SetTravelModes(HereUtils::Convert(eTransMode));
	}

	/* eFeature */
	maps_route_feature_e eFeature;
	maps_route_feature_weight_e eFeatureWeight;
	if (maps_preference_get_route_feature(hPref, &eFeature) == MAPS_ERROR_NONE &&
	    maps_preference_get_route_feature_weight(hPref, &eFeatureWeight) == MAPS_ERROR_NONE)
	{
		m_pQuery->SetFeatureWeight(HereUtils::Convert(eFeature),
			HereUtils::Convert(eFeatureWeight));
	}

	/* exclude areas */
	char *szAreaToAvoid;
	if (maps_preference_get(hPref, MAPS_ROUTE_RECT_AREA_TO_AVOID, &szAreaToAvoid) == MAPS_ERROR_NONE)
	{
		GeoBoundingBox gbBox;
		GeoBoundingBoxList gbBoxList;
		gbBoxList.push_back(HereUtils::Convert(szAreaToAvoid, gbBox));
		m_pQuery->SetExcludeAreas(gbBoxList);
		g_free(szAreaToAvoid);
	}

	/* optimization */
	GeoRouteQuery::RouteOptimization hereOpt;
	maps_route_optimization_e mapsOpt;
	if (maps_preference_get_route_optimization(hPref, &mapsOpt) == MAPS_ERROR_NONE)
	{
		switch (mapsOpt)
		{
		case MAPS_ROUTE_TYPE_FASTEST:  hereOpt = GeoRouteQuery::RO_FastestRoute;  break;
		case MAPS_ROUTE_TYPE_SHORTEST: hereOpt = GeoRouteQuery::RO_ShortestRoute; break;
		default:                       hereOpt = GeoRouteQuery::RO_FastestRoute;  break;
		}
		m_pQuery->SetRouteOptimization(hereOpt);
	}

	/* Metric System */
	GeoRouteQuery::MetricSystem eMetric;
	maps_distance_unit_e eUnit;
	if (maps_preference_get_distance_unit(hPref, &eUnit) == MAPS_ERROR_NONE)
	{
		switch (eUnit)
		{
		case MAPS_DISTANCE_UNIT_M:  eMetric = GeoRouteQuery::DIST_metric;   break;
		case MAPS_DISTANCE_UNIT_KM: eMetric = GeoRouteQuery::DIST_metric;   break;
		default:                    eMetric = GeoRouteQuery::DIST_imperial; break;
		}
		m_eDistanceUnit = eUnit;
		m_pQuery->SetMetricSystem(eMetric);
	}

	char *szViewBounds;
	if (maps_preference_get(hPref, MAPS_ROUTE_GEOMETRY_BOUNDING_BOX, &szViewBounds) == MAPS_ERROR_NONE)
	{
		GeoBoundingBox gbBox;
		HereUtils::Convert(szViewBounds, gbBox);
		m_pQuery->SetViewBounds(gbBox);
		g_free(szViewBounds);
	}

	return HERE_ERROR_NONE;
}

here_error_e HereRoute::StartRoute(void)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	m_nRestReqId = m_pQuery->Execute(*this, NULL);

	return (m_nRestReqId > 0 ? HERE_ERROR_NONE : HERE_ERROR_INVALID_OPERATION);
}

void HereRoute::OnRouteReply(const GeoRouteReply& Reply)
{
	if (m_bCanceled || !m_pCbFunc) // ignore call back if it was cancelled.
	{
		delete this;
		return;
	}

	maps_route_h mapsRoute;
	maps_error_e error;
	GeoRouteList hereRouteList = Reply.GetRoutes();
	int nReplyIdx = 0, nReplyNum = hereRouteList.size();
	GeoRouteList::iterator hereRoute;

	if (nReplyNum == 0)
	{
		((maps_service_search_route_cb)m_pCbFunc)(MAPS_ERROR_NOT_FOUND, m_nReqId,
			0, 0, NULL, m_pUserData);
		delete this;
		return;
	}

	for (hereRoute = hereRouteList.begin() ; hereRoute != hereRouteList.end() ; hereRoute++)
	{
		error = (maps_error_e)maps_route_create(&mapsRoute);

		if (error == MAPS_ERROR_NONE)
		{
			/* route id */
			if (!hereRoute->GetRouteId().empty())
				maps_route_set_route_id(mapsRoute, (char*)hereRoute->GetRouteId().c_str());

			/* distance */
			maps_route_set_total_distance(mapsRoute,
				HereUtils::ConvertDistance(hereRoute->GetDistance(), m_eDistanceUnit));

			/* distance unit */
			maps_route_set_distance_unit(mapsRoute, m_eDistanceUnit);

			/* duration */
			maps_route_set_total_duration(mapsRoute, hereRoute->GetTravelTime());

			/* travel mode */
			maps_route_transport_mode_e eTransportMode;
			eTransportMode = HereUtils::Convert(hereRoute->GetTravelMode());
			maps_route_set_transport_mode(mapsRoute, eTransportMode);

			/* path */
			GeoCoordinateList herePathList = hereRoute->GetPath();
			maps_item_list_h mapsPathList;
			maps_coordinates_h mapsPath;

			if (maps_item_list_create(&mapsPathList) == MAPS_ERROR_NONE)
			{
				GeoCoordinateList::iterator herePath;
				for (herePath = herePathList.begin(); herePath != herePathList.end(); herePath++)
				{
					double dLat = herePath->GetLatitude();
					double dLng = herePath->GetLongitude();

					if(maps_coordinates_create(dLat, dLng, &mapsPath) == MAPS_ERROR_NONE)
					{
						if (herePath == herePathList.begin())
							maps_route_set_origin(mapsRoute, mapsPath);
						else if (herePath == herePathList.end()-1)
							maps_route_set_destination(mapsRoute, mapsPath);
						else
							maps_item_list_append(mapsPathList, mapsPath, maps_coordinates_clone);

						maps_coordinates_destroy(mapsPath);
					}
				}

				if (maps_item_list_items(mapsPathList))
				{
					maps_route_set_path(mapsRoute, mapsPathList);
					maps_item_list_remove_all(mapsPathList, maps_coordinates_destroy);
				}
				maps_item_list_destroy(mapsPathList);
			}

			/* bounding box */
			maps_area_h hMapsArea = NULL;
			HereUtils::Convert(hereRoute->GetBounds(), hMapsArea);
			if (hMapsArea)
			{
				maps_route_set_bounding_box(mapsRoute, hMapsArea);
				maps_area_destroy(hMapsArea);
			}

			/* segments */
			ProcessSegments(mapsRoute, hereRoute->GetRouteSegmentList());
		}

		if (m_bCanceled)
		{
			maps_route_destroy(mapsRoute);
			break;
		}
		else
		{
			if (((maps_service_search_route_cb)m_pCbFunc)(error, m_nReqId,
				nReplyIdx++, nReplyNum, mapsRoute, m_pUserData) == FALSE)
			{
				delete this;
				return;
			}
			//maps_route_destroy(mapsRoute);
		}
	}

	if(nReplyIdx >= nReplyNum)
		delete this;
}

void HereRoute::OnRouteFailure(const GeoRouteReply& Reply)
{
	if (!m_bCanceled && m_pCbFunc)
		((maps_service_search_route_cb)m_pCbFunc)((maps_error_e)GetErrorCode(Reply), m_nReqId, 0, 0, NULL, m_pUserData);
	delete this;
}

maps_error_e HereRoute::ProcessSegments(maps_route_h mapsRoute, const RouteSegmentList& hereSegmList)
{
	maps_item_list_h mapsSegmList;
	maps_route_segment_h mapsSegm;
	maps_error_e error;

	if (hereSegmList.empty()) return MAPS_ERROR_NOT_FOUND;

	if ((error = (maps_error_e)maps_item_list_create(&mapsSegmList)) != MAPS_ERROR_NONE)
		return error;

	RouteSegmentList::const_iterator hereSegm;
	for (hereSegm = hereSegmList.begin() ; hereSegm != hereSegmList.end() ; hereSegm++)
	{
		if (maps_route_segment_create(&mapsSegm) != MAPS_ERROR_NONE) continue;

		/* distance */
		maps_route_segment_set_distance(mapsSegm,
			HereUtils::ConvertDistance(hereSegm->GetDistance(), m_eDistanceUnit));

		/* tranvel time */
		maps_route_segment_set_duration(mapsSegm, hereSegm->GetTravelTime());

		/* origin, destination */
		GeoCoordinateList herePathList = hereSegm->GetPath();
		int here_path_list_size = herePathList.size();

		if (here_path_list_size > 0)
		{
			GeoCoordinates hereOrig = herePathList.at(0);
			GeoCoordinates hereDest = herePathList.at(here_path_list_size-1);

			maps_coordinates_h mapsOrig, mapsDest;
			maps_coordinates_create(hereOrig.GetLatitude(),
						hereOrig.GetLongitude(), &mapsOrig);
			maps_coordinates_create(hereDest.GetLatitude(),
						hereDest.GetLongitude(), &mapsDest);
			maps_route_segment_set_origin(mapsSegm, mapsOrig);
			maps_route_segment_set_destination(mapsSegm, mapsDest);
			maps_coordinates_destroy(mapsOrig);
			maps_coordinates_destroy(mapsDest);
		}

		/* maneuver */
		ProcessManeuver(mapsSegm, hereSegm->GetManeuverList());

		maps_item_list_append(mapsSegmList, mapsSegm, maps_route_segment_clone);
		maps_route_segment_destroy(mapsSegm);
	}

	if (maps_item_list_items(mapsSegmList))
	{
		maps_route_set_segments(mapsRoute, mapsSegmList);
		maps_item_list_remove_all(mapsSegmList, maps_route_segment_destroy);
	}
	maps_item_list_destroy(mapsSegmList);

	return MAPS_ERROR_NONE;
}

maps_error_e HereRoute::ProcessManeuver(maps_route_segment_h mapsSegm, const ManeuverList& hereManeList)
{
	maps_item_list_h mapsManeList;
	maps_route_maneuver_h mapsManeuver;
	maps_coordinates_h mapsCoord;
	maps_error_e error;

	if (hereManeList.empty()) return MAPS_ERROR_NOT_FOUND;

	if ((error = (maps_error_e)maps_item_list_create(&mapsManeList)) != MAPS_ERROR_NONE)
		return error;

	ManeuverList::const_iterator hereMane;
	for (hereMane = hereManeList.begin() ; hereMane != hereManeList.end() ; hereMane++)
	{
		if (maps_route_maneuver_create(&mapsManeuver) != MAPS_ERROR_NONE) continue;

		/* position */
		if (maps_coordinates_create(hereMane->GetPosition().GetLatitude(),
			hereMane->GetPosition().GetLongitude(), &mapsCoord) == MAPS_ERROR_NONE)
		{
			maps_route_maneuver_set_position(mapsManeuver, mapsCoord);
			maps_coordinates_destroy(mapsCoord);
		}

		/* instruction */
		if (!hereMane->GetInstructionText().empty())
			maps_route_maneuver_set_instruction_text(mapsManeuver,
				(char*)hereMane->GetInstructionText().c_str());

		/* length */
		maps_route_maneuver_set_distance_to_next_instruction(mapsManeuver,
			HereUtils::ConvertDistance(hereMane->GetDistanceToNextInstruction(), m_eDistanceUnit));

		/* travel time */
		maps_route_maneuver_set_time_to_next_instruction(mapsManeuver,
			hereMane->GetTimeToNextInstruction());

		/* direction -> turn type */
		maps_route_maneuver_set_turn_type(mapsManeuver,
			HereUtils::Convert(hereMane->GetDirection()));

		maps_item_list_append(mapsManeList, mapsManeuver, maps_route_maneuver_clone);
		maps_route_maneuver_destroy(mapsManeuver);
	}

	if (maps_item_list_items(mapsManeList))
	{
		maps_route_segment_set_maneuvers(mapsSegm, mapsManeList);
		maps_item_list_remove_all(mapsManeList, maps_route_maneuver_destroy);
	}
	maps_item_list_destroy(mapsManeList);

	return MAPS_ERROR_NONE;
}

HERE_PLUGIN_END_NAMESPACE

