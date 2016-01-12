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

#ifndef _LOCATION_HERE_PLACE_H_
#define _LOCATION_HERE_PLACE_H_

#include <deque>

//plug-in header
#include "here_manager.h"

//maps-service header
#include <maps_place_plugin.h>
#include <maps_place_rating_plugin.h>
#include <maps_place_contact_plugin.h>
#include <maps_place_image_plugin.h>
#include <maps_place_link_object_plugin.h>
#include <maps_place_editorial_plugin.h>
#include <maps_place_review_plugin.h>

//map engine header
#include <finder/DiscoveryQuery.h>
#include <finder/PlaceDetailsQuery.h>
#include <finder/FinderQueryListener.h>
#include <finder/DiscoveryReply.h>
#include <finder/PlaceDetailsReply.h>
#include <finder/PlaceDetails.h>
#include <finder/CategoryId.h>
#include <finder/LinkObject.h>
#include <finder/Ratings.h>
#include <finder/RelatedItem.h>
#include <common/GeoLocation.h>
#include <common/Address.h>


HERE_PLUGIN_BEGIN_NAMESPACE

using namespace HERE_MAPS_NAMESPACE_PREFIX;

class HerePlace
: public HereBase
, public FinderQueryListener
{
public:
	typedef std::deque<maps_place_h> PlaceList;

	/**
	 *This is the default constructor for Place.
	 */

	HerePlace(void *pCbFunc, void *pUserData, int nReqId);

	/**
	 *This is the default destructor for Place.
	 */

	~HerePlace();

	here_error_e PrepareDiscoveryQuery();
	here_error_e PrepareDiscoveryPreference(maps_preference_h hPref);
	here_error_e PrepareDiscoveryFilter(maps_place_filter_h hFilter);

	here_error_e StartDiscoveryPlace(maps_coordinates_h hCoord, int nDistance);
	here_error_e StartDiscoveryPlace(maps_area_h hArea, const char *szAddr = "");

	here_error_e PreparePlaceDetailsQuery();
	here_error_e PreparePlaceDetailsPreference(maps_preference_h hPref);

	here_error_e StartPlaceDetails(const char* szUrl);
	here_error_e StartPlaceDetailsInternal(const char* szUrl);

	virtual void OnDiscoverReply(const DiscoveryReply &Reply);
	virtual void OnDiscoverFailure(const DiscoveryReply& Reply);

	virtual void OnPlaceDetailsReply(const PlaceDetailsReply &Reply);
	virtual void OnPlaceDetailsFailure(const PlaceDetailsReply& Reply);

private:
	void ProcessPlaceLocation(PlaceDetails herePlace, maps_place_h mapsPlace);
	void ProcessPlaceContact(PlaceDetails herePlace, maps_place_h mapsPlace);
	void ProcessPlaceCategory(PlaceDetails herePlace, maps_place_h mapsPlace);
	void ProcessPlaceImage(PlaceDetails herePlace, maps_place_h mapsPlace);
	void ProcessPlaceDetails(PlaceDetails herePlace, maps_place_h mapsPlace);
	void ProcessPlaceReviews(PlaceDetails herePlace, maps_place_h mapsPlace);
	void ProcessPlaceRatings(PlaceDetails herePlace, maps_place_h mapsPlace);
	void ProcessPlaceRated(PlaceDetails herePlace, maps_place_h mapsPlace);

	void __sortList(PlaceList &list);
	void __flushReplies(int error);
	static bool __compareWithTitle(const maps_place_h &item1, const maps_place_h &item2);
	static bool __compareWithId(const maps_place_h &item1, const maps_place_h &item2);
	static bool __compareWithType(const maps_place_h &item1, const maps_place_h &item2);
	static bool __compareWithDistance(const maps_place_h &item1, const maps_place_h &item2);
	static bool __compareWithRating(const maps_place_h &item1, const maps_place_h &item2);
	static bool __compareWithCategory(const maps_place_h &item1, const maps_place_h &item2);
	static bool __compareWithCategoryCb(int index, int total, maps_place_category_h category,
					 void *user_data);

	DiscoveryQuery* m_pDiscoveryQuery;
	PlaceDetailsQuery* m_pPlaceDetailsQuery;
	int m_nReplyCnt;
	int m_nReplyIdx;
	bool m_bReplyFlushed;
	char *m_szSortBy;
	bool m_bPlaceDetailsInternal;
	maps_distance_unit_e m_eDistanceUnit;

	PlaceList m_PlaceList;

	static const bool __sending_place_details_query_automatically = TRUE;
};

HERE_PLUGIN_END_NAMESPACE

#endif //_LOCATION_HERE_PLACE_H_
