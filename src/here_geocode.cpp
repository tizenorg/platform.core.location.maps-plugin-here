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

#include "here_geocode.h"

HERE_PLUGIN_BEGIN_NAMESPACE

HereGeocode::HereGeocode(void *pCbFunc, void *pUserData, int nReqId)
{
	m_pQuery = NULL;

	m_pCbFunc = pCbFunc;
	m_pUserData = pUserData;
	m_nReqId = nReqId;
}

HereGeocode::~HereGeocode()
{
	if (m_pQuery)
	{
		delete m_pQuery;
		m_pQuery = NULL;
	}
}

here_error_e HereGeocode::PrepareQuery()
{
	if (m_pQuery)
		return HERE_ERROR_PERMISSION_DENIED;

	m_pQuery = new (std::nothrow) GeoCoderQuery();

	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;
	else
		return HERE_ERROR_NONE;
}

here_error_e HereGeocode::PreparePreference(maps_preference_h hPref)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hPref)
		return HERE_ERROR_NONE;

	int ret;
	char *szLanguage = NULL;
	ret = maps_preference_get_language(hPref, &szLanguage);
	if (ret == MAPS_ERROR_NONE && szLanguage && *szLanguage)
	{
		m_pQuery->AppendPreferredLanguage(szLanguage);
		g_free(szLanguage);
	}

	int nMaxResults;
	ret = maps_preference_get_max_results(hPref, &nMaxResults);
	if (ret == MAPS_ERROR_NONE)
	{
		m_pQuery->SetMaxResults((size_t)nMaxResults);
	}

	return HERE_ERROR_NONE;
}

here_error_e HereGeocode::StartGeocode(const char* szAddr)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!szAddr || (szAddr && strlen(szAddr) <= 0))
		return HERE_ERROR_INVALID_PARAMETER;


	String sSearch(szAddr);
	m_pQuery->SetSearchtext(sSearch);


	m_nRestReqId = m_pQuery->Execute(*this, NULL);

	return (m_nRestReqId > 0 ? HERE_ERROR_NONE : HERE_ERROR_INVALID_OPERATION);
}

here_error_e HereGeocode::StartGeocodeInsideArea(const char* szAddr, const maps_area_h hArea)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!szAddr || (szAddr && strlen(szAddr) <= 0) || !hArea)
		return HERE_ERROR_INVALID_PARAMETER;


	String sSearch(szAddr);
	m_pQuery->SetSearchtext(sSearch);

	maps_area_s *pArea = (maps_area_s *)hArea;
	if (pArea->type == MAPS_AREA_RECTANGLE) {
		double dLatTL = pArea->rect.top_left.latitude;
		double dLngTL = pArea->rect.top_left.longitude;
		GeoCoordinates geoCoordTL(dLatTL, dLngTL);

		double dLatBR = pArea->rect.bottom_right.latitude;
		double dLngBR = pArea->rect.bottom_right.longitude;
		GeoCoordinates geoCoordBR(dLatBR, dLngBR);

		GeoBoundingBox BoundingBox(geoCoordTL, geoCoordBR);

		m_pQuery->SetBoundingBox(BoundingBox);
	} else if (pArea->type == MAPS_AREA_CIRCLE) {
		MAPS_LOGD("HERE Maps is not supported circle type in GeocoderQuery");
		return HERE_ERROR_NOT_SUPPORTED;
	} else {
		return HERE_ERROR_INVALID_PARAMETER;
	}


	m_nRestReqId = m_pQuery->Execute(*this, NULL);

	return (m_nRestReqId > 0 ? HERE_ERROR_NONE : HERE_ERROR_INVALID_OPERATION);
}

here_error_e HereGeocode::StartGeocodeByStructuredAddress(const maps_address_h hAddr)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hAddr)
		return HERE_ERROR_INVALID_PARAMETER;


	Address rAddress;

	int ret;
	char *szCountry = NULL;
	ret = maps_address_get_country(hAddr, &szCountry);
	if (ret == MAPS_ERROR_NONE && szCountry && *szCountry)
		rAddress.SetCountry(String(szCountry));
	g_free(szCountry);

	char *szCountryCode = NULL;
	ret = maps_address_get_country_code(hAddr, &szCountryCode);
	if (ret == MAPS_ERROR_NONE && szCountryCode && *szCountryCode)
		rAddress.SetCountryCode(String(szCountryCode));
	g_free(szCountryCode);

	char *szCounty = NULL;
	ret = maps_address_get_county(hAddr, &szCounty);
	if (ret == MAPS_ERROR_NONE && szCounty && *szCounty)
		rAddress.SetCounty(String(szCounty));
	g_free(szCounty);

	char *szState = NULL;
	ret = maps_address_get_state(hAddr, &szState);
	if (ret == MAPS_ERROR_NONE && szState && *szState)
		rAddress.SetState(String(szState));
	g_free(szState);

	char *szCity = NULL;
	ret = maps_address_get_city(hAddr, &szCity);
	if (ret == MAPS_ERROR_NONE && szCity && *szCity)
		rAddress.SetCity(String(szCity));
	g_free(szCity);

	char *szDistrict = NULL;
	ret = maps_address_get_district(hAddr, &szDistrict);
	if (ret == MAPS_ERROR_NONE && szDistrict && *szDistrict)
		rAddress.SetDistrict(String(szDistrict));
	g_free(szDistrict);

	char *szStreet = NULL;
	ret = maps_address_get_street(hAddr, &szStreet);
	if (ret == MAPS_ERROR_NONE && szStreet && *szStreet)
		rAddress.SetStreet(String(szStreet));
	g_free(szStreet);

	char *szBuildingNumber = NULL;
	ret = maps_address_get_building_number(hAddr, &szBuildingNumber);
	if (ret == MAPS_ERROR_NONE && szBuildingNumber && *szBuildingNumber)
		rAddress.SetHouseNumber(String(szBuildingNumber));
	g_free(szBuildingNumber);

	char *szPostalCode = NULL;
	ret = maps_address_get_postal_code(hAddr, &szPostalCode);
	if (ret == MAPS_ERROR_NONE && szPostalCode && *szPostalCode)
		rAddress.SetPostalCode(String(szPostalCode));
	g_free(szPostalCode);

	//not defined in maps-service
	//rAddress.SetLabel(String(sLabel));
	//rAddress.SetFloor(String(sFloor));
	//rAddress.SetSuite(String(sSuite));

	m_pQuery->SetAddress(rAddress);



	m_nRestReqId = m_pQuery->Execute(*this, NULL);

	return (m_nRestReqId > 0 ? HERE_ERROR_NONE : HERE_ERROR_INVALID_OPERATION);
}

void HereGeocode::OnGeoCoderReply(const GeoCoderReply& Reply)
{
	if (m_bCanceled || !m_pCbFunc) // ignore call back
	{
		delete this;
		return;
	}

	Result* pResult;
	size_t nResults = Reply.GetNumResults();
	GeoCoordinates hereCoord;
	maps_coordinates_h mapsCoord;

	if (nResults == 0) {
		((maps_service_geocode_cb)m_pCbFunc)(MAPS_ERROR_NOT_FOUND, m_nReqId,
			0, 0, NULL, m_pUserData);
		delete this;
		return;
	}

	for (size_t i = 0 ; i < nResults; i++)
	{
		pResult = (Result*)Reply.GetResult(i);

		if (pResult) {
			hereCoord = (pResult->GetLocation()).GetDisplayPosition();
		} else {
			hereCoord.SetLatitude(0.0);
			hereCoord.SetLongitude(0.0);
		}

		maps_error_e error = (maps_error_e)maps_coordinates_create(
				     hereCoord.GetLatitude(), hereCoord.GetLongitude(), &mapsCoord);

		if (m_bCanceled || !m_pCbFunc) {
			if (mapsCoord) maps_coordinates_destroy(mapsCoord);
			break;
		} else {
			if (((maps_service_geocode_cb)m_pCbFunc)(error, m_nReqId, i,
				nResults, mapsCoord, m_pUserData) == FALSE) {
				delete this;
				return;
			}
		}
	}

	delete this;
}

void HereGeocode::OnGeoCoderFailure(const GeoCoderReply& Reply)
{
	if (!m_bCanceled && m_pCbFunc)
		((maps_service_geocode_cb)m_pCbFunc)((maps_error_e)GetErrorCode(Reply), m_nReqId, 0, 0, NULL, m_pUserData);
	delete this;
}

HERE_PLUGIN_END_NAMESPACE

