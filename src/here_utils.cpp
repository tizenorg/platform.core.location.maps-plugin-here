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

#include "here_utils.h"
#include <common/CommunicationError.h>


static const double LATITUDE_RANGE = 85.05113;
static const double LONGITUDE_RANGE = 180.0;


extern "C"
{
int ConvertToMapsError(int nErr)
{
	switch (nErr)
	{
		case HERE_ERROR_NONE:                  return MAPS_ERROR_NONE;
		case HERE_ERROR_PERMISSION_DENIED:     return MAPS_ERROR_PERMISSION_DENIED;
		case HERE_ERROR_OUT_OF_MEMORY:         return MAPS_ERROR_OUT_OF_MEMORY;
		case HERE_ERROR_INVALID_PARAMETER:     return MAPS_ERROR_INVALID_PARAMETER;
		case HERE_ERROR_NOT_SUPPORTED:         return MAPS_ERROR_NOT_SUPPORTED;
		case HERE_ERROR_CONNECTION_TIME_OUT:   return MAPS_ERROR_CONNECTION_TIME_OUT;
		case HERE_ERROR_NETWORK_UNREACHABLE:   return MAPS_ERROR_NETWORK_UNREACHABLE;
		case HERE_ERROR_INVALID_OPERATION:     return MAPS_ERROR_INVALID_OPERATION;
		case HERE_ERROR_KEY_NOT_AVAILABLE:     return MAPS_ERROR_KEY_NOT_AVAILABLE;
		case HERE_ERROR_RESOURCE_BUSY:         return MAPS_ERROR_RESOURCE_BUSY;
		case HERE_ERROR_CANCELED:              return MAPS_ERROR_CANCELED;
		case HERE_ERROR_UNKNOWN:               return MAPS_ERROR_UNKNOWN;
		case HERE_ERROR_SERVICE_NOT_AVAILABLE: return MAPS_ERROR_SERVICE_NOT_AVAILABLE;
		case HERE_ERROR_NOT_FOUND:             return MAPS_ERROR_NOT_FOUND;
	}
	return MAPS_ERROR_UNKNOWN;
}

int ConvertToHereError(int nErr)
{
	switch (nErr)
	{
		case MAPS_ERROR_NONE:                  return HERE_ERROR_NONE;
		case MAPS_ERROR_PERMISSION_DENIED:     return HERE_ERROR_PERMISSION_DENIED;
		case MAPS_ERROR_OUT_OF_MEMORY:         return HERE_ERROR_OUT_OF_MEMORY;
		case MAPS_ERROR_INVALID_PARAMETER:     return HERE_ERROR_INVALID_PARAMETER;
		case MAPS_ERROR_NOT_SUPPORTED:         return HERE_ERROR_NOT_SUPPORTED;
		case MAPS_ERROR_CONNECTION_TIME_OUT:   return HERE_ERROR_CONNECTION_TIME_OUT;
		case MAPS_ERROR_NETWORK_UNREACHABLE:   return HERE_ERROR_NETWORK_UNREACHABLE;
		case MAPS_ERROR_INVALID_OPERATION:     return HERE_ERROR_INVALID_OPERATION;
		case MAPS_ERROR_KEY_NOT_AVAILABLE:     return HERE_ERROR_KEY_NOT_AVAILABLE;
		case MAPS_ERROR_RESOURCE_BUSY:         return HERE_ERROR_RESOURCE_BUSY;
		case MAPS_ERROR_CANCELED:              return HERE_ERROR_CANCELED;
		case MAPS_ERROR_UNKNOWN:               return HERE_ERROR_UNKNOWN;
		case MAPS_ERROR_SERVICE_NOT_AVAILABLE: return HERE_ERROR_SERVICE_NOT_AVAILABLE;
		case MAPS_ERROR_NOT_FOUND:             return HERE_ERROR_NOT_FOUND;
	}
	return HERE_ERROR_UNKNOWN;
}

const char* ConverHereErrorToString(int nErr)
{
	switch (nErr)
	{
		case HERE_ERROR_NONE:                  return "No errors";
		case HERE_ERROR_PERMISSION_DENIED:     return "Permission denied";
		case HERE_ERROR_OUT_OF_MEMORY:         return "Out of memory";
		case HERE_ERROR_INVALID_PARAMETER:     return "Invalid Parameter";
		case HERE_ERROR_NOT_SUPPORTED:         return "Not suppoerted";
		case HERE_ERROR_CONNECTION_TIME_OUT:   return "Connection time out";
		case HERE_ERROR_NETWORK_UNREACHABLE:   return "Network unreachable";
		case HERE_ERROR_INVALID_OPERATION:     return "Invalid operation";
		case HERE_ERROR_KEY_NOT_AVAILABLE:     return "Key not available";
		case HERE_ERROR_RESOURCE_BUSY:         return "Resource busy";
		case HERE_ERROR_CANCELED:              return "Canceled";
		case HERE_ERROR_UNKNOWN:               return "Unknown";
		case HERE_ERROR_SERVICE_NOT_AVAILABLE: return "Service not available";
		case HERE_ERROR_NOT_FOUND:             return "Not found";
	}
	return "Unknown";
}

const char* ConvertMapsErrorToChar(int nErr)
{
	switch (nErr)
	{
		case MAPS_ERROR_NONE:                  return "MAPS_ERROR_NONE";
		case MAPS_ERROR_PERMISSION_DENIED:     return "MAPS_ERROR_PERMISSION_DENIED";
		case MAPS_ERROR_OUT_OF_MEMORY:         return "MAPS_ERROR_OUT_OF_MEMORY";
		case MAPS_ERROR_INVALID_PARAMETER:     return "MAPS_ERROR_INVALID_PARAMETER";
		case MAPS_ERROR_NOT_SUPPORTED:         return "MAPS_ERROR_NOT_SUPPORTED";
		case MAPS_ERROR_CONNECTION_TIME_OUT:   return "MAPS_ERROR_CONNECTION_TIME_OUT";
		case MAPS_ERROR_NETWORK_UNREACHABLE:   return "MAPS_ERROR_NETWORK_UNREACHABLE";
		case MAPS_ERROR_INVALID_OPERATION:     return "MAPS_ERROR_INVALID_OPERATION";
		case MAPS_ERROR_KEY_NOT_AVAILABLE:     return "MAPS_ERROR_KEY_NOT_AVAILABLE";
		case MAPS_ERROR_RESOURCE_BUSY:         return "MAPS_ERROR_RESOURCE_BUSY";
		case MAPS_ERROR_CANCELED:              return "MAPS_ERROR_CANCELED";
		case MAPS_ERROR_UNKNOWN:               return "MAPS_ERROR_UNKNOWN";
		case MAPS_ERROR_SERVICE_NOT_AVAILABLE: return "MAPS_ERROR_SERVICE_NOT_AVAILABLE";
		case MAPS_ERROR_NOT_FOUND:             return "MAPS_ERROR_NOT_FOUND";
	}
	return "MAPS_ERROR_UNKNOWN";
}
}


HERE_PLUGIN_BEGIN_NAMESPACE

HereUtils::HereUtils()
{
}

HereUtils::~HereUtils()
{
}

GeoRouteQuery::TravelMode HereUtils::Convert(maps_route_transport_mode_e nVal)
{
	switch (nVal)
	{
		case MAPS_ROUTE_TRANSPORT_MODE_CAR:           return GeoRouteQuery::TM_CarTravel;
		case MAPS_ROUTE_TRANSPORT_MODE_PEDESTRIAN:    return GeoRouteQuery::TM_PedestrianTravel;
		case MAPS_ROUTE_TRANSPORT_MODE_PUBLICTRANSIT: return GeoRouteQuery::TM_PublicTransitTravel;
		default: break;
	}
	return GeoRouteQuery::TM_CarTravel;
}

maps_route_transport_mode_e HereUtils::Convert(GeoRouteQuery::TravelMode nVal)
{
	switch (nVal)
	{
		case GeoRouteQuery::TM_CarTravel:           return MAPS_ROUTE_TRANSPORT_MODE_CAR;
		case GeoRouteQuery::TM_PedestrianTravel:    return MAPS_ROUTE_TRANSPORT_MODE_PEDESTRIAN;
		case GeoRouteQuery::TM_PublicTransitTravel: return MAPS_ROUTE_TRANSPORT_MODE_PUBLICTRANSIT;
		default: break;
	}
	return MAPS_ROUTE_TRANSPORT_MODE_CAR;
}

GeoRouteQuery::FeatureType HereUtils::Convert(maps_route_feature_e nVal)
{
	switch (nVal)
	{
		case MAPS_ROUTE_FEATURE_NO:             return GeoRouteQuery::FT_NoFeature;
		case MAPS_ROUTE_FEATURE_TOLL:           return GeoRouteQuery::FT_TollFeature;
		case MAPS_ROUTE_FEATURE_MOTORWAY:       return GeoRouteQuery::FT_MotorwayFeature;
		case MAPS_ROUTE_FEATURE_BOATFERRY:      return GeoRouteQuery::FT_BoatFerryFeature;
		case MAPS_ROUTE_FEATURE_RAILFERRY:      return GeoRouteQuery::FT_RailFerryFeature;
		case MAPS_ROUTE_FEATURE_PUBLICTTRANSIT: return GeoRouteQuery::FT_PublicTransitFeature;
		case MAPS_ROUTE_FEATURE_TUNNEL:         return GeoRouteQuery::FT_TunnelFeature;
		case MAPS_ROUTE_FEATURE_DIRTROAD:       return GeoRouteQuery::FT_DirtRoadFeature;
		case MAPS_ROUTE_FEATURE_PARKS:          return GeoRouteQuery::FT_ParksFeature;
		case MAPS_ROUTE_FEATURE_HOVLANE:        return GeoRouteQuery::FT_HOVLane;
		case MAPS_ROUTE_FEATURE_STAIRS:         return GeoRouteQuery::FT_Stairs;
		default: break;
	}
	return GeoRouteQuery::FT_NoFeature;
}

GeoRouteQuery::FeatureWeight HereUtils::Convert(maps_route_feature_weight_e nVal)
{
	switch (nVal)
	{
		case MAPS_ROUTE_FEATURE_WEIGHT_NORMAL:        return GeoRouteQuery::FW_NormalFeatureWeight;
		case MAPS_ROUTE_FEATURE_WEIGHT_PREFER:        return GeoRouteQuery::FW_PreferFeatureWeight;
		case MAPS_ROUTE_FEATURE_WEIGHT_AVOID:         return GeoRouteQuery::FW_AvoidFeatureWeight;
		case MAPS_ROUTE_FEATURE_WEIGHT_SOFTEXCLUDE:   return GeoRouteQuery::FW_SoftExcludeFeatureWeight;
		case MAPS_ROUTE_FEATURE_WEIGHT_STRICTEXCLUDE: return GeoRouteQuery::FW_StrictExcludeFeatureWeight;
		default: break;
	}
	return GeoRouteQuery::FW_NormalFeatureWeight;
}

maps_route_turn_type_e HereUtils::Convert(Maneuver::InstructionDirection nVal)
{
	switch (nVal)
	{
		case Maneuver::ID_NoDirection:          return MAPS_ROUTE_TURN_TYPE_NONE;
		case Maneuver::ID_DirectionForward:     return MAPS_ROUTE_TURN_TYPE_STRAIGHT;
		case Maneuver::ID_DirectionBearRight:   return MAPS_ROUTE_TURN_TYPE_BEAR_RIGHT;
		case Maneuver::ID_DirectionLightRight:  return MAPS_ROUTE_TURN_TYPE_LIGHT_RIGHT;
		case Maneuver::ID_DirectionRight:       return MAPS_ROUTE_TURN_TYPE_RIGHT;
		case Maneuver::ID_DirectionHardRight:   return MAPS_ROUTE_TURN_TYPE_HARD_RIGHT;
		case Maneuver::ID_DirectionUTurnRight:  return MAPS_ROUTE_TURN_TYPE_UTURN_RIGHT;
		case Maneuver::ID_DirectionUTurnLeft:   return MAPS_ROUTE_TURN_TYPE_UTURN_LEFT;
		case Maneuver::ID_DirectionHardLeft:    return MAPS_ROUTE_TURN_TYPE_HARD_LEFT;
		case Maneuver::ID_DirectionLeft:        return MAPS_ROUTE_TURN_TYPE_LEFT;
		case Maneuver::ID_DirectionLightLeft:   return MAPS_ROUTE_TURN_TYPE_LIGHT_LEFT;
		case Maneuver::ID_DirectionBearLeft:    return MAPS_ROUTE_TURN_TYPE_BEAR_LEFT;
		default: break;
	}
	return MAPS_ROUTE_TURN_TYPE_NONE;
}

Maneuver::InstructionDirection HereUtils::Convert(maps_route_turn_type_e nVal)
{
	switch (nVal)
	{
		case MAPS_ROUTE_TURN_TYPE_NONE:         return Maneuver::ID_NoDirection;
		case MAPS_ROUTE_TURN_TYPE_STRAIGHT:     return Maneuver::ID_DirectionForward;
		case MAPS_ROUTE_TURN_TYPE_BEAR_RIGHT:   return Maneuver::ID_DirectionBearRight;
		case MAPS_ROUTE_TURN_TYPE_LIGHT_RIGHT:  return Maneuver::ID_DirectionLightRight;
		case MAPS_ROUTE_TURN_TYPE_RIGHT:        return Maneuver::ID_DirectionRight;
		case MAPS_ROUTE_TURN_TYPE_HARD_RIGHT:   return Maneuver::ID_DirectionHardRight;
		case MAPS_ROUTE_TURN_TYPE_UTURN_RIGHT:  return Maneuver::ID_DirectionUTurnRight;
		case MAPS_ROUTE_TURN_TYPE_UTURN_LEFT:   return Maneuver::ID_DirectionUTurnLeft;
		case MAPS_ROUTE_TURN_TYPE_HARD_LEFT:    return Maneuver::ID_DirectionHardLeft;
		case MAPS_ROUTE_TURN_TYPE_LEFT:         return Maneuver::ID_DirectionLeft;
		case MAPS_ROUTE_TURN_TYPE_LIGHT_LEFT:   return Maneuver::ID_DirectionLightLeft;
		case MAPS_ROUTE_TURN_TYPE_BEAR_LEFT:    return Maneuver::ID_DirectionBearLeft;
		default: break;
	}
	return Maneuver::ID_NoDirection;
}

maps_error_e HereUtils::ConvertHttpCodeToMapsError(int nVal)
{
	switch (nVal)
	{
		case 200:/*Ok*/				return MAPS_ERROR_NONE;
		case 408:/*Request timeout*/
		case 504:/*Gateway timeout*/
		case 598:/*Network reading timeout*/
		case 599:/*Network connection timeout*/	return MAPS_ERROR_CONNECTION_TIME_OUT;

		case 404:/*Not found*/
		case 407:/*Proxy auth. required*/
		case 502:/*Bad gateway*/		return MAPS_ERROR_NETWORK_UNREACHABLE;

		case 401:/*Unauthorized*/
		case 402:/*Payment required*/		return MAPS_ERROR_KEY_NOT_AVAILABLE;

		case 405:/*Method not allowed*/
		case 413:/*Request entity too larget*/
		case 414:/*Request uri too large*/	return MAPS_ERROR_INVALID_OPERATION;

		case 403:/*Forbidden*/
		case 500:/*Server internal error*/
		case 501:/*Not implemented*/
		case 503:/*Service unavailable*/	return MAPS_ERROR_SERVICE_NOT_AVAILABLE;
	}

	if (nVal > 0 && nVal < 100) // curl error code
		return MAPS_ERROR_NETWORK_UNREACHABLE;

	if (nVal >= 400 && nVal < 500) // http code 4xx (client-side error)
		return MAPS_ERROR_INVALID_OPERATION;

	if (nVal >= 500 && nVal < 600) // http code 5xx (server-side error)
		return MAPS_ERROR_SERVICE_NOT_AVAILABLE;

	return MAPS_ERROR_UNKNOWN;
}

GeoBoundingBox& HereUtils::Convert(maps_area_h hArea, GeoBoundingBox& Box)
{
	maps_area_s* area_s = (maps_area_s*)hArea;

	if (!area_s || area_s->type != MAPS_AREA_RECTANGLE) return Box;

	GeoCoordinates hereCoordLT(area_s->rect.top_left.latitude, area_s->rect.top_left.longitude);
	GeoCoordinates hereCoordRB(area_s->rect.bottom_right.latitude, area_s->rect.bottom_right.longitude);

	Box.SetTopLeft(hereCoordLT);
	Box.SetBottomRight(hereCoordRB);

	return Box;
}

maps_area_h& HereUtils::Convert(GeoBoundingBox Box, maps_area_h& hArea)
{
	maps_coordinates_h mapsCoordLT, mapsCoordRB;
	GeoCoordinates hereCoordLT, hereCoordRB;

	hereCoordLT = Box.GetTopLeft();
	hereCoordRB = Box.GetBottomRight();

	maps_coordinates_create(hereCoordLT.GetLatitude(), hereCoordLT.GetLongitude(), &mapsCoordLT);
	maps_coordinates_create(hereCoordRB.GetLatitude(), hereCoordRB.GetLongitude(), &mapsCoordRB);

	maps_area_create_rectangle(mapsCoordLT, mapsCoordRB, &hArea);

	maps_coordinates_destroy(mapsCoordLT);
	maps_coordinates_destroy(mapsCoordRB);

	return hArea;
}

GeoBoundingCircle& HereUtils::Convert(maps_area_h hArea, GeoBoundingCircle& circle)
{
	maps_area_s* area_s = (maps_area_s*)hArea;

	if (!area_s || area_s->type != MAPS_AREA_CIRCLE) return circle;

	GeoCoordinates hereCoord(area_s->circle.center.latitude, area_s->circle.center.longitude);

	circle.SetCenter(hereCoord);
	circle.SetRadius(area_s->circle.radius);

	return circle;
}

void HereUtils::Convert(String strUtf8, WString& strUtf16)
{
	strUtf16.assign(strUtf8.begin(), strUtf8.end());
}

void HereUtils::Convert(WString strUtf16, String& strUtf8)
{
	strUtf8.assign(strUtf16.begin(), strUtf16.end());
}

GeoBoundingBox& HereUtils::Convert(const char *src, GeoBoundingBox &box)
{
	int i = 0;
	char *token, *next;
	double coord[4] = { 0.0, };

	token = strtok_r((char*)src, ",;", &next);
	while (token && i < 4)
	{
		coord[i++] = atof(token);
		token = strtok_r(NULL, ",;", &next);
	}
	box.SetTopLeft(GeoCoordinates(coord[0], coord[1]));
	box.SetBottomRight(GeoCoordinates(coord[2], coord[3]));
	return box;
}

bool HereUtils::IsValid(GeoCoordinates geoCoord)
{
	return IsValidCoord(geoCoord.GetLatitude(), geoCoord.GetLongitude());
}

bool HereUtils::IsValid(maps_coordinates_s geoCoord)
{
	return IsValidCoord(geoCoord.latitude, geoCoord.longitude);
}

bool HereUtils::IsValidCoord(double dLat, double dLng)
{
	return ((dLat <= LATITUDE_RANGE && dLat >= -LATITUDE_RANGE) &&
		(dLng <= LONGITUDE_RANGE && dLng >= -LONGITUDE_RANGE));
}

bool HereUtils::IsValid(maps_area_s hArea)
{
	if (hArea.type == MAPS_AREA_RECTANGLE)
	{
		return (HereUtils::IsValid(hArea.rect.top_left) &&
			HereUtils::IsValid(hArea.rect.bottom_right));
	}
	else if(hArea.type == MAPS_AREA_CIRCLE)
	{
		return HereUtils::IsValid(hArea.circle.center);
	}
	else
		return false;
}

const double HereUtils::ConvertDistance(const double originValue, maps_distance_unit_e destUnit)
{
	return ConvertDistance(originValue, MAPS_DISTANCE_UNIT_M, destUnit);
}

const double HereUtils::ConvertDistance(const double originValue, maps_distance_unit_e originUnit, maps_distance_unit_e destUnit)
{
	double meterConstant[MAPS_DISTANCE_UNIT_YD+1] = { 1.0, 0.001, 3.2808399, 1.0936133 };
	return originValue / meterConstant[originUnit] * meterConstant[destUnit];
}

HERE_PLUGIN_END_NAMESPACE
