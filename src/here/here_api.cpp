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
#include "here_place.h"
#include "here_route.h"
#include <common/HereConfig.h>


using namespace HERE_PLUGIN_NAMESPACE_PREFIX;

int HerePluginInit(maps_plugin_h *hPlugin)
{
	if (!hPlugin)
		return HERE_ERROR_INVALID_PARAMETER;

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

	here_error_e error = HereManager::GetHandler()->SetCredentials(szKey);

	return error;
}

int HerePluginGetProviderKey(char** szKey)
{
	if (!szKey)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	here_error_e error = HereManager::GetHandler()->GetCredentials(szKey);

	return error;
}

int HerePluginSetPreference(maps_preference_h hPref)
{
	if (!hPref)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	here_error_e error = HereManager::GetHandler()->SetPreference(hPref);

	return error;
}

int HerePluginGetPreference(maps_preference_h *hPref)
{
	if (!hPref)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!HereManager::GetHandler())
		return HERE_ERROR_INVALID_OPERATION;

	here_error_e error = HereManager::GetHandler()->GetPreference(hPref);

	return error;
}

int HerePluginGeocode(const char* szAddr,
	maps_item_hashtable_h hPref, maps_service_geocode_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!szAddr || (szAddr && *szAddr == '\0') || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

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

		error = pGeocode->StartGeocode(szAddr);
	} while(0);

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

		error = pGeocode->StartGeocodeByStructuredAddress(hAddr);
	} while(0);

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

		error = pGeocode->StartGeocodeInsideArea(szAddr, hArea);
	} while(0);

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

		error = pRevGeocode->PreparePosition(dLatitude, dLongitude);
		if (error != HERE_ERROR_NONE) break;

		error = pRevGeocode->StartRevGeocode(hPref);
	} while(0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pRevGeocode->TerminateService();

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

		error =	pPlace->PrepareDiscoveryFilter(hFilter);
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->StartDiscoveryPlace(hPos, nDistance);
	} while(0);

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

		error =	pPlace->PrepareDiscoveryFilter(hFilter);
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->StartDiscoveryPlaceByArea(hArea);
	} while(0);

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

		error =	pPlace->PrepareDiscoveryFilter(hFilter);
		if (error != HERE_ERROR_NONE) break;

		error = pPlace->StartDiscoveryPlaceByAddress(szAddr, hArea);
	} while(0);

	/* finishing task */
	if(error != HERE_ERROR_NONE)
		pPlace->TerminateService();

	return error;
}

int HerePluginSearchPlaceDetails(const char* szUrl,
	maps_item_hashtable_h hPref, maps_service_search_place_cb pCbFunc,
	void *pUserData, int *nReqId)
{
	/* checking parmaters */
	if (!szUrl || (szUrl && *szUrl == '\0') || !pCbFunc || !nReqId)
		return HERE_ERROR_INVALID_PARAMETER;

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

		error = pPlace->PreparePlaceDetailsPreference(hPref);

		error = pPlace->StartPlaceDetails(szUrl);
	} while(0);

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

		error = pRoute->PrepareWaypoint(hOrigin, hDestination);
		if (error != HERE_ERROR_NONE) break;

		error = pRoute->StartRoute();
	} while(0);

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

	for (int i=0; i<nWaypointNum; i++)
	{
		if (!HereUtils::IsValid(*(maps_coordinates_s*)hWaypointList[i]))
			return HERE_ERROR_INVALID_PARAMETER;
	}

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

		error = pRoute->StartRoute();
	} while(0);

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
