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

#ifndef _LOCATION_HERE_MANAGER_H_
#define _LOCATION_HERE_MANAGER_H_

//common header
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>

//platform header
#include <net_connection.h>
#include <app_manager.h>

//plug-in header
#include "here_base.h"
#include "here_api.h"
#include "here_types.h"
#include "here_utils.h"

//map engine header
#include <common/ApplicationContext.h>
#include <common/HereConfig.h>

HERE_PLUGIN_BEGIN_NAMESPACE

class HereManager;

typedef std::vector<HereBase*> HereSvcList;

class HereManager
{
public:
	/**
	 *This is the default constructor for Geocoder.
	 */

	HereManager();

	/**
	 *This is the default destructor for Geocoder.
	 */

	virtual ~HereManager();

	enum HereSvcType {
		HERE_SVC_GEOCODE,
		HERE_SVC_REV_GEOCODE,
		HERE_SVC_PLACE,
		HERE_SVC_ROUTE,
		HERE_SVC_MULTI_REV_GEOCODE
	};

	void* CreateInstance(HereSvcType nHereSvc, void* pCbFunc = NULL, void* pUserData = NULL, int *nReqId = NULL);
	here_error_e CloseInstance(int nReqId);
	here_error_e CancelInstance(int nReqId);
	here_error_e SetCredentials(const char* provider_key);
	here_error_e GetCredentials(char** provider_key);
	void TerminateAllServices(void);

	here_error_e SetProxyAddress();
	here_error_e SetPreference(maps_preference_h hPref);
	here_error_e GetPreference(maps_preference_h *hPref);
	maps_preference_h GetPreference();

	static bool Create();
	static HereManager* GetHandler();
	static void Close();
	static here_error_e CheckAgreement();

private:
	here_error_e SetCredentials();
	static bool AppInfoMetadataCb(const char *metadata_key, const char *metadata_value, void *user_data);
	static void NetworkStateChangedIndCb(connection_type_e type, void *user_data);
	static here_error_e ConvertNetworkErrorCode(const int nErrorCode);
	connection_h m_hConnection;
	static int m_nRefCnt;
	static HereManager *m_pHereManager;

protected:
	HereSvcList m_HereList;
	gint m_nNextReqId;
	maps_preference_h m_hPref;
	pthread_mutex_t m_mtxHereList;
};

HERE_PLUGIN_END_NAMESPACE

#endif //_LOCATION_HERE_MANAGER_H_
