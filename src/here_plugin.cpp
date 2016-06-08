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
	int ret = HerePluginInit(plugin);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_init_module(maps_plugin_h *plugin, const char *module)
{
	int ret = HerePluginInit(plugin, module);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_shutdown(maps_plugin_h plugin)
{
	int ret = HerePluginShutdown(plugin);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_info(maps_plugin_info_h* info)
{
	int ret = maps_plugin_info_create(info);

	if (ret == MAPS_ERROR_NONE)
		ret = maps_plugin_info_set_provider_name(*info, "HERE");

	return ret;
}

EXPORT_API int maps_plugin_set_provider_key(const char* provider_key)
{
	int ret = HerePluginSetProviderKey(provider_key);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_provider_key(char** provider_key)
{
	int ret = HerePluginGetProviderKey(provider_key);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_set_preference(maps_preference_h preference)
{
	int ret = HerePluginSetPreference(preference);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_preference(maps_preference_h* preference)
{
	int ret = HerePluginGetPreference(preference);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

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
		case MAPS_SERVICE_MULTI_REVERSE_GEOCODE:
		case MAPS_SERVICE_SEARCH_PLACE_LIST:
		case MAPS_SERVICE_SEARCH_GET_PLACE_DETAILS:
		case MAPS_SERVICE_VIEW:
			*supported = TRUE;
			break;
		default:
			*supported = FALSE;
			break;
	}
	return MAPS_ERROR_NONE;
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
		case MAPS_VIEW_TRAFFIC:
		case MAPS_VIEW_PUBLIC_TRANSIT:
		case MAPS_VIEW_SCALEBAR:
			*supported = TRUE;
			break;
		case MAPS_VIEW_BUILDING:
		default:
			*supported = FALSE;
			break;
	}
	return MAPS_ERROR_NONE;
}

EXPORT_API int maps_plugin_geocode(const char* address, const maps_preference_h preference,
	maps_service_geocode_cb callback, void *user_data, int* request_id)
{
	int ret = HerePluginGeocode(address, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_geocode_inside_area(const char* address, const maps_area_h bounds,
	const maps_preference_h preference, maps_service_geocode_cb callback,
	void* user_data, int* request_id)
{
	int ret = HerePluginGeocodeInsideArea(address, bounds, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_geocode_by_structured_address(const maps_address_h address,
	const maps_preference_h preference, maps_service_geocode_cb callback,
	void *user_data, int* request_id)
{
	int ret = HerePluginGeocodeByStructuredAddress(address, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_reverse_geocode(double latitude, double longitude,
	const maps_preference_h preference, maps_service_reverse_geocode_cb callback,
	void *user_data, int* request_id)
{
	int ret = HerePluginReverseGeocode(latitude, longitude, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_multi_reverse_geocode(const maps_coordinates_list_h geocode_list,
	const maps_preference_h preference, maps_service_multi_reverse_geocode_cb callback,
	void *user_data, int *request_id)
{
	int ret = HerePluginMultiReverseGeocode(geocode_list, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_place(const maps_coordinates_h position, int distance,
	const maps_place_filter_h filter, maps_preference_h preference, maps_service_search_place_cb callback,
	void* user_data, int* request_id)
{
	int ret = HerePluginSearchPlace(position, distance, preference, filter, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_place_by_area(const maps_area_h boundary,
	const maps_place_filter_h filter, maps_preference_h preference, maps_service_search_place_cb callback,
	void* user_data, int* request_id)
{
	int ret = HerePluginSearchPlaceByArea(boundary, preference, filter, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_place_by_address(const char* address, const maps_area_h boundary,
	const maps_place_filter_h filter, maps_preference_h preference, maps_service_search_place_cb callback,
	void* user_data, int* request_id)
{
	int ret = HerePluginSearchPlaceByAddress(address, boundary, preference, filter, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_place_list(const maps_area_h boundary, const maps_place_filter_h filter,
	maps_preference_h preference, maps_service_search_place_list_cb callback, void* user_data, int* request_id)
{
	int ret = HerePluginSearchPlaceList(boundary, preference, filter, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_place_details(const char* url,
	maps_service_get_place_details_cb callback, void* user_data, int* request_id)
{
	int ret = HerePluginSearchPlaceDetails(url, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_route(const maps_coordinates_h origin, const maps_coordinates_h destination,
	maps_preference_h preference, maps_service_search_route_cb callback, void* user_data, int* request_id)
{
	int ret = HerePluginSearchRoute(origin, destination, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_search_route_waypoints(const maps_coordinates_h* waypoint_list, int waypoint_num,
	maps_preference_h preference, maps_service_search_route_cb callback,
	void* user_data, int* request_id)
{
	int ret = HerePluginSearchRouteWaypoints(waypoint_list, waypoint_num, preference, callback, user_data, request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_cancel_request(int request_id)
{
	int ret = HerePluginCancelRequest(request_id);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

/* Mapping */
EXPORT_API int maps_plugin_create_map_view(maps_view_h hView, maps_plugin_map_view_ready_cb pCbFunc)
{
	int ret = HerePluginCreateMapView(hView, pCbFunc);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_destroy_map_view(maps_view_h hView)
{
	int ret = HerePluginDestroyMapView(hView);

	MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_render_map(maps_view_h hView,
	const maps_coordinates_h coordinates, double zoom_factor, double rotation_angle)
{
	int ret = HerePluginRenderMap(hView, coordinates, zoom_factor, rotation_angle);

	if (ret != HERE_ERROR_NONE)
		MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_move_center(maps_view_h hView, int delta_x, int delta_y)
{
	int ret = HerePluginMoveCenter(hView, delta_x, delta_y);

	if (ret != HERE_ERROR_NONE)
		MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_set_scalebar(maps_view_h hView, bool enable)
{
	int ret = HerePluginSetScalebar(hView, enable);

	if (ret != HERE_ERROR_NONE)
		MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_scalebar(maps_view_h hView, bool *enabled)
{
	int ret = HerePluginGetScalebar(hView, enabled);
	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_on_object(maps_view_h hView, const maps_view_object_h object, maps_view_object_operation_e operation)
{
	int ret = HerePluginOnViewObject(hView, object, operation);

	if (ret != HERE_ERROR_NONE)
		MAPS_LOGD("here_error_e = %d, %s", ret, ConverHereErrorToString(ret));

	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_screen_to_geography(maps_view_h hView, int x, int y, maps_coordinates_h *mapsCoord)
{
	int ret = HerePluginScreenToGeography(hView, x, y, mapsCoord);
	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_geography_to_screen(maps_view_h hView, const maps_coordinates_h mapsCoord, int* x, int* y)
{
	int ret = HerePluginGeographyToScreen(hView, mapsCoord, x, y);
	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_min_zoom_level(maps_view_h hView, int *min_zoom_level)
{
	int ret = HerePluginGetMinZoomLevel(hView, min_zoom_level);
	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_max_zoom_level(maps_view_h hView, int *max_zoom_level)
{
	int ret = HerePluginGetMaxZoomLevel(hView, max_zoom_level);
	return ConvertToMapsError(ret);
}

EXPORT_API int maps_plugin_get_center(maps_view_h hView, maps_coordinates_h *center)
{
	int ret = HerePluginGetCenter(hView, center);
	return ConvertToMapsError(ret);
}

} // end of extern "C"

