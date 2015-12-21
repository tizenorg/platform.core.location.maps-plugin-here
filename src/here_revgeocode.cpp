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

#include "here_revgeocode.h"

HERE_PLUGIN_BEGIN_NAMESPACE

HereRevGeocode::HereRevGeocode(void* pCbFunc, void* pUserData, int nReqId)
: m_geoCoord(0,0,0)
{
	m_pQuery = NULL;
	m_pCbFunc = pCbFunc;
	m_pUserData = pUserData;
	m_nReqId = nReqId;
}

HereRevGeocode::~HereRevGeocode()
{
	if (m_pQuery)
	{
		delete m_pQuery;
		m_pQuery = NULL;
	}
}

here_error_e HereRevGeocode::PrepareQuery()
{
	if (m_pQuery)
		return HERE_ERROR_PERMISSION_DENIED;

	m_pQuery = new (std::nothrow) ReverseGeoCoderQuery();

	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;
	else
		return HERE_ERROR_NONE;
}

here_error_e HereRevGeocode::PreparePreference(maps_preference_h hPref)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hPref)
		return HERE_ERROR_INVALID_PARAMETER;

	int ret;
	char *szLanguage;
	ret = maps_preference_get_language(hPref, &szLanguage);
	if (ret == MAPS_ERROR_NONE && szLanguage && *szLanguage)
		m_pQuery->AppendPreferredLanguage(szLanguage);
	g_free(szLanguage);

	int nMaxResults;
	ret = maps_preference_get_max_results(hPref, &nMaxResults);
	if (ret == MAPS_ERROR_NONE)
		m_pQuery->SetMaxResults((size_t)nMaxResults);

	return HERE_ERROR_NONE;
}

here_error_e HereRevGeocode::PreparePosition(double dLat, double dLng)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	GeoCoordinates geoCoord(dLat, dLng);
	if (!HereUtils::IsValid(geoCoord))
		return HERE_ERROR_INVALID_PARAMETER;

	m_pQuery->SetProximity(geoCoord, 0);
	m_pQuery->SetMode(ReverseGeoCoderQuery::RM_RetrieveAddresses);

	return HERE_ERROR_NONE;
}

here_error_e HereRevGeocode::StartRevGeocode(maps_item_hashtable_h hPref)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	m_nRestReqId = m_pQuery->Execute(*this, NULL);

	return (m_nRestReqId > 0 ? HERE_ERROR_NONE : HERE_ERROR_INVALID_OPERATION);
}

void HereRevGeocode::OnGeoCoderReply(const GeoCoderReply& Reply)
{
	if (m_bCanceled) // ignore call back if it was cancelled.
	{
		delete this;
		return;
	}


	int nResults = Reply.GetNumResults();
	Result* pResult;
	float fDistance, fShortestDistance = 0;
	int nShortestIdx = -1;

	for (size_t i = 0; i < (size_t)nResults; i++)
	{
		pResult = (Result*)Reply.GetResult(i);

		if(pResult)
		{
			fDistance = pResult->GetDistance();

			if (nShortestIdx < 0 || fDistance < fShortestDistance)
			{
				fShortestDistance = fDistance;
				nShortestIdx = i;
			}
		}
	}


	if (nShortestIdx < 0)
	{
		((maps_service_reverse_geocode_cb)m_pCbFunc)(MAPS_ERROR_NOT_FOUND,
			m_nReqId, 0, 0, NULL, m_pUserData);
		delete this;
		return;
	}

	maps_address_h hAddr = NULL;
	maps_error_e error = (maps_error_e)maps_address_create(&hAddr);
	String *additionalDataValue = NULL;

	if(error == MAPS_ERROR_NONE)
	{
		pResult = (Result*)Reply.GetResult(nShortestIdx);

		if (pResult)
		{
			Address tmpAddr = (pResult->GetLocation()).GetAddress();

			if (!tmpAddr.GetHouseNumber().empty())
				maps_address_set_building_number(hAddr, tmpAddr.GetHouseNumber().c_str());

			if (!tmpAddr.GetStreet().empty())
				maps_address_set_street(hAddr, tmpAddr.GetStreet().c_str());

			if (!tmpAddr.GetDistrict().empty())
				maps_address_set_district(hAddr, tmpAddr.GetDistrict().c_str());

			if (!tmpAddr.GetCity().empty())
				maps_address_set_city(hAddr, tmpAddr.GetCity().c_str());

			additionalDataValue = (String*)tmpAddr.GetAdditionalDataValue("CountyName");
			if (additionalDataValue && !additionalDataValue->empty())
				maps_address_set_county(hAddr, additionalDataValue->c_str());
			else if (!tmpAddr.GetCounty().empty())
				maps_address_set_county(hAddr, tmpAddr.GetCounty().c_str());

			additionalDataValue = (String*)tmpAddr.GetAdditionalDataValue("StateName");
			if (additionalDataValue && !additionalDataValue->empty())
				maps_address_set_state(hAddr, additionalDataValue->c_str());
			else if (!tmpAddr.GetState().empty())
				maps_address_set_state(hAddr, tmpAddr.GetState().c_str());

			additionalDataValue = (String*)tmpAddr.GetAdditionalDataValue("CountryName");
			if (additionalDataValue && !additionalDataValue->empty())
				maps_address_set_country(hAddr, additionalDataValue->c_str());
			else if (!tmpAddr.GetCountry().empty())
				maps_address_set_country(hAddr, tmpAddr.GetCountry().c_str());

			if (!tmpAddr.GetCountry().empty())
				maps_address_set_country_code(hAddr, tmpAddr.GetCountry().c_str());

			if (!tmpAddr.GetPostalCode().empty())
				maps_address_set_postal_code(hAddr, tmpAddr.GetPostalCode().c_str());

			if (!tmpAddr.GetLabel().empty())
				maps_address_set_freetext(hAddr, tmpAddr.GetLabel().c_str());
		}
	}

	if (m_bCanceled)
	{
		maps_address_destroy(hAddr);
	}
	else
	{
		((maps_service_reverse_geocode_cb)m_pCbFunc)(error, m_nReqId, 0, 1, hAddr, m_pUserData);
	}

	delete this;
}

void HereRevGeocode::OnGeoCoderFailure(const GeoCoderReply& Reply)
{
	if (!m_bCanceled)
		((maps_service_reverse_geocode_cb)m_pCbFunc)((maps_error_e)GetErrorCode(Reply), m_nReqId, 0, 0, NULL, m_pUserData);
	delete this;
}

HERE_PLUGIN_END_NAMESPACE

