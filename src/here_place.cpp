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

#include "here_place.h"

HERE_PLUGIN_BEGIN_NAMESPACE

HerePlace::HerePlace(void *pCbFunc, void *pUserData, int nReqId)
{
	m_pDiscoveryQuery = NULL;
	m_pPlaceDetailsQuery = NULL;

	m_pCbFunc = pCbFunc;
	m_pUserData = pUserData;
	m_nReqId = nReqId;

	m_nReplyCnt = 0;
	m_nReplyIdx = 0;
	m_bReplyFlushed = false;
	m_szSortBy = NULL;
	m_bPlaceDetails = false;
	m_bPlaceDetailsInternal = false;
	m_bReplyWithList = false;
	m_eDistanceUnit = MAPS_DISTANCE_UNIT_M;
}

HerePlace::~HerePlace()
{
	if (m_pDiscoveryQuery)
	{
		delete m_pDiscoveryQuery;
		m_pDiscoveryQuery = NULL;
	}

	if (m_pPlaceDetailsQuery)
	{
		delete m_pPlaceDetailsQuery;
		m_pPlaceDetailsQuery = NULL;
	}

	while(!m_PlaceList.empty())
	{
		maps_place_destroy(m_PlaceList.front());
		m_PlaceList.pop_front();
	}
}

here_error_e HerePlace::PrepareDiscoveryQuery()
{
	if (m_pDiscoveryQuery)
		return HERE_ERROR_PERMISSION_DENIED;

	 m_pDiscoveryQuery = new (std::nothrow) DiscoveryQuery();

	if (!m_pDiscoveryQuery)
		return HERE_ERROR_OUT_OF_MEMORY;
	else
		return HERE_ERROR_NONE;
}

here_error_e HerePlace::PrepareDiscoveryPreference(maps_preference_h hPref)
{
	if (!m_pDiscoveryQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hPref)
		return HERE_ERROR_NONE;


	int ret;
	char *szLanguage = NULL;
	ret = maps_preference_get_language(hPref, &szLanguage);
	if (ret == MAPS_ERROR_NONE && szLanguage && *szLanguage)
		m_pDiscoveryQuery->SetLanguage(szLanguage);
	g_free(szLanguage);

	int nMaxResults;
	ret = maps_preference_get_max_results(hPref, &nMaxResults);
	if (ret == MAPS_ERROR_NONE)
		m_pDiscoveryQuery->SetMaxResults((size_t)nMaxResults);

	maps_distance_unit_e eUnit;
	ret = maps_preference_get_distance_unit(hPref, &eUnit);
	if (ret == MAPS_ERROR_NONE)
		m_eDistanceUnit = eUnit;

	char *szSortBy;
	ret = maps_preference_get(hPref, MAPS_PLACE_FILTER_SORT_BY, &szSortBy);
	if (ret == MAPS_ERROR_NONE)
		m_szSortBy = szSortBy;

	return HERE_ERROR_NONE;
}

here_error_e HerePlace::PrepareDiscoveryFilter(maps_place_filter_h hFilter)
{
	if (!m_pDiscoveryQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hFilter)
		return HERE_ERROR_INVALID_PARAMETER;

	int ret;
	maps_place_category_h mapsCate = NULL;
	if (maps_place_filter_get_category(hFilter, &mapsCate) == MAPS_ERROR_NONE)
	{
		CategoryList hereCateList;
		Category hereCate;
		char *szId = NULL, *szName = NULL, *szUrl = NULL;

		ret = maps_place_category_get_name(mapsCate, &szName);
		if (ret == MAPS_ERROR_NONE && szName && *szName)
			hereCate.SetTitle(szName);
		g_free(szName);

		ret = maps_place_category_get_url(mapsCate, &szUrl);
		if (ret == MAPS_ERROR_NONE && szUrl && *szUrl)
			hereCate.SetHref(szUrl);
		g_free(szUrl);

		ret = maps_place_category_get_id(mapsCate, &szId);
		if (ret == MAPS_ERROR_NONE && szId && *szId)
			hereCate.SetCategoryId(CategoryId(szId));
		else if (hereCate.GetTitle().size() > 0)
		{
			hereCate.SetCategoryId(CategoryId(hereCate.GetTitle()));
			hereCate.SetTitle("");
		}
		g_free(szId);

		hereCateList.push_back(hereCate);
		m_pDiscoveryQuery->SetCategoriesFilter(hereCateList);
		maps_place_category_destroy(mapsCate);
	}

	char *szName = NULL;
	ret = maps_place_filter_get_place_name(hFilter, &szName);
	if (ret == MAPS_ERROR_NONE && szName && *szName)
		m_pDiscoveryQuery->SetSearchText(szName);
	g_free(szName);

	char *szKeyword = NULL;
	ret = maps_place_filter_get_keyword(hFilter, &szKeyword);
	if (ret == MAPS_ERROR_NONE && szKeyword && *szKeyword)
	{
		String szSearchText = m_pDiscoveryQuery->GetSearchText();
		if (szSearchText.size() > 0) szSearchText += " ";
		szSearchText += szKeyword;
		m_pDiscoveryQuery->SetSearchText(szSearchText);
	}
	g_free(szKeyword);

	char *szAddress = NULL;
	ret = maps_place_filter_get_place_address(hFilter, &szAddress);
	if (ret == MAPS_ERROR_NONE && szAddress && *szAddress)
	{
		String szSearchText = szAddress;
		if (m_pDiscoveryQuery->GetSearchText().size() > 0)
		{
			szSearchText += " " + m_pDiscoveryQuery->GetSearchText();
		}
		m_pDiscoveryQuery->SetSearchText(szSearchText);
	}
	g_free(szAddress);

	return HERE_ERROR_NONE;
}

here_error_e HerePlace::StartDiscoveryPlace(maps_coordinates_h hCoord, int nDistance)
{
	if (!hCoord || nDistance < 0)
		return HERE_ERROR_INVALID_PARAMETER;

	maps_area_h area = NULL;
	maps_area_create_circle(hCoord, nDistance, &area);
	here_error_e error = StartDiscoveryPlace(area);
	maps_area_destroy(area);
	return error;
}

here_error_e HerePlace::StartDiscoveryPlace(maps_area_h hArea, const char *szAddr)
{
	if (!hArea)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!m_pDiscoveryQuery)
		return HERE_ERROR_OUT_OF_MEMORY;



	typedef enum {
		PLACE_CMD_TEXT,
		PLACE_CMD_CENTER,
		PLACE_CMD_AREA,
	} PlaceCmdType;

	PlaceCmdType cmdType;
	maps_area_s *pArea = (maps_area_s*)hArea;
	GeoCoordinates geoCoord;
	GeoBoundingArea *geoArea = NULL;
	GeoBoundingBox geoBox;
	GeoBoundingCircle geoCircle;

	/* Merge search text with other search text being in preference */
	String szSearchText = (szAddr ? szAddr : "");
	if (m_pDiscoveryQuery->GetSearchText().size() > 0)
	{
		if (szSearchText.size() > 0) szSearchText += " ";
		szSearchText += m_pDiscoveryQuery->GetSearchText();
	}
	m_pDiscoveryQuery->SetSearchText(szSearchText);


	/* Decide command type */
	if (!szSearchText.empty())
	{
		cmdType = PLACE_CMD_TEXT;
	}
	else if (pArea->type == MAPS_AREA_CIRCLE && pArea->circle.radius == 0)
	{
		cmdType = PLACE_CMD_CENTER;
	}
	else
	{
		cmdType = PLACE_CMD_AREA;
	}


	/* Get proximity with area */
	if (cmdType == PLACE_CMD_TEXT || cmdType == PLACE_CMD_CENTER)
	{
		if (pArea->type == MAPS_AREA_RECTANGLE)
		{
			double dLat1 = pArea->rect.top_left.latitude;
			double dLng1 = pArea->rect.top_left.longitude;
			double dLat2 = pArea->rect.bottom_right.latitude;
			double dLng2 = pArea->rect.bottom_right.longitude;
			double dLat = (dLat1 + dLat2) / 2;
			double dLng = (dLng1 + dLng2) / 2;

			geoCoord.SetLatitude(dLat);
			geoCoord.SetLongitude(dLng);
		}
		else if(pArea->type == MAPS_AREA_CIRCLE)
		{
			double dLat = pArea->circle.center.latitude;
			double dLng = pArea->circle.center.longitude;

			geoCoord.SetLatitude(dLat);
			geoCoord.SetLongitude(dLng);
		}
		else
			return HERE_ERROR_INVALID_PARAMETER;
	}
	else if (cmdType == PLACE_CMD_AREA)
	{
		if (pArea->type == MAPS_AREA_RECTANGLE)
		{
			HereUtils::Convert(hArea, geoBox);
			geoArea = &geoBox;
		}
		else if (pArea->type == MAPS_AREA_CIRCLE)
		{
			HereUtils::Convert(hArea, geoCircle);
			geoArea = &geoCircle;
		}
		else
			return HERE_ERROR_INVALID_PARAMETER;
	}


	/* Set properties */
	if (cmdType == PLACE_CMD_TEXT)
	{
		m_pDiscoveryQuery->SetType(DiscoveryQuery::QT_SEARCH);
		m_pDiscoveryQuery->SetProximity(geoCoord);
	}
	else if (cmdType == PLACE_CMD_CENTER)
	{
		m_pDiscoveryQuery->SetType(DiscoveryQuery::QT_EXPLORE);
		m_pDiscoveryQuery->SetProximity(geoCoord);
	}
	else
	{
		m_pDiscoveryQuery->SetType(DiscoveryQuery::QT_EXPLORE);
		if (geoArea)
			m_pDiscoveryQuery->SetArea(*geoArea);
	}

	/* Execute query */
	m_nRestReqId = m_pDiscoveryQuery->Execute(*this, NULL);

	return (m_nRestReqId > 0 ? HERE_ERROR_NONE : HERE_ERROR_INVALID_OPERATION);
}

here_error_e HerePlace::StartDiscoveryPlaceList(maps_area_h hArea)
{
	m_bReplyWithList = true;
	return StartDiscoveryPlace(hArea);
}

here_error_e HerePlace::PreparePlaceDetailsQuery()
{
	if (m_pPlaceDetailsQuery)
		return HERE_ERROR_PERMISSION_DENIED;

	m_pPlaceDetailsQuery = new (std::nothrow) PlaceDetailsQuery();

	if (!m_pPlaceDetailsQuery)
		return HERE_ERROR_OUT_OF_MEMORY;
	else
		return HERE_ERROR_NONE;
}

here_error_e HerePlace::PreparePlaceDetailsPreference(maps_preference_h hPref)
{
	if (!m_pPlaceDetailsQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!hPref)
		return HERE_ERROR_NONE;

	int ret;
	char *szLanguage = NULL;
	ret = maps_preference_get_language(hPref, &szLanguage);
	if (ret == MAPS_ERROR_NONE && szLanguage && *szLanguage)
		m_pPlaceDetailsQuery->SetLanguage(szLanguage);
	g_free(szLanguage);

	maps_distance_unit_e eUnit;
	ret = maps_preference_get_distance_unit(hPref, &eUnit);
	if (ret == MAPS_ERROR_NONE)
		m_eDistanceUnit = eUnit;

	return HERE_ERROR_NONE;
}

here_error_e HerePlace::StartPlaceDetails(const char *szUrl)
{
	if (!m_pPlaceDetailsQuery)
		return HERE_ERROR_OUT_OF_MEMORY;

	if (!szUrl || (szUrl && strlen(szUrl) <= 0))
		return HERE_ERROR_INVALID_PARAMETER;

	m_bPlaceDetails = true;

	m_nRestReqId = m_pPlaceDetailsQuery->Execute(*this, NULL, szUrl);

	return (m_nRestReqId > 0 ? HERE_ERROR_NONE : HERE_ERROR_INVALID_OPERATION);
}

here_error_e HerePlace::StartPlaceDetailsInternal(const char *szUrl)
{
	if (!szUrl || (szUrl && strlen(szUrl) <= 0))
		return HERE_ERROR_INVALID_PARAMETER;

	std::unique_ptr<PlaceDetailsQuery> pPlaceDetailsQuery (new (std::nothrow)PlaceDetailsQuery());

	m_bPlaceDetailsInternal = true;
	bool bExcuted = (int)(pPlaceDetailsQuery->Execute(*this, NULL, szUrl) > 0);

	return (bExcuted ? HERE_ERROR_NONE : HERE_ERROR_INVALID_OPERATION);
}

void HerePlace::OnDiscoverReply (const DiscoveryReply &Reply)
{
	maps_place_h mapsPlace;
	PlaceItemList herePlaceList = Reply.GetPlaceItems();
	PlaceItemList::iterator herePlaceIt;
	SearchItemList hereSearchList = Reply.GetSearchItems();
	SearchItemList::iterator hereSearchIt;
	LinkObject hereLinkObj;
	GeoCoordinates hereCoord;
	maps_coordinates_h mapsCoord;
	Category hereCate;
	maps_place_category_h mapsCate;
	maps_place_rating_h mapsRating;
	int error = MAPS_ERROR_UNKNOWN, sub_error;
	bool is_valid, isPending;

	if (m_bCanceled || !m_pCbFunc)
	{
		delete this;
		return;
	}

	m_nReplyIdx = 0;
	m_nReplyCnt = herePlaceList.size() + hereSearchList.size();

	for (herePlaceIt = herePlaceList.begin();
		herePlaceIt != herePlaceList.end();
		herePlaceIt++)
	{
		if ((error = maps_place_create(&mapsPlace)) == MAPS_ERROR_NONE)
		{
			isPending = false;

			/* title, uri, id */
			hereLinkObj = herePlaceIt->GetLinkObject();

			if (!hereLinkObj.GetTitle().empty())
				maps_place_set_name(mapsPlace, (char*)hereLinkObj.GetTitle().c_str());

			if (!hereLinkObj.GetHref().empty())
				maps_place_set_uri(mapsPlace, (char*)hereLinkObj.GetHref().c_str());

			if (!hereLinkObj.GetId().empty())
				maps_place_set_id(mapsPlace, (char*)hereLinkObj.GetId().c_str());

			/* icon */
			/* type */

			/* position */
			hereCoord = herePlaceIt->GetPosition();
			if (maps_coordinates_create(hereCoord.GetLatitude(), hereCoord.GetLongitude(),
				&mapsCoord) == MAPS_ERROR_NONE)
			{
				maps_place_set_location(mapsPlace, mapsCoord);
				maps_coordinates_destroy(mapsCoord);
			}

			/* rating (optional) */
			if (maps_place_rating_create(&mapsRating) == MAPS_ERROR_NONE)
			{
				maps_place_rating_set_average(mapsRating, herePlaceIt->GetAverageRating());
				maps_place_set_rating(mapsPlace, mapsRating);
				maps_place_rating_destroy(mapsRating);
			}

			/* category (optional) */
			hereCate = herePlaceIt->GetCategory();

			maps_item_list_h mapsCateList;
			if (maps_item_list_create(&mapsCateList) == MAPS_ERROR_NONE)
			{
				if (maps_place_category_create(&mapsCate) == MAPS_ERROR_NONE)
				{
					is_valid = false;

					if (!hereCate.GetCategoryId().ToString().empty())
					{
						sub_error = maps_place_category_set_id(mapsCate,
								(char*)hereCate.GetCategoryId().ToString().c_str());
						is_valid |= (sub_error == MAPS_ERROR_NONE);
					}

					if (!hereCate.GetTitle().empty())
					{
						sub_error = maps_place_category_set_name(mapsCate,
								(char*)hereCate.GetTitle().c_str());
						is_valid |= (sub_error == MAPS_ERROR_NONE);
					}

					if (!hereCate.GetHref().empty())
					{
						sub_error = maps_place_category_set_url(mapsCate,
								(char*)hereCate.GetHref().c_str());
						is_valid |= (sub_error == MAPS_ERROR_NONE);
					}

					if (is_valid)
					{
						maps_item_list_append(mapsCateList, mapsCate, maps_place_category_clone);
						maps_place_set_categories(mapsPlace, mapsCateList);
						maps_item_list_remove_all(mapsCateList, maps_place_category_destroy);
					}
					maps_place_category_destroy(mapsCate);
				}
				maps_item_list_destroy(mapsCateList);
			}

			/* distance */
			maps_place_set_distance(mapsPlace, HereUtils::ConvertDistance((int)herePlaceIt->GetDistance(), m_eDistanceUnit));

			/* sponser */
			/* herePlaceList.GetIsSponsored() */

			/* vicinity */

			/* If needed PlaceDetails information, postpone to send a reply */
			if(__sending_place_details_query_automatically && !m_bReplyWithList)
			{
				hereLinkObj = herePlaceIt->GetLinkObject();
				if (!hereLinkObj.GetHref().empty() && !hereLinkObj.GetId().empty())
				{
					if (StartPlaceDetailsInternal(hereLinkObj.GetHref().c_str()) == HERE_ERROR_NONE)
					{
						m_PlaceList.push_back(mapsPlace);
						isPending = true;
						MAPS_LOGD("Add maps_place_h to the pending list. id=%s", hereLinkObj.GetId().data());
					}
				}
			}

			if (!isPending) {
				m_nReplyIdx++;
				m_PlaceList.push_back(mapsPlace);
			}
		}
		else
		{
			m_nReplyCnt--;
		}
	}

	for (hereSearchIt = hereSearchList.begin();
		hereSearchIt != hereSearchList.end();
		hereSearchIt++)
	{
		error = maps_place_create(&mapsPlace);

		if(error == MAPS_ERROR_NONE)
		{
			is_valid = false;

			// title, uri, szId
			hereLinkObj = hereSearchIt->GetLinkObject();

			if (!hereLinkObj.GetTitle().empty())
			{
				sub_error = maps_place_set_name(mapsPlace,
						(char*)hereLinkObj.GetTitle().c_str());
				is_valid |= (sub_error == MAPS_ERROR_NONE);
			}

			if (!hereLinkObj.GetHref().empty())
			{
				sub_error = maps_place_set_uri(mapsPlace,
						(char*)hereLinkObj.GetHref().c_str());
				is_valid |= (sub_error == MAPS_ERROR_NONE);
			}

			if (!hereLinkObj.GetId().empty())
			{
				sub_error = maps_place_set_id(mapsPlace,
						(char*)hereLinkObj.GetId().c_str());
				is_valid |= (sub_error == MAPS_ERROR_NONE);
			}
			/* icon */
			/* type */

			if (!is_valid)
			{
				m_nReplyCnt--;
				error = MAPS_ERROR_NOT_FOUND;
				maps_place_destroy(mapsPlace);
				mapsPlace = NULL;
			}
			else
			{
				m_PlaceList.push_back(mapsPlace);
				m_nReplyIdx++;
			}
		}
		else
		{
			m_nReplyCnt--;
		}
	}


	if (!m_bReplyFlushed && (m_nReplyCnt == 0 || m_nReplyIdx == m_nReplyCnt))
	{
		if (m_nReplyCnt == 0)
			error = MAPS_ERROR_NOT_FOUND;

		__flushReplies(error);
		delete this;
	}
}

void HerePlace::OnDiscoverFailure(const DiscoveryReply& Reply)
{
	if (!m_bReplyFlushed)
	{
		m_nReplyIdx = 0;
		m_nReplyCnt = 0;
		__flushReplies((maps_error_e)GetErrorCode(Reply));
		delete this;
	}
}

void HerePlace::OnPlaceDetailsReply (const PlaceDetailsReply &Reply)
{
	if (m_nReplyCnt == 0)
	{
		if (m_bCanceled || !m_pCbFunc)
		{
			delete this;
			return;
		}
		m_nReplyCnt = 1;
	}

	PlaceDetails herePlace = Reply.GetPlaceDetails();
	maps_place_h mapsPlace = NULL;
	int error = MAPS_ERROR_NONE, sub_error;
	bool is_valid, isPending = false;
	char *placeId;
	int placeIdLen;

	/* Finding maps_place_h which is already pending since DiscoverReply */
	PlaceList::iterator it;
	for (it = m_PlaceList.begin(); it != m_PlaceList.end(); it++)
	{
		if (maps_place_get_id(*it, &placeId) == MAPS_ERROR_NONE)
		{
			placeIdLen = strlen(placeId);
			if(!herePlace.GetPlaceId().compare(0, placeIdLen, placeId))
			{
				mapsPlace = *it;
				isPending = true;
				MAPS_LOGD("Found maps_place_h in the pending list. id=%s", placeId);
				g_free(placeId);
				break;
			}
		}
		g_free(placeId);
	}

	/* If not found, create new handle */
	if (!mapsPlace)
		error = maps_place_create(&mapsPlace);

	if (error == MAPS_ERROR_NONE)
	{
		is_valid = false;

		/* name */
		if (!herePlace.GetName().empty())
		{
			sub_error = maps_place_set_name(mapsPlace, (char*)herePlace.GetName().c_str());
			is_valid |= (sub_error == MAPS_ERROR_NONE);
		}

		/* id */
		if (!herePlace.GetPlaceId().empty())
		{
			sub_error = maps_place_set_id(mapsPlace, (char*)herePlace.GetPlaceId().c_str());
			is_valid |= (sub_error == MAPS_ERROR_NONE);
		}

		/* view */
		if (!herePlace.GetView().empty())
		{
			sub_error = maps_place_set_uri(mapsPlace, (char*)herePlace.GetView().c_str());
			is_valid |= (sub_error == MAPS_ERROR_NONE);
		}

		if (is_valid)
		{
			/* icon */
			/* maps not supported // herePlace.GetIconPath(); */

			/* location */
			ProcessPlaceLocation(herePlace, mapsPlace);

			ProcessPlaceContact(herePlace, mapsPlace);

			ProcessPlaceCategory(herePlace, mapsPlace);

			/* tags */
			/* maps & here not supported */

			ProcessPlaceImage(herePlace, mapsPlace);

			ProcessPlaceDetails(herePlace, mapsPlace);

			ProcessPlaceReviews(herePlace, mapsPlace);

			ProcessPlaceRatings(herePlace, mapsPlace);

			ProcessPlaceRated(herePlace, mapsPlace);

			if (!isPending)
				m_PlaceList.push_back(mapsPlace);

			m_nReplyIdx++;
		}
		else
		{
			m_nReplyCnt--;
			error = MAPS_ERROR_NOT_FOUND;
			maps_place_destroy(mapsPlace);
			mapsPlace = NULL;
		}
	}
	else
	{
		m_nReplyCnt--;
	}

	if (!m_bReplyFlushed && (m_nReplyCnt == 0 || m_nReplyIdx == m_nReplyCnt))
	{
		if (m_nReplyCnt == 0)
			error = MAPS_ERROR_NOT_FOUND;

		__flushReplies(error);
		delete this;
	}
}

void HerePlace::OnPlaceDetailsFailure(const PlaceDetailsReply& Reply)
{
	if (!m_bPlaceDetailsInternal)
	{
		if (!m_bReplyFlushed)
		{
			m_nReplyIdx = 0;
			m_nReplyCnt = 0;
			__flushReplies(GetErrorCode(Reply));
			delete this;
		}
	}
	else
	{
		m_nReplyIdx++;
		MAPS_LOGD("Internal error during updating detailed information for the place. (%d/%d)", m_nReplyIdx, m_nReplyCnt);
		if (!m_bReplyFlushed && (m_nReplyIdx == m_nReplyCnt))
		{
			__flushReplies(MAPS_ERROR_NONE);
			delete this;
		}
	}
}

void HerePlace::ProcessPlaceLocation(PlaceDetails herePlace, maps_place_h mapsPlace)
{
	GeoLocation hereLocation = herePlace.GetLocation();

	/* position */
	GeoCoordinates hereCoord = hereLocation.GetDisplayPosition();
	maps_coordinates_h mapsCoord;

	if (maps_coordinates_create(hereCoord.GetLatitude(),
		hereCoord.GetLongitude(), &mapsCoord) == MAPS_ERROR_NONE)
	{
		maps_place_set_location(mapsPlace, mapsCoord);
		maps_coordinates_destroy(mapsCoord);
	}

	/* address */
	Address hereAddr = hereLocation.GetAddress();
	maps_address_h mapsAddr;
	int error;
	bool is_valid;

	if (maps_address_create(&mapsAddr) == MAPS_ERROR_NONE)
	{
		is_valid = false;

		if (!hereAddr.GetHouseNumber().empty())
		{
			error = maps_address_set_building_number(mapsAddr,
					hereAddr.GetHouseNumber().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereAddr.GetStreet().empty())
		{
			error = maps_address_set_street(mapsAddr, hereAddr.GetStreet().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereAddr.GetDistrict().empty())
		{
			error = maps_address_set_district(mapsAddr, hereAddr.GetDistrict().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereAddr.GetCity().empty())
		{
			error = maps_address_set_city(mapsAddr, hereAddr.GetCity().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereAddr.GetState().empty())
		{
			error = maps_address_set_state(mapsAddr, hereAddr.GetState().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereAddr.GetCountry().empty())
		{
			error = maps_address_set_country(mapsAddr, hereAddr.GetCountry().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereAddr.GetCountryCode().empty())
		{
			error = maps_address_set_country_code(mapsAddr, hereAddr.GetCountryCode().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereAddr.GetCounty().empty())
		{
			error = maps_address_set_county(mapsAddr, hereAddr.GetCounty().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereAddr.GetPostalCode().empty())
		{
			error = maps_address_set_postal_code(mapsAddr, hereAddr.GetPostalCode().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereAddr.GetLabel().empty())
		{
			error = maps_address_set_freetext(mapsAddr, hereAddr.GetLabel().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (is_valid)
		{
			maps_place_set_address(mapsPlace, mapsAddr);
		}
		maps_address_destroy(mapsAddr);
	}
}


void HerePlace::ProcessPlaceContact(PlaceDetails herePlace, maps_place_h mapsPlace)
{
	/* contact */
	ContactDetailsList hereContList = herePlace.GetContactDetails();
	ContactDetailsList::iterator hereCont;
	maps_item_list_h mapsContList;
	maps_place_contact_h mapsCont;
	int error;
	bool is_valid;

	if (hereContList.empty()) return;

	if (maps_item_list_create(&mapsContList) != MAPS_ERROR_NONE) return;

	for (hereCont = hereContList.begin(); hereCont != hereContList.end(); hereCont++)
	{
		if (maps_place_contact_create(&mapsCont) != MAPS_ERROR_NONE) continue;

		is_valid = false;

		if (!hereCont->GetLabel().empty())
		{
			error = maps_place_contact_set_label(mapsCont,
				(char*)hereCont->GetLabel().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereCont->GetValue().empty())
		{
			error = maps_place_contact_set_value(mapsCont,
				(char*)hereCont->GetValue().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereCont->GetContactType().empty())
		{
			error = maps_place_contact_set_type(mapsCont,
				(char*)hereCont->GetContactType().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (is_valid)
		{
			maps_item_list_append(mapsContList, mapsCont,
				maps_place_contact_clone);
		}
		maps_place_contact_destroy(mapsCont);
	}

	if (maps_item_list_items(mapsContList))
	{
		maps_place_set_contacts(mapsPlace, mapsContList);
		maps_item_list_remove_all(mapsContList, maps_place_contact_destroy);
	}
	maps_item_list_destroy(mapsContList);
}

void HerePlace::ProcessPlaceCategory(PlaceDetails herePlace, maps_place_h mapsPlace)
{
	CategoryList hereCateList = herePlace.GetCategories();
	CategoryList::iterator hereCate;
	maps_item_list_h mapsCateList;
	maps_place_category_h mapsCate;
	int error;
	bool is_valid = false;

	if (hereCateList.empty()) return;

	if (maps_item_list_create(&mapsCateList) != MAPS_ERROR_NONE) return;

	// maps-service supports only one category
	hereCate = hereCateList.begin();
	if (maps_place_category_create(&mapsCate) == MAPS_ERROR_NONE)
	{
		if (!hereCate->GetCategoryId().ToString().empty())
		{
			error = maps_place_category_set_id(mapsCate,
				hereCate->GetCategoryId().ToString().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereCate->GetTitle().empty())
		{
			error = maps_place_category_set_name(mapsCate,
				hereCate->GetTitle().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereCate->GetHref().empty())
		{
			error = maps_place_category_set_url(mapsCate,
				hereCate->GetHref().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (is_valid)
		{
			maps_item_list_append(mapsCateList, mapsCate, maps_place_category_clone);
		}
		maps_place_category_destroy(mapsCate);
	}

	if (maps_item_list_items(mapsCateList))
	{
		maps_place_set_categories(mapsPlace, mapsCateList);
		maps_item_list_remove_all(mapsCateList, maps_place_category_destroy);
	}
	maps_item_list_destroy(mapsCateList);
}

void HerePlace::ProcessPlaceImage(PlaceDetails herePlace, maps_place_h mapsPlace)
{
	ImageContentList hereImageList = herePlace.GetImageContent();
	ImageContentList::iterator hereImage;
	maps_item_list_h mapsImageList;
	maps_place_image_h mapsImage;
	maps_place_link_object_h mapsImageUser;
	LinkObject hereImageUser;
	int error;
	bool is_valid, is_valid2;

	if (hereImageList.empty()) return;

	if (maps_item_list_create(&mapsImageList) != MAPS_ERROR_NONE) return;

	for (hereImage = hereImageList.begin(); hereImage != hereImageList.end(); hereImage++)
	{
		if (maps_place_image_create(&mapsImage) != MAPS_ERROR_NONE) continue;

		is_valid = false;

		/* here not supported
		// maps_place_image_set_height(maps_place_image_h mapsPlace, const int height); */

		/* here not supported
		// maps_place_image_set_media(maps_place_image_h mapsPlace, maps_place_media_h media); */

		if (!hereImage->GetSource().empty())
		{
			error = maps_place_image_set_url(mapsImage, (char*)hereImage->GetSource().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereImage->GetImageId().empty())
		{
			error = maps_place_image_set_id(mapsImage, (char*)hereImage->GetImageId().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		hereImageUser = hereImage->GetUser();
		if (maps_place_link_object_create(&mapsImageUser) == MAPS_ERROR_NONE)
		{
			is_valid2 = false;

			if (!hereImageUser.GetId().empty())
			{
				error = maps_place_link_object_set_id(mapsImageUser,
						(char*)hereImageUser.GetId().c_str());
				is_valid2 |= (error == MAPS_ERROR_NONE);
			}

			if (!hereImageUser.GetTitle().empty())
			{
				error = maps_place_link_object_set_name(mapsImageUser,
						(char*)hereImageUser.GetTitle().c_str());
				is_valid2 |= (error == MAPS_ERROR_NONE);
			}

			if (!hereImageUser.GetHref().empty())
			{
				error = maps_place_link_object_set_string(mapsImageUser,
						(char*)hereImageUser.GetHref().c_str());
				is_valid2 |= (error == MAPS_ERROR_NONE);
			}

			if (!hereImageUser.GetType().empty())
			{
				error = maps_place_link_object_set_type(mapsImageUser,
						(char*)hereImageUser.GetType().c_str());
				is_valid2 |= (error == MAPS_ERROR_NONE);
			}

			if (is_valid2)
			{
				maps_place_image_set_user_link(mapsImage, mapsImageUser);
				is_valid |= is_valid2;
			}
			maps_place_link_object_destroy(mapsImageUser);
		}

		if (is_valid)
		{
			maps_item_list_append(mapsImageList, mapsImage, maps_place_image_clone);
		}
		maps_place_image_destroy(mapsImage);
	}

	if (maps_item_list_items(mapsImageList))
	{
		maps_place_set_images(mapsPlace, mapsImageList);
		maps_item_list_remove_all(mapsImageList, maps_place_image_destroy);
	}
	maps_item_list_destroy(mapsImageList);
}

void HerePlace::ProcessPlaceDetails(PlaceDetails herePlace, maps_place_h mapsPlace)
{
	EditorialContentList hereEditList = herePlace.GetEditorialContent();
	EditorialContentList::iterator hereEdit;
	maps_item_list_h mapsEditList;
	maps_place_editorial_h mapsEdit;
	int error;
	bool is_valid;

	if (hereEditList.empty()) return;

	if (maps_item_list_create(&mapsEditList) != MAPS_ERROR_NONE) return;

	for (hereEdit = hereEditList.begin(); hereEdit != hereEditList.end(); hereEdit++)
	{
		if (maps_place_editorial_create(&mapsEdit) != MAPS_ERROR_NONE) continue;

		is_valid = false;

		if (!hereEdit->GetDescription().empty())
		{
			error = maps_place_editorial_set_description(mapsEdit,
				(char*)hereEdit->GetDescription().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereEdit->GetLanguage().empty())
		{
			error = maps_place_editorial_set_language(mapsEdit,
				(char*)hereEdit->GetLanguage().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		/* maps_place_editorial_set_media(mapsEdit, maps_place_media_h media); */

		if (is_valid)
		{
			maps_item_list_append(mapsEditList, mapsEdit, maps_place_editorial_clone);
		}
		maps_place_editorial_destroy(mapsEdit);
	}

	if (maps_item_list_items(mapsEditList))
	{
		maps_place_set_editorials(mapsPlace, mapsEditList);
		maps_item_list_remove_all(mapsEditList, maps_place_editorial_destroy);
	}
	maps_item_list_destroy(mapsEditList);
}

void HerePlace::ProcessPlaceReviews(PlaceDetails herePlace, maps_place_h mapsPlace)
{
	ReviewContentList hereReviewList = herePlace.GetReviewContent();
	ReviewContentList::iterator hereReview;
	maps_place_review_h mapsReview;
	maps_item_list_h mapsReviewList;
	LinkObject hereReviewUser;
	maps_place_link_object_h mapsReviewUser;
	int error;
	bool is_valid, is_valid2;

	if (hereReviewList.empty()) return;

	if (maps_item_list_create(&mapsReviewList) != MAPS_ERROR_NONE) return;

	for (hereReview = hereReviewList.begin(); hereReview != hereReviewList.end(); hereReview++)
	{
		if (maps_place_review_create(&mapsReview) != MAPS_ERROR_NONE) continue;

		is_valid = false;

		if (!hereReview->GetDateTime().empty())
		{
			error = maps_place_review_set_date(mapsReview,
				(char*)hereReview->GetDateTime().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereReview->GetDescription().empty())
		{
			error = maps_place_review_set_description(mapsReview,
				(char*)hereReview->GetDescription().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		if (!hereReview->GetLanguage().empty())
		{
			error = maps_place_review_set_language(mapsReview,
				(char*)hereReview->GetLanguage().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		/* maps_place_review_set_media(mapsReview, maps_place_media_h media) */

		maps_place_review_set_rating(mapsReview, hereReview->GetRating());

		if (!hereReview->GetTitle().empty())
		{
			error = maps_place_review_set_title(mapsReview,
				(char*)hereReview->GetTitle().c_str());
			is_valid |= (error == MAPS_ERROR_NONE);
		}

		hereReviewUser = hereReview->GetUser();
		if (maps_place_link_object_create(&mapsReviewUser) == MAPS_ERROR_NONE)
		{
			is_valid2 = false;

			if (!hereReviewUser.GetId().empty())
			{
				error = maps_place_link_object_set_id(mapsReviewUser,
					(char*)hereReviewUser.GetId().c_str());
				is_valid2 |= (error == MAPS_ERROR_NONE);
			}

			if (!hereReviewUser.GetTitle().empty())
			{
				error = maps_place_link_object_set_name(mapsReviewUser,
					(char*)hereReviewUser.GetTitle().c_str());
				is_valid2 |= (error == MAPS_ERROR_NONE);
			}

			if (!hereReviewUser.GetHref().empty())
			{
				error = maps_place_link_object_set_string(mapsReviewUser,
					(char*)hereReviewUser.GetHref().c_str());
				is_valid2 |= (error == MAPS_ERROR_NONE);
			}

			if (!hereReviewUser.GetType().empty())
			{
				error = maps_place_link_object_set_type(mapsReviewUser,
					(char*)hereReviewUser.GetType().c_str());
				is_valid2 |= (error == MAPS_ERROR_NONE);
			}

			if (is_valid2)
			{
				maps_place_review_set_user_link(mapsReview, mapsReviewUser);
				is_valid |= is_valid2;
			}
			maps_place_link_object_destroy(mapsReviewUser);
		}

		if (is_valid)
		{
			maps_item_list_append(mapsReviewList, mapsReview, maps_place_review_clone);
		}
		maps_place_review_destroy(mapsReview);
	}

	if (maps_item_list_items(mapsReviewList))
	{
		maps_place_set_reviews(mapsPlace, mapsReviewList);
		maps_item_list_remove_all(mapsReviewList, maps_place_review_destroy);
	}
	maps_item_list_destroy(mapsReviewList);
}

void HerePlace::ProcessPlaceRatings(PlaceDetails herePlace, maps_place_h mapsPlace)
{
	Ratings hereRating = herePlace.GetRatings();
	maps_place_rating_h mapsRating;

	if (maps_place_rating_create(&mapsRating) != MAPS_ERROR_NONE) return;

	maps_place_rating_set_average(mapsRating, hereRating.GetAverage());
	maps_place_rating_set_count(mapsRating, hereRating.GetCount());
	maps_place_set_rating(mapsPlace, mapsRating);
	maps_place_rating_destroy(mapsRating);
}

void HerePlace::ProcessPlaceRated(PlaceDetails herePlace, maps_place_h mapsPlace)
{
	RelatedItem hereRelated = herePlace.GetRelatedItem();
	maps_place_link_object_h mapsRelated;
	int error;
	bool is_valid = false;

	if (maps_place_link_object_create(&mapsRelated) != MAPS_ERROR_NONE) return;

	//need to check if GetId() exist
	//maps_place_link_object_set_id(mapsRelated, hereRelated.GetId());

	if (!hereRelated.GetTitle().empty())
	{
		error = maps_place_link_object_set_name(mapsRelated,
			(char*)hereRelated.GetTitle().c_str());
		is_valid |= (error == MAPS_ERROR_NONE);
	}

	if (!hereRelated.GetHref().empty())
	{
		error = maps_place_link_object_set_string(mapsRelated,
			(char*)hereRelated.GetHref().c_str());
		is_valid |= (error == MAPS_ERROR_NONE);
	}

	if (!hereRelated.GetType().empty())
	{
		error = maps_place_link_object_set_type(mapsRelated,
			(char*)hereRelated.GetType().c_str());
		is_valid |= (error == MAPS_ERROR_NONE);
	}

	if (is_valid)
	{
		maps_place_set_related_link(mapsPlace, mapsRelated);
	}
	maps_place_link_object_destroy(mapsRelated);
}

void HerePlace::__flushReplies(int error)
{
	maps_place_h mapsPlace;
	maps_item_list_h place_list;

	m_nReplyIdx = 0;
	__sortList(m_PlaceList);

	if (m_bPlaceDetails)
	{
		if (error != MAPS_ERROR_NONE)
		{
			((maps_service_get_place_details_cb)m_pCbFunc)((maps_error_e)error, m_nReqId, NULL, m_pUserData);
			return;
		}

			mapsPlace = m_PlaceList.front();
			m_PlaceList.pop_front();

		((maps_service_get_place_details_cb)m_pCbFunc)((maps_error_e)error, m_nReqId, mapsPlace, m_pUserData);
	}
	else if (m_bReplyWithList)
	{
		int error = maps_item_list_create(&place_list);
		if (error != MAPS_ERROR_NONE)
		{
			((maps_service_search_place_list_cb)m_pCbFunc)((maps_error_e)error, m_nReqId, NULL, m_pUserData);
			return;
		}

		while (m_nReplyIdx < m_nReplyCnt && !m_bCanceled && !m_PlaceList.empty())
		{
			mapsPlace = m_PlaceList.front();
			m_PlaceList.pop_front();

			maps_item_list_append(place_list, mapsPlace, maps_place_clone);
		}

		((maps_service_search_place_list_cb)m_pCbFunc)((maps_error_e)error, m_nReqId, place_list, m_pUserData);
	}
	else
	{
		while (m_nReplyIdx < m_nReplyCnt && !m_bCanceled && !m_PlaceList.empty())
		{
			mapsPlace = m_PlaceList.front();
			m_PlaceList.pop_front();

			/* callback function */
			if (((maps_service_search_place_cb)m_pCbFunc)((maps_error_e)error, m_nReqId,
				m_nReplyIdx++, m_nReplyCnt, mapsPlace, m_pUserData) == FALSE)
			{
				break;
			}
		}
	}
}

bool HerePlace::__compareWithTitle(const maps_place_h &item1, const maps_place_h &item2)
{
	bool result = false;
	char *str1 = NULL, *str2 = NULL;

	if (maps_place_get_name(item1, &str1) == MAPS_ERROR_NONE &&
		maps_place_get_name(item2, &str2) == MAPS_ERROR_NONE)
	{
		result = (strcmp(str1, str2) < 0);
	}
	g_free(str1);
	g_free(str2);
	return result;
}

bool HerePlace::__compareWithId(const maps_place_h &item1, const maps_place_h &item2)
{
	bool result = false;
	char *str1 = NULL, *str2 = NULL;

	if (maps_place_get_id(item1, &str1) == MAPS_ERROR_NONE &&
		maps_place_get_id(item2, &str2) == MAPS_ERROR_NONE)
	{
		result = (strcmp(str1, str2) < 0);
	}
	g_free(str1);
	g_free(str2);
	return result;
}

bool HerePlace::__compareWithDistance(const maps_place_h &item1, const maps_place_h &item2)
{
	bool result = false;
	int num1 = 0, num2 = 0;

	if (maps_place_get_distance(item1, &num1) == MAPS_ERROR_NONE &&
		maps_place_get_distance(item2, &num2) == MAPS_ERROR_NONE)
	{
		result = (num1 < num2);
	}
	return result;
}

bool HerePlace::__compareWithRating(const maps_place_h &item1, const maps_place_h &item2)
{
	bool result = false;
	maps_place_rating_h rat1 = NULL, rat2 = NULL;
	double num1 = 0, num2 = 0;	

	if (maps_place_get_rating(item1, &rat1) == MAPS_ERROR_NONE &&
		maps_place_get_rating(item2, &rat2) == MAPS_ERROR_NONE)
	{
		if (maps_place_rating_get_average(rat1, &num1) == MAPS_ERROR_NONE &&
			maps_place_rating_get_average(rat2, &num2) == MAPS_ERROR_NONE)
		{
			result = (num1 > num2);
		}
	}
	maps_place_rating_destroy(rat1);
	maps_place_rating_destroy(rat2);
	return result;
}

bool HerePlace::__compareWithCategoryCb(int index, int total,
					 maps_place_category_h category,
					 void *user_data)
{
	user_data = category;
	return false;
}

bool HerePlace::__compareWithCategory(const maps_place_h &item1, const maps_place_h &item2)
{
	bool result = false;
	maps_place_category_h cat1 = NULL, cat2 = NULL;
	char *str1 = NULL, *str2 = NULL;

	maps_place_foreach_category(item1, __compareWithCategoryCb, &cat1);
	maps_place_foreach_category(item2, __compareWithCategoryCb, &cat2);

	if (maps_place_category_get_id(item1, &str1) == MAPS_ERROR_NONE &&
		maps_place_category_get_id(item2, &str2) == MAPS_ERROR_NONE)
	{
		result = (strcmp(str1, str2) < 0);
	}
	maps_place_category_destroy(item1);
	maps_place_category_destroy(item2);
	g_free(str1);
	g_free(str2);
	return result;
}

void HerePlace::__sortList(PlaceList &list)
{
	if (!m_szSortBy) return;

	if (!strcmp(m_szSortBy, "name") || !strcmp(m_szSortBy, "title"))
	{
		std::sort(list.begin(), list.end(), __compareWithTitle);
	}
	else if (!strcmp(m_szSortBy, "id"))
	{
		std::sort(list.begin(), list.end(), __compareWithId);
	}
	else if (!strcmp(m_szSortBy, "distance"))
	{
		std::sort(list.begin(), list.end(), __compareWithDistance);
	}
	else if (!strcmp(m_szSortBy, "rate") || !strcmp(m_szSortBy, "rating"))
	{
		std::sort(list.begin(), list.end(), __compareWithRating);
	}
	else if (!strcmp(m_szSortBy, "category"))
	{
		std::sort(list.begin(), list.end(), __compareWithCategory);
	}
}

HERE_PLUGIN_END_NAMESPACE
