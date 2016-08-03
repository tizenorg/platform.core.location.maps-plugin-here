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

#ifndef _LOCATION_HERE_MULTI_REV_GEOCODER_H_
#define _LOCATION_HERE_MULTI_REV_GEOCODER_H_

//plug-in header
#include "here_manager.h"

#include <maps_coordinates.h>

//map engine header
#include <geocoder/MultiReverseQuery.h>
#include <geocoder/MultiReverseReply.h>
#include <geocoder/MultiReverseQueryListener.h>
#include <geocoder/Result.h>
#include <common/GeoLocation.h>
#include <common/Address.h>

HERE_PLUGIN_BEGIN_NAMESPACE

using namespace HERE_MAPS_NAMESPACE_PREFIX;
using namespace TIZEN_MAPS_NAMESPACE_PREFIX;

class HereMultiRevGeocode
: public HereBase
, public MultiReverseQueryListener
{
public:
	/**
	 *This is the default constructor for reverse Geocoder.
	 */

	HereMultiRevGeocode(void *pCbFunc, void *pUserData, int nReqId);

	/**
	 *This is the default destructor for reverse Geocoder.
	 */

	~HereMultiRevGeocode();


	here_error_e PrepareQuery();
	here_error_e PreparePositionList(const maps_coordinates_list_h hGeocodeList);
	here_error_e StartMultiReverse(maps_item_hashtable_h hPref);

	virtual void OnMultiReverseReply(const MultiReverseReply& Reply);
	virtual void OnMultiReverseFailure(const MultiReverseReply& Reply);

private:
	MultiReverseQuery* m_pQuery;
	GeoCoordinates m_geoCoord;
};

HERE_PLUGIN_END_NAMESPACE

#endif //_LOCATION_HERE_MULTI_REV_GEOCODER_H_
