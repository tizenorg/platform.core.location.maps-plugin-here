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

#include <stdio.h>
#include <stdlib.h>

#include <maps_plugin.h>
#include "here_api.h"
#include "here_types.h"
#include "here_utils.h"

extern "C"
{

EXPORT_API int maps_plugin_init(maps_plugin_h *plugin)
{
	if (!plugin)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginInit(plugin);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_shutdown(maps_plugin_h plugin)
{
	if (!plugin)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginShutdown(plugin);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_info(maps_plugin_info_h* info)
{
	if (!info)
		return MAPS_ERROR_INVALID_PARAMETER;

	maps_plugin_info_create(info);
	maps_plugin_info_set_provider_name(*info, "HERE");

	return MAPS_ERROR_NONE;
}

EXPORT_API int maps_plugin_set_provider_key(const char* provider_key)
{
	if (!provider_key)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginSetProviderKey(provider_key);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_provider_key(char** provider_key)
{
	if (!provider_key)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginGetProviderKey(provider_key);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_set_preference(maps_preference_h preference)
{
	if (!preference)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginSetPreference(preference);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_preference(maps_preference_h* preference)
{
	if (!preference)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginGetPreference(preference);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_is_service_supported(maps_service_e service, bool *supported)
{
	if (!supported)
		return MAPS_ERROR_INVALID_PARAMETER;

	switch(service)
	{
		case MAPS_SERVICE_GEOCODE:
		case MAPS_SERVICE_GEOCODE_INSIDE_AREA:
		case MAPS_SERVICE_GEOCODE_BY_STRUCTURED_ADDRESS:
		case MAPS_SERVICE_REVERSE_GEOCODE:
		case MAPS_SERVICE_SEARCH_PLACE:
		case MAPS_SERVICE_SEARCH_PLACE_BY_AREA:
		case MAPS_SERVICE_SEARCH_PLACE_BY_ADDRESS:
		case MAPS_SERVICE_SEARCH_ROUTE:
		case MAPS_SERVICE_SEARCH_ROUTE_WAYPOINTS:
		case MAPS_SERVICE_CANCEL_REQUEST:
			*supported = TRUE;
			return MAPS_ERROR_NONE;
		default:
			*supported = FALSE;
			return MAPS_ERROR_NOT_SUPPORTED;
	}
}

EXPORT_API int maps_plugin_is_data_supported(maps_service_data_e service, bool *supported)
{
	if (!supported)
		return MAPS_ERROR_INVALID_PARAMETER;

	switch(service)
	{
		case MAPS_PLACE_ADDRESS:
		case MAPS_PLACE_RATING:
		case MAPS_PLACE_CATEGORIES:
		case MAPS_PLACE_ATTRIBUTES:
		case MAPS_PLACE_CONTACTS:
		case MAPS_PLACE_EDITORIALS:
		case MAPS_PLACE_REVIEWS:
		case MAPS_PLACE_IMAGE:
		case MAPS_PLACE_SUPPLIER:
		case MAPS_PLACE_RELATED:
		case MAPS_ROUTE_PATH:
		case MAPS_ROUTE_SEGMENTS_PATH:
		case MAPS_ROUTE_SEGMENTS_MANEUVERS:
			*supported = TRUE;
			return MAPS_ERROR_NONE;
		default:
			*supported = FALSE;
			return MAPS_ERROR_NOT_SUPPORTED;
	}
}

EXPORT_API int maps_plugin_geocode(const char* address, const maps_preference_h preference,
	maps_service_geocode_cb callback, void *user_data, int* request_id)
{
	if (!address || !callback || !request_id)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginGeocode(address, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_geocode_inside_area(const char* address, const maps_area_h bounds,
	const maps_preference_h preference, maps_service_geocode_cb callback,
	void* user_data, int* request_id)
{
	if (!bounds || !address || !callback || !request_id)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginGeocodeInsideArea(address, bounds, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_geocode_by_structured_address(const maps_address_h address,
	const maps_preference_h preference, maps_service_geocode_cb callback,
	void *user_data, int* request_id)
{
	if (!address || !callback || !request_id)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginGeocodeByStructuredAddress(address, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_reverse_geocode(double latitude, double longitude,
	const maps_preference_h preference, maps_service_reverse_geocode_cb callback,
	void *user_data, int* request_id)
{
	if (!callback || !request_id)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginReverseGeocode(latitude, longitude, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_place(const maps_coordinates_h position, int distance,
	const maps_place_filter_h filter, maps_preference_h preference, maps_service_search_place_cb callback,
	void* user_data, int* request_id)
{
	if (!position || !filter || !callback || !request_id)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginSearchPlace(position, distance, preference, filter, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_place_by_area(const maps_area_h boundary,
	const maps_place_filter_h filter, maps_preference_h preference, maps_service_search_place_cb callback,
	void* user_data, int* request_id)
{
	if (!boundary || !filter || !callback || !request_id)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginSearchPlaceByArea(boundary, preference, filter, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_place_by_address(const char* address, const maps_area_h boundary,
	const maps_place_filter_h filter, maps_preference_h preference, maps_service_search_place_cb callback,
	void* user_data, int* request_id)
{
	if (!address || !boundary || !filter || !callback || !request_id)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginSearchPlaceByAddress(address, boundary, preference, filter, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_route(const maps_coordinates_h origin, const maps_coordinates_h destination,
	maps_preference_h preference, maps_service_search_route_cb callback,
	void* user_data, int* request_id)
{
	if (!origin || !destination || !callback || !request_id)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginSearchRoute(origin, destination, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_route_waypoints(const maps_coordinates_h* waypoint_list, int waypoint_num,
	maps_preference_h preference, maps_service_search_route_cb callback,
	void* user_data, int* request_id)
{
	if (!waypoint_list || waypoint_num <= 0 || !callback || !request_id)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginSearchRouteWaypoints(waypoint_list, waypoint_num, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_cancel_request(int request_id)
{
	if (request_id < 0)
		return MAPS_ERROR_INVALID_PARAMETER;

	int ret = HerePluginCancelRequest(request_id);

	MAPS_LOGD("here_error_e = %d", ret);

	return ConvertToMapsError(ret);
}

} // end of extern "C"

