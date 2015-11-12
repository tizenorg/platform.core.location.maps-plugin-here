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

#ifndef _LOCATION_HERE_REV_GEOCODER_H_
#define _LOCATION_HERE_REV_GEOCODER_H_

//plug-in header
#include "here_manager.h"

#include <maps_extra_types.h>
#include <maps_coordinates.h>

//map engine header
#include <geocoder/ReverseGeoCoderQuery.h>
#include <geocoder/GeoCoderQueryListener.h>
#include <geocoder/GeoCoderReply.h>
#include <geocoder/Result.h>
#include <common/GeoLocation.h>
#include <common/Address.h>

HERE_PLUGIN_BEGIN_NAMESPACE

using namespace HERE_MAPS_NAMESPACE_PREFIX;

class HereRevGeocode
: public HereBase
, public GeoCoderQueryListener
{
public:
	/**
	 *This is the default constructor for reverse Geocoder.
	 */

	HereRevGeocode(void *pCbFunc, void *pUserData, int nReqId);

	/**
	 *This is the default destructor for reverse Geocoder.
	 */

	~HereRevGeocode();


	here_error_e PrepareQuery();
	here_error_e PreparePreference(maps_preference_h hPref);
	here_error_e PreparePosition(double dLat, double dLng);

	here_error_e StartRevGeocode(maps_item_hashtable_h hPref);

	virtual void OnGeoCoderReply(const GeoCoderReply& Reply);
	virtual void OnGeoCoderFailure(const GeoCoderReply& Reply);

private:
	ReverseGeoCoderQuery* m_pQuery;
	GeoCoordinates m_geoCoord;
};

HERE_PLUGIN_END_NAMESPACE

#endif //_LOCATION_HERE_REV_GEOCODER_H_
