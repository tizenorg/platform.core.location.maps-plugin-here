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
#ifndef _LOCATION_HERE_API_H_
#define _LOCATION_HERE_API_H_

#include <maps_plugin.h>
#include <maps_view_plugin.h>

int HerePluginInit(maps_plugin_h *hPlugin, const char *module = NULL);

int HerePluginShutdown(maps_plugin_h hPlugin);

int HerePluginSetProviderKey(const char* szKey);

int HerePluginGetProviderKey(char** szKey);

int HerePluginSetPreference(maps_preference_h hPref);

int HerePluginGetPreference(maps_preference_h *hPref);

int HerePluginGeocode(const char* szAddr,
	maps_item_hashtable_h hPref, maps_service_geocode_cb pCbFunc,
	void *pUserData, int *nReqId);

int HerePluginGeocodeByStructuredAddress(const maps_address_h hAddr,
	maps_item_hashtable_h hPref, maps_service_geocode_cb pCbFunc,
	void *pUserData, int *nReqId);

int HerePluginGeocodeInsideArea(const char* szAddr, maps_area_h hArea,
	maps_item_hashtable_h hPref, maps_service_geocode_cb pCbFunc,
	void *pUserData, int *nReqId);

int HerePluginReverseGeocode(double dLatitude, double dLongitude,
	maps_item_hashtable_h hPref, maps_service_reverse_geocode_cb pCbFunc,
	void *pUserData, int *nReqId);

int HerePluginMultiReverseGeocode(const maps_coordinates_list_h hGeocodeList,
	maps_item_hashtable_h hPref, maps_service_multi_reverse_geocode_cb pCbFunc,
	void *pUserData, int *nReqId);

int HerePluginSearchPlace(maps_coordinates_h hPos, int nDistance,
	maps_item_hashtable_h hPref, maps_place_filter_h hFilter, maps_service_search_place_cb pCbFunc,
	void * pUserData, int *nReqId);

int HerePluginSearchPlaceByArea(maps_area_h hArea,
	maps_item_hashtable_h hPref, maps_place_filter_h hFilter, maps_service_search_place_cb pCbFunc,
	void * pUserData, int *nReqId);

int HerePluginSearchPlaceByAddress(const char* szAddr, maps_area_h hArea,
	maps_item_hashtable_h hPref, maps_place_filter_h hFilter, maps_service_search_place_cb pCbFunc,
	void * pUserData, int *nReqId);

int HerePluginSearchPlaceList(maps_area_h hArea, maps_item_hashtable_h hPref,
	maps_place_filter_h hFilter, maps_service_search_place_list_cb pCbFunc,
	void * pUserData, int *nReqId);

int HerePluginSearchPlaceDetails(const char* szUrl,
	maps_service_get_place_details_cb pCbFunc,
	void * pUserData, int *nReqId);

int HerePluginSearchRoute(maps_coordinates_h hOrigin, maps_coordinates_h hDestination,
	maps_item_hashtable_h hPref, maps_service_search_route_cb pCbFunc,
	void *pUserData, int *nReqId);

int HerePluginSearchRouteWaypoints(const maps_coordinates_h* hWaypointList, int nWaypointNum,
	maps_item_hashtable_h hPref, maps_service_search_route_cb pCbFunc,
	void* pUserData, int *nReqId);

int HerePluginCancelRequest(int nReqId);

/* Mapping API */

int HerePluginCreateMapView(maps_view_h hView, maps_plugin_map_view_ready_cb pCbFunc);

int HerePluginDestroyMapView(maps_view_h hView);

int HerePluginRenderMap(maps_view_h hView, const maps_coordinates_h mapsCoord, double dZoom, double dAngle);

int HerePluginMoveCenter(maps_view_h hView, int delta_x, int delta_y);

int HerePluginSetScalebar(maps_view_h hView, bool enable);

int HerePluginGetScalebar(maps_view_h hView, bool *enabled);

int HerePluginGetCenter(maps_view_h hView, maps_coordinates_h *center);

int HerePluginScreenToGeography(maps_view_h hView, int x, int y, maps_coordinates_h *mapsCoord);

int HerePluginGeographyToScreen(maps_view_h hView, const maps_coordinates_h mapsCoord, int *x, int *y);

int HerePluginGetMinZoomLevel(maps_view_h hView, int *nMinZoomLevel);

int HerePluginGetMaxZoomLevel(maps_view_h hView, int *nMaxZoomLevel);

int HerePluginOnViewObject(maps_view_h hView, const maps_view_object_h object, maps_view_object_operation_e operation);

int HerePluginCaptureSnapshot(maps_view_h hView, void **data, int *w, int *h, maps_view_colorspace_type_e *cs);

#endif //_LOCATION_HERE_API_H_