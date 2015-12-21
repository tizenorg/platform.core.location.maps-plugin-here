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

#include "here_multirevgeocode.h"

HERE_PLUGIN_BEGIN_NAMESPACE

HereMultiRevGeocode::HereMultiRevGeocode(void* pCbFunc, void* pUserData, int nReqId)
: m_geoCoord(0,0,0)
{
	m_pQuery = NULL;
	m_pCbFunc = pCbFunc;
	m_pUserData = pUserData;
	m_nReqId = nReqId;
}

HereMultiRevGeocode::~HereMultiRevGeocode()
{
	if (m_pQuery)
	{
		delete m_pQuery;
		m_pQuery = NULL;
	}
}

here_error_e HereMultiRevGeocode::PrepareQuery()
{
	if (m_pQuery)
		return HERE_ERROR_PERMISSION_DENIED;

	m_pQuery = new MultiReverseQuery();

	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;
	else
		return HERE_ERROR_NONE;
}

static bool geocoder_coordinates_cb(int index, maps_coordinates_h coordinates, void *user_data)
{
	double dLatitude = 0.0;
	double dLongitude = 0.0;
	GeoCoordinates hereCoord;
	maps_coordinates_get_latitude(coordinates, &dLatitude);
	maps_coordinates_get_longitude(coordinates, &dLongitude);
	hereCoord = GeoCoordinates(dLatitude, dLongitude);

	if (!HereUtils::IsValid(hereCoord))
		return HERE_ERROR_INVALID_PARAMETER;

	GeoCoordinateList *pList =(GeoCoordinateList *) user_data;
	pList->push_back(hereCoord);

	return true;
}

here_error_e HereMultiRevGeocode::PreparePositionList(const maps_coordinates_list_h hGeocodeList)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hGeocodeList)
		return HERE_ERROR_INVALID_PARAMETER;

	GeoCoordinateList hereCoordList;
	maps_coordinates_list_foreach(hGeocodeList, geocoder_coordinates_cb, &hereCoordList);

	m_pQuery->SetMode(MultiReverseQuery::RM_RetrieveAddresses);
	m_pQuery->SetGeocodeList(hereCoordList);
	m_pQuery->SetMaxResults(1);
	m_pQuery->SetGenParameter(8);

	return HERE_ERROR_NONE;
}

here_error_e HereMultiRevGeocode::StartMultiReverse(maps_item_hashtable_h hPref)
{
	if (!m_pQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	m_nRestReqId = m_pQuery->Execute(*this, NULL);

	return (m_nRestReqId > 0 ? HERE_ERROR_NONE : HERE_ERROR_CANCELED);
}

void HereMultiRevGeocode::OnMultiReverseReply(const MultiReverseReply& Reply)
{
	if (m_bCanceled || !m_pCbFunc) // ignore call back
	{
		delete this;
		return;
	}

	int nResults = Reply.GetNumResults();
	Result* pResult;

	maps_address_list_h address_list;
	maps_address_list_create(&address_list);
	maps_address_h pAddr = NULL;
	String *additionalDataValue = NULL;

	for (size_t i = 0; i < (size_t)nResults; i++)
	{
		maps_error_e error = (maps_error_e)maps_address_create(&pAddr);

		if(error == MAPS_ERROR_NONE)
		{
			pResult = (Result*)Reply.GetResult(i);

			if (pResult)
			{
				Address tmpAddr = (pResult->GetLocation()).GetAddress();

				if(!tmpAddr.GetHouseNumber().empty())
					maps_address_set_building_number(pAddr, tmpAddr.GetHouseNumber().c_str());

				if(!tmpAddr.GetStreet().empty())
					maps_address_set_street(pAddr, tmpAddr.GetStreet().c_str());

				if(!tmpAddr.GetDistrict().empty())
					maps_address_set_district(pAddr, tmpAddr.GetDistrict().c_str());

				if(!tmpAddr.GetCity().empty())
					maps_address_set_city(pAddr, tmpAddr.GetCity().c_str());

				additionalDataValue = (String*)tmpAddr.GetAdditionalDataValue("CountyName");
				if (additionalDataValue && !additionalDataValue->empty())
					maps_address_set_county(pAddr, additionalDataValue->c_str());
				else if (!tmpAddr.GetCounty().empty())
					maps_address_set_county(pAddr, tmpAddr.GetCounty().c_str());

				additionalDataValue = (String*)tmpAddr.GetAdditionalDataValue("StateName");
				if (additionalDataValue && !additionalDataValue->empty())
					maps_address_set_state(pAddr, additionalDataValue->c_str());
				else if (!tmpAddr.GetState().empty())
					maps_address_set_state(pAddr, tmpAddr.GetState().c_str());

				additionalDataValue = (String*)tmpAddr.GetAdditionalDataValue("CountryName");
				if (additionalDataValue && !additionalDataValue->empty())
					maps_address_set_country(pAddr, additionalDataValue->c_str());
				else if (!tmpAddr.GetCountry().empty())
					maps_address_set_country(pAddr, tmpAddr.GetCountry().c_str());

				if(!tmpAddr.GetCountry().empty())
					maps_address_set_country_code(pAddr, tmpAddr.GetCountry().c_str());

				if(!tmpAddr.GetPostalCode().empty())
					maps_address_set_postal_code(pAddr, tmpAddr.GetPostalCode().c_str());

				if(!tmpAddr.GetLabel().empty())
					maps_address_set_freetext(pAddr, tmpAddr.GetLabel().c_str());
			}
		}
		maps_address_list_append(address_list, pAddr);
	}

	if (m_bCanceled || !m_pCbFunc)
	{
		maps_address_list_destroy(address_list);
	}
	else if (nResults <= 0)
	{
		((maps_service_multi_reverse_geocode_cb)m_pCbFunc)(MAPS_ERROR_NOT_FOUND, m_nReqId, 0, NULL, m_pUserData);
	}
	else
	{
		((maps_service_multi_reverse_geocode_cb)m_pCbFunc)(MAPS_ERROR_NONE, m_nReqId, nResults, address_list, m_pUserData);
	}

	delete this;
}

void HereMultiRevGeocode::OnMultiReverseFailure(const MultiReverseReply& Reply)
{
	if (!m_bCanceled && m_pCbFunc)
		((maps_service_multi_reverse_geocode_cb)m_pCbFunc)((maps_error_e)GetErrorCode(Reply), m_nReqId, 0, NULL, m_pUserData);
	delete this;
}

HERE_PLUGIN_END_NAMESPACE

