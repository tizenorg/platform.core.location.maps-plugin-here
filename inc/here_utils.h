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

#ifndef _LOCATION_HERE_UTILS_H_
#define _LOCATION_HERE_UTILS_H_

//common header
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>

//maps-service header
#include <maps_area.h>
#include <maps_preference.h>
#include <maps_route_maneuver.h>
#include <maps_service.h>
#include <map_view.h>

//plug-in header
#include "here_types.h"

//map engine header
#include <geocoder/GeoCoderQuery.h>
#include <finder/DiscoveryQuery.h>
#include <routes/GeoRouteQuery.h>
#include <routes/Maneuver.h>
#include <common/GeoCoordinates.h>
#include <common/GeoBoundingBox.h>
#include <common/GeoBoundingCircle.h>
#include <maps/GeoTiledMap.h>

#define HERE_PLUGIN_BEGIN_NAMESPACE  namespace Here { namespace PlugIn {
#define HERE_PLUGIN_END_NAMESPACE    }}
#define HERE_PLUGIN_NAMESPACE_PREFIX Here::PlugIn

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "HERE_PLUGIN"

/*
* Internal Macros
*/
#define MAPS_LOGD(fmt,args...)  LOGD(fmt, ##args)
#define MAPS_LOGW(fmt,args...)  LOGW(fmt, ##args)
#define MAPS_LOGI(fmt,args...)  LOGI(fmt, ##args)
#define MAPS_LOGE(fmt,args...)  LOGE(fmt, ##args)
#define MAPS_SECLOG(fmt,args...)  SECURE_LOGD(fmt, ##args)

#define MAPS_CHECK_CONDITION(condition, error, msg)	\
	do { \
		if (condition) { \
		} else { \
			MAPS_LOGE("%s(0x%08x)", msg, error); \
			return error; \
		} \
	} while (0)

#define MAPS_NULL_ARG_CHECK_RETURN_FALSE(arg)\
	do { \
		if(arg != NULL) { \
		} else	{ \
			MAPS_LOGE("MAPS_ERROR_INVALID_PARAMETER");  \
			return false; };	\
	} while (0)

#define MAPS_NULL_ARG_CHECK(arg)	\
	MAPS_CHECK_CONDITION(arg != NULL,MAPS_ERROR_INVALID_PARAMETER,"MAPS_ERROR_INVALID_PARAMETER")

#define MAPS_PRINT_ERROR_CODE_RETURN(code) \
	do{ \
		MAPS_LOGE("%s(0x%08x)", #code, code); \
		return code;	\
	} while (0)

#ifndef TIZEN_MIGRATION
typedef std::string String;
typedef std::string Uri;
typedef std::wstring WString;
#endif

#define maps_item_list_items(item_list) g_list_length((GList*)(*(unsigned long*)item_list)  )

extern "C"
{
	int ConvertToMapsError(int nRet);
	int ConvertToHereError(int nRet);
	const char* ConverHereErrorToString(int nErr);
	const char* ConvertMapsErrorToChar(int nErr);
}

HERE_PLUGIN_BEGIN_NAMESPACE

using namespace HERE_MAPS_NAMESPACE_PREFIX;

class HereUtils
{
public:
	/**
	 *This is the default constructor for Geocoder.
	 */

	HereUtils();

	/**
	 *This is the default destructor for Geocoder.
	 */

	~HereUtils();

	static GeoRouteQuery::TravelMode Convert(maps_route_transport_mode_e nVal);
	static maps_route_transport_mode_e Convert(GeoRouteQuery::TravelMode nVal);
	static GeoRouteQuery::FeatureType Convert(maps_route_feature_e nVal);
	static GeoRouteQuery::FeatureWeight Convert(maps_route_feature_weight_e nVal);
	static Maneuver::InstructionDirection Convert(maps_route_turn_type_e nVal);
	static GeoTiledMap::MapType Convert(map_view_type_e nVal);
	static maps_route_turn_type_e Convert(Maneuver::InstructionDirection nVal);
	static GeoBoundingBox& Convert(maps_area_h hArea, GeoBoundingBox& Box);
	static maps_area_h& Convert(GeoBoundingBox Box, maps_area_h& hArea);
	static GeoBoundingCircle& Convert(maps_area_h hArea, GeoBoundingCircle& circle);
	static void Convert(String strUtf8, WString& strUtf16);
	static void Convert(WString strUtf16, String& strUtf8);
	static GeoBoundingBox& Convert(const char *src, GeoBoundingBox &box);
	static maps_error_e ConvertHttpCodeToMapsError(int nVal);
	static const double ConvertDistance(const double originValue, maps_distance_unit_e destUnit);
	static const double ConvertDistance(const double originValue, maps_distance_unit_e originUnit, maps_distance_unit_e destUnit);

	static bool IsValid(GeoCoordinates geoCoord);
	static bool IsValid(maps_coordinates_s geoCoord);
	static bool IsValidCoord(double dLat, double dLng);
	static bool IsValid(maps_area_s hArea);

private:
};

HERE_PLUGIN_END_NAMESPACE

#endif //_LOCATION_HERE_UTILS_H_
