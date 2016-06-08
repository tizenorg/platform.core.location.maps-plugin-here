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

#include "here_api.h"
#include "here_types.h"
#include "here_geocode.h"
#include "here_revgeocode.h"
#include "here_multirevgeocode.h"
#include "here_place.h"
#include "here_route.h"
#include "here_view.h"
#include <common/HereConfig.h>

using namespace HERE_PLUGIN_NAMESPACE_PREFIX;

int HerePluginInit(maps_plugin_h *hPlugin, const char *module)
{
	if (!hPlugin)
		return HERE_ERROR_INVALID_PARAMETER;

	here_error_e error = HereManager::CheckAgreement();
	if (error != HERE_ERROR_NONE)
		return error;

	HereManager::Create();

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	HereManager::GetHandler()->SetProxyAddress();

	return HERE_ERROR_NONE;
}

int HerePluginShutdown(maps_plugin_h hPlugin)
{
	if (!hPlugin)
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::GetHandler())
		HereManager::GetHandler()->Close();

	return HERE_ERROR_NONE;
}

int HerePluginSetProviderKey(const char* szKey)
{
	if (!szKey)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	return HereManager::GetHandler()->SetCredentials(szKey);
}

int HerePluginGetProviderKey(char** szKey)
{
	if (!szKey)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	return HereManager::GetHandler()->GetCredentials(szKey);
}

int HerePluginSetPreference(maps_preference_h hPref)
{
	if (!hPref)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	return HereManager::GetHandler()->SetPreference(hPref);
}

int HerePluginGetPreference(maps_preference_h *hPref)
{
	if (!hPref)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	return HereManager::GetHandler()->GetPreference(hPref);
}

int HerePluginGeocode(const char* szAddr,
	maps_item_hashtable_h hPref, maps_service_geocode_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!szAddr || (szAddr && *szAddr == '\0') || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HereGeocode *pGeocode =
		(HereGeocode*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_GEOCODE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pGeocode)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pGeocode->PrepareQuery();
		if (error != HERE_ERROR_NONE) break;

		error = pGeocode->PreparePreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error = pGeocode->StartGeocode(szAddr);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pGeocode->TerminateService();

	return error;
}

int HerePluginGeocodeByStructuredAddress(const maps_address_h hAddr,
	maps_item_hashtable_h hPref, maps_service_geocode_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!hAddr || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HereGeocode *pGeocode =
		(HereGeocode*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_GEOCODE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pGeocode)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pGeocode->PrepareQuery();
		if (error != HERE_ERROR_NONE) break;

		error = pGeocode->PreparePreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error = pGeocode->StartGeocodeByStructuredAddress(hAddr);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pGeocode->TerminateService();

	return error;
}

int HerePluginGeocodeInsideArea(const char* szAddr, maps_area_h hArea,
	maps_item_hashtable_h hPref, maps_service_geocode_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!szAddr || (szAddr && *szAddr == '\0') || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!hArea || !HereUtils::IsValid(*(maps_area_s*)hArea))
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HereGeocode *pGeocode =
		(HereGeocode*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_GEOCODE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pGeocode)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pGeocode->PrepareQuery();
		if (error != HERE_ERROR_NONE) break;

		error = pGeocode->PreparePreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error = pGeocode->StartGeocodeInsideArea(szAddr, hArea);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pGeocode->TerminateService();

	return error;
}

int HerePluginReverseGeocode(double dLatitude, double dLongitude,
	maps_item_hashtable_h hPref, maps_service_reverse_geocode_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!HereUtils::IsValidCoord(dLatitude, dLongitude))
		return HERE_ERROR_INVALID_PARAMETER;

	if (!pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HereRevGeocode *pRevGeocode =
		(HereRevGeocode*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_REV_GEOCODE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pRevGeocode)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_UNKNOWN;

	do {
		error = pRevGeocode->PrepareQuery();
		if (error != HERE_ERROR_NONE) break;

		error = pRevGeocode->PreparePreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error = pRevGeocode->PreparePosition(dLatitude, dLongitude);
		if (error != HERE_ERROR_NONE) break;

		error = pRevGeocode->StartRevGeocode(hPref);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pRevGeocode->TerminateService();

	return error;
}

int HerePluginMultiReverseGeocode(const maps_coordinates_list_h hGeocodeList,
	maps_item_hashtable_h hPref, maps_service_multi_reverse_geocode_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!hGeocodeList || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HereMultiRevGeocode *pMultiRevGeocode =
		(HereMultiRevGeocode*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_MULTI_REV_GEOCODE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pMultiRevGeocode)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_UNKNOWN;

	do {
		error = pMultiRevGeocode->PrepareQuery();
		if (error != HERE_ERROR_NONE) break;

		error = pMultiRevGeocode->PreparePositionList(hGeocodeList);
		if (error != HERE_ERROR_NONE) break;

		error = pMultiRevGeocode->StartMultiReverse(hPref);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pMultiRevGeocode->TerminateService();

	return error;
}

int HerePluginSearchPlace(maps_coordinates_h hPos, int nDistance,
	maps_item_hashtable_h hPref, maps_place_filter_h hFilter, maps_service_search_place_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!hPos || !HereUtils::IsValid(*(maps_coordinates_s*)hPos) || nDistance <= 0)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!hFilter || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HerePlace *pPlace =
		(HerePlace*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_PLACE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pPlace)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pPlace->PrepareDiscoveryQuery();
		if (error != HERE_ERROR_NONE) break;

		error =	pPlace->PrepareDiscoveryPreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error =	pPlace->PrepareDiscoveryFilter(hFilter);
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->StartDiscoveryPlace(hPos, nDistance);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pPlace->TerminateService();

	return error;
}

int HerePluginSearchPlaceByArea(maps_area_h hArea,
	maps_item_hashtable_h hPref, maps_place_filter_h hFilter, maps_service_search_place_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!hArea || !HereUtils::IsValid(*(maps_area_s*)hArea))
		return HERE_ERROR_INVALID_PARAMETER;

	if (!hFilter || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HerePlace *pPlace =
		(HerePlace*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_PLACE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pPlace)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pPlace->PrepareDiscoveryQuery();
		if (error != HERE_ERROR_NONE) break;

		error =	pPlace->PrepareDiscoveryPreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error =	pPlace->PrepareDiscoveryFilter(hFilter);
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->StartDiscoveryPlace(hArea);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pPlace->TerminateService();

	return error;
}

int HerePluginSearchPlaceByAddress(const char* szAddr, maps_area_h hArea,
	maps_item_hashtable_h hPref, maps_place_filter_h hFilter, maps_service_search_place_cb pCbFunc,
	void * pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!szAddr || (szAddr && *szAddr == '\0') || !hFilter || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!hArea || !HereUtils::IsValid(*(maps_area_s*)hArea))
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HerePlace *pPlace =
		(HerePlace*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_PLACE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pPlace)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pPlace->PrepareDiscoveryQuery();
		if (error != HERE_ERROR_NONE) break;

		error =	pPlace->PrepareDiscoveryPreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error =	pPlace->PrepareDiscoveryFilter(hFilter);
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->StartDiscoveryPlace(hArea, szAddr);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pPlace->TerminateService();

	return error;
}

int HerePluginSearchPlaceList(maps_area_h hArea, maps_item_hashtable_h hPref,
	maps_place_filter_h hFilter, maps_service_search_place_list_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!hFilter || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!hArea || !HereUtils::IsValid(*(maps_area_s*)hArea))
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HerePlace *pPlace =
		(HerePlace*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_PLACE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pPlace)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pPlace->PrepareDiscoveryQuery();
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->PrepareDiscoveryPreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->PrepareDiscoveryFilter(hFilter);
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->StartDiscoveryPlaceList(hArea);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pPlace->TerminateService();

	return error;
}

int HerePluginSearchPlaceDetails(const char* szUrl,
	maps_service_get_place_details_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!szUrl || (szUrl && *szUrl == '\0') || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HerePlace *pPlace =
		(HerePlace*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_PLACE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pPlace)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pPlace->PreparePlaceDetailsQuery();
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->StartPlaceDetails(szUrl);
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pPlace->TerminateService();

	return error;
}

int HerePluginSearchRoute(maps_coordinates_h hOrigin, maps_coordinates_h hDestination,
	maps_item_hashtable_h hPref, maps_service_search_route_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!hOrigin || !hDestination || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!HereUtils::IsValid(*(maps_coordinates_s*)hOrigin) ||
		!HereUtils::IsValid(*(maps_coordinates_s*)hDestination))
		return HERE_ERROR_INVALID_PARAMETER;

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HereRoute *pRoute =
		(HereRoute*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_ROUTE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pRoute)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pRoute->PrepareQuery();
		if (error != HERE_ERROR_NONE) break;

		error = pRoute->PreparePreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error = pRoute->PrepareWaypoint(hOrigin, hDestination);
		if (error != HERE_ERROR_NONE) break;

		error = pRoute->StartRoute();
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pRoute->TerminateService();

	return error;
}

int HerePluginSearchRouteWaypoints(const maps_coordinates_h* hWaypointList, int nWaypointNum,
	maps_item_hashtable_h hPref, maps_service_search_route_cb pCbFunc,
	void* pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!hWaypointList || nWaypointNum < 2 || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

	for (int i = 0; i < nWaypointNum; i++)
	{
		if (!HereUtils::IsValid(*(maps_coordinates_s*)hWaypointList[i]))
			return HERE_ERROR_INVALID_PARAMETER;
	}

	if (HereManager::CheckAgreement() != HERE_ERROR_NONE)
		return HERE_ERROR_PERMISSION_DENIED;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	/* creating instance */
	HereRoute *pRoute =
		(HereRoute*)(HereManager::GetHandler()->CreateInstance(HereManager::HERE_SVC_ROUTE,
		(void*)pCbFunc, pUserData, nReqId));

	if(!pRoute)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* sending request */
	here_error_e error = HERE_ERROR_NONE;

	do {
		error = pRoute->PrepareQuery();
		if (error != HERE_ERROR_NONE) break;

		error = pRoute->PrepareWaypoint(hWaypointList, nWaypointNum);
		if (error != HERE_ERROR_NONE) break;

		error = pRoute->PreparePreference(hPref);
		if (error != HERE_ERROR_NONE) break;

		error = pRoute->StartRoute();
	} while (0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pRoute->TerminateService();

	return error;
}

int HerePluginCancelRequest(int nReqId)
{
	if (nReqId <= 0)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	return (HereManager::GetHandler()->CancelInstance(nReqId));
}



/*****************************************************************************/
/*                                                                           */
/*  Maps Widget                                                              */
/*                                                                           */
/*****************************************************************************/

int HerePluginCreateMapView(maps_view_h hView, maps_plugin_map_view_ready_cb pCbFunc)
{
	HereView *vh = NULL, *ovh = NULL;
	vh = new HereView();
	if (!vh) return HERE_ERROR_OUT_OF_MEMORY;
	maps_view_get_maps_plugin_view_handle(hView, (void**)&ovh);
	maps_view_set_maps_plugin_view_handle(hView, vh);
	if (ovh)
		delete ovh;
	return vh->init(hView, pCbFunc);
}

int HerePluginDestroyMapView(maps_view_h hView)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh) {
		maps_view_set_maps_plugin_view_handle(hView, NULL);
		error = vh->close(hView);
		delete vh;
	}
	return error;
}

int HerePluginRenderMap(maps_view_h hView, const maps_coordinates_h mapsCoord,
	double dZoom, double dAngle)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->renderMap(hView, mapsCoord, dZoom, dAngle);
	return error;
}

int HerePluginMoveCenter(maps_view_h hView, int delta_x, int delta_y)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->moveCenter(hView, delta_x, delta_y);
	return error;
}

int HerePluginSetScalebar(maps_view_h hView, bool enable)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->setScalebarEnabled(hView, enable);
	return error;
}

int HerePluginGetScalebar(maps_view_h hView, bool *enabled)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->getScalebarEnabled(hView, enabled);
	return error;
}

int HerePluginGetCenter(maps_view_h hView, maps_coordinates_h *center)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->getCenter(hView, center);
	return error;
}

int HerePluginScreenToGeography(maps_view_h hView, int x, int y, maps_coordinates_h *mapsCoord)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->convertScreenToGeolocation(hView, x, y, mapsCoord);
	return error;
}

int HerePluginGeographyToScreen(maps_view_h hView, const maps_coordinates_h mapsCoord, int *x, int *y)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->convertGeolocationToScreen(hView, mapsCoord, x, y);
	return error;
}

int HerePluginGetMinZoomLevel(maps_view_h hView, int *nMinZoomLevel)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->getMinZoomLevel(hView, nMinZoomLevel);
	return error;
}

int HerePluginGetMaxZoomLevel(maps_view_h hView, int *nMaxZoomLevel)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->getMaxZoomLevel(hView, nMaxZoomLevel);
	return error;
}

int HerePluginOnViewObject(maps_view_h hView, const maps_view_object_h object,
	maps_view_object_operation_e operation)
{
	HereView *vh = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(hView, (void**)&vh);
	here_error_e error = (here_error_e)ConvertToHereError(maps_error);
	if (error == HERE_ERROR_NONE && vh)
		error = vh->onViewObject(hView, object, operation);
	return error;
}
