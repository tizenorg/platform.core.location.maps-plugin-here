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

#include <unistd.h>
#include <libxml/xpath.h>

#include "here_manager.h"
#include "here_base.h"
#include "here_geocode.h"
#include "here_revgeocode.h"
#include "here_multirevgeocode.h"
#include "here_place.h"
#include "here_route.h"
#include "here_utils.h"
#include <common/HereConfig.h>

using namespace HERE_PLUGIN_NAMESPACE_PREFIX;
using namespace TIZEN_MAPS_NAMESPACE_PREFIX;

HERE_PLUGIN_BEGIN_NAMESPACE

HereManager *HereManager::m_pHereManager = NULL;
int HereManager::m_nRefCnt = 0;
pthread_mutex_t g_mtxRef;

HereManager::HereManager()
: m_nNextReqId(1),
  m_hPref(NULL)
{
	xmlInitParser();
	m_hConnection = NULL;
	pthread_mutex_init(&m_mtxHereList, NULL);
	pthread_mutex_init(&g_mtxRef, NULL);
}

HereManager::~HereManager()
{
	if (m_hConnection)
	{
		connection_unset_type_changed_cb(m_hConnection);
		connection_destroy(m_hConnection);
		m_hConnection = NULL;
	}

	pthread_mutex_destroy(&m_mtxHereList);
	pthread_mutex_destroy(&g_mtxRef);
	xmlCleanupParser();
}

bool HereManager::Create()
{
	bool result = false;

	if (!m_pHereManager)
	{
		m_pHereManager = new HereManager();
	}

	pthread_mutex_lock(&g_mtxRef);
	if (m_pHereManager)
	{
		m_nRefCnt++;
		result = true;
		MAPS_LOGD("Created a HereManager instance (%d).", m_nRefCnt);
	}
	pthread_mutex_unlock(&g_mtxRef);

	m_pHereManager->SetCredentials();
	return result;
}

void HereManager::Close()
{
	pthread_mutex_lock(&g_mtxRef);
	bool terminate = (--m_nRefCnt == 0 && m_pHereManager);
	pthread_mutex_unlock(&g_mtxRef);

	if (terminate)
	{
		m_pHereManager->TerminateAllServices();
		HereConfig::Shutdown();

		delete m_pHereManager;
		m_pHereManager = NULL;
	}
	MAPS_LOGD("Closed a HereManager instance (%d).", m_nRefCnt);
}

HereManager* HereManager::GetHandler()
{
	return m_pHereManager;
}

void* HereManager::CreateInstance(HereSvcType nHereSvc, void* pCbFunc,
	void* pUserData, int *nReqId)
{
	HereBase *pHere = NULL;

	*nReqId = m_nNextReqId++;

	switch(nHereSvc)
	{
	case HERE_SVC_GEOCODE:
		pHere = (HereBase*)new HereGeocode(pCbFunc, pUserData, *nReqId);
		break;

	case HERE_SVC_REV_GEOCODE:
		pHere = (HereBase*)new HereRevGeocode(pCbFunc, pUserData, *nReqId);
		break;

	case HERE_SVC_PLACE:
		pHere = (HereBase*)new HerePlace(pCbFunc, pUserData, *nReqId);
		break;

	case HERE_SVC_ROUTE:
		pHere = (HereBase*)new HereRoute(pCbFunc, pUserData, *nReqId);
		break;

	case HERE_SVC_MULTI_REV_GEOCODE:
		pHere = (HereBase*)new HereMultiRevGeocode(pCbFunc, pUserData, *nReqId);
		break;

	default:
		return NULL;
	}

	pthread_mutex_lock(&m_mtxHereList);
	m_HereList.push_back(pHere);
	pthread_mutex_unlock(&m_mtxHereList);

	return pHere;
}

here_error_e HereManager::CloseInstance(int nReqId)
{
	HereSvcList::iterator it;

	pthread_mutex_lock(&m_mtxHereList);
	for (it = m_HereList.begin(); it != m_HereList.end(); it++)
	{
		if ((*it)->GetReqId() == nReqId)
		{
			m_HereList.erase(it);
			break;
		}
	}
	pthread_mutex_unlock(&m_mtxHereList);
	
	return HERE_ERROR_NONE;
}

here_error_e HereManager::CancelInstance(int nReqId)
{
	HereSvcList::iterator it;

	pthread_mutex_lock(&m_mtxHereList);
	for (it = m_HereList.begin(); it != m_HereList.end(); it++)
	{
		if ((*it)->GetReqId() == nReqId)
		{
			m_HereList.erase(it);
			RestItemHandle::Cancel((*it)->GetRestReqId());
			(*it)->TerminateService();
			pthread_mutex_unlock(&m_mtxHereList);
			return HERE_ERROR_NONE;
		}
	}
	pthread_mutex_unlock(&m_mtxHereList);

	return HERE_ERROR_NOT_FOUND;
}

bool HereManager::AppInfoMetadataCb(const char *metadata_key, const char *metadata_value, void *user_data)
{
	if (!metadata_key || !metadata_value)
		return false;

	if (!strncmp(metadata_key, "http://tizen.org/metadata/here_key", 35) && strlen(metadata_value) > 0 )
	{
		if (m_pHereManager->SetCredentials(metadata_value) == HERE_ERROR_NONE)
		{
			MAPS_LOGD("Succeeded getting credential from metadata");
		}

		return false;
	}

	return true;
}

here_error_e HereManager::SetCredentials(void)
{
	int nRet = 0;
	app_info_h hAppInfo;
	pid_t nProcessId = -1;
	char *strAppId = NULL;

	nProcessId = getpid();
	nRet = app_manager_get_app_id(nProcessId, &strAppId);
	if (nRet != APP_MANAGER_ERROR_NONE)
	{
		MAPS_LOGI("Get app_id [%ld]. nRet[%d]", nProcessId, nRet);
		return HERE_ERROR_NONE;
	}

	nRet = app_info_create(strAppId, &hAppInfo);
	if (nRet != APP_MANAGER_ERROR_NONE)
	{
		MAPS_LOGI("Get appinfo of [%s]. nRet[%d]", strAppId, nRet);
		if (strAppId) free(strAppId);
		return HERE_ERROR_NONE;
	}

	if (strAppId) free(strAppId);

	nRet = app_info_foreach_metadata(hAppInfo, AppInfoMetadataCb, NULL);
	if (nRet != APP_MANAGER_ERROR_NONE)
	{
		MAPS_LOGI("Get metadata. nRet[%d]", nRet);
	}

	nRet = app_info_destroy(hAppInfo);
	if (nRet != APP_MANAGER_ERROR_NONE)
	{
		MAPS_LOGI("Destroy app_info. nRet[%d]", nRet);
	}

	return HERE_ERROR_NONE;
}

here_error_e HereManager::SetCredentials(const char *szKey)
{
	if (!szKey)
		return HERE_ERROR_INVALID_PARAMETER;

	String strKey(szKey);
	String strAppId, strAppCode;
	size_t nCodeStart;

	nCodeStart = strKey.find("/");

	if(nCodeStart == 0 || nCodeStart >= (strKey.length()-1))
	{
		MAPS_LOGE("[error] Key type fault : Key type should be as like XXXXX/YYYYY");
		return HERE_ERROR_INVALID_PARAMETER;
	}

	strAppId = strKey.substr(0, nCodeStart);
	strAppCode = strKey.substr(nCodeStart+1, std::string::npos);

	if(!ApplicationContext::GetInstance().Initialize(strAppCode, strAppId))
		return HERE_ERROR_INVALID_OPERATION;

	//MAPS_LOGD("[success] credential setted to 'XXXXX/XXXXX'");

	return HERE_ERROR_NONE;
}

here_error_e HereManager::GetCredentials(char **szKey)
{
	if (!szKey)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!ApplicationContext::GetInstance().IsInitialized())
		return HERE_ERROR_NOT_FOUND;

	String strCredentials = ApplicationContext::GetInstance().GetAppId() + "/" +
				ApplicationContext::GetInstance().GetAppCode();

	*szKey = g_strndup(strCredentials.c_str(), strCredentials.length());

	if (*szKey == NULL)
		return HERE_ERROR_INVALID_OPERATION;

	//MAPS_LOGD("current credential : %s", *szKey);

	return HERE_ERROR_NONE;
}

here_error_e HereManager::SetPreference(maps_preference_h hPref)
{
	int error = HERE_ERROR_NONE;

	if (!hPref)
		return HERE_ERROR_INVALID_PARAMETER;

	if (m_hPref)
	{
		if (maps_preference_destroy(m_hPref) != MAPS_ERROR_NONE)
			return HERE_ERROR_INVALID_OPERATION;
	}

	do {
		error = maps_preference_clone(hPref, &m_hPref);
		if (error != MAPS_ERROR_NONE) break;

		char *szLanguage = NULL;
		error = maps_preference_get_language(hPref, &szLanguage);
		if (error == MAPS_ERROR_NONE && szLanguage && strlen(szLanguage) > 0)
			ApplicationContext::GetInstance().SetPreferredLanguage(String(szLanguage));
	} while(0);

	return (here_error_e)ConvertToHereError(error);
}

here_error_e HereManager::GetPreference(maps_preference_h *hPref)
{
	int ret = HERE_ERROR_NONE;

	if (!hPref)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!m_hPref)
		return HERE_ERROR_NOT_FOUND;

	ret = maps_preference_clone(m_hPref, hPref);

	return (here_error_e)ConvertToHereError(ret);
}

maps_preference_h HereManager::GetPreference()
{
	return m_hPref;
}

void HereManager::TerminateAllServices(void)
{
	HereSvcList::iterator it;

	while (1)
	{
		pthread_mutex_lock(&m_mtxHereList);
		if (m_HereList.empty())
		{
			pthread_mutex_unlock(&m_mtxHereList);
			break;
		}
		it = m_HereList.begin();
		pthread_mutex_unlock(&m_mtxHereList);

		try {
			if (*it) (*it)->TerminateService();
			m_HereList.erase(it);
		}
		catch (std::exception &e) {
			MAPS_LOGD("Exception caught: %s", e.what());
		}
	};

	if (m_hPref)
	{
		maps_preference_destroy(m_hPref);
		m_hPref = NULL;
	}
}

here_error_e HereManager::ConvertNetworkErrorCode(const int nErrorCode)
{
	here_error_e err = HERE_ERROR_NONE;

	switch (nErrorCode)
	{
	case CONNECTION_ERROR_NONE:
		//MAPS_LOGD("No error");
		err = HERE_ERROR_NONE;
		break;
	case CONNECTION_ERROR_INVALID_PARAMETER:
		MAPS_LOGD("Invalid parameter");
		err = HERE_ERROR_INVALID_PARAMETER;
		break;
	case CONNECTION_ERROR_OUT_OF_MEMORY:
		MAPS_LOGD("Out of memory error");
		err = HERE_ERROR_OUT_OF_MEMORY;
		break;
	case CONNECTION_ERROR_INVALID_OPERATION:
		MAPS_LOGD("Invalid Operation");
		err = HERE_ERROR_INVALID_OPERATION;
		break;
	case CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED:
		MAPS_LOGD("Address family not supported");
		err = HERE_ERROR_NOT_SUPPORTED;
		break;
	case CONNECTION_ERROR_PERMISSION_DENIED:
		MAPS_LOGD("Permission denied");
		err = HERE_ERROR_PERMISSION_DENIED;
		break;
	case CONNECTION_ERROR_OPERATION_FAILED:
		MAPS_LOGD("Operation failed");
		err = HERE_ERROR_INVALID_OPERATION;
		break;
	case CONNECTION_ERROR_ITERATOR_END:
		MAPS_LOGD("End of iteration");
		break;
	case CONNECTION_ERROR_NO_CONNECTION:
		MAPS_LOGD("There is no connection");
		err = HERE_ERROR_NETWORK_UNREACHABLE;
		break;
	case CONNECTION_ERROR_NOW_IN_PROGRESS:
		MAPS_LOGD("Now in progress");
		err = HERE_ERROR_RESOURCE_BUSY;
		break;
	case CONNECTION_ERROR_ALREADY_EXISTS:
		MAPS_LOGD("Already exists");
		break;
	case CONNECTION_ERROR_OPERATION_ABORTED:
		MAPS_LOGD("Operation is aborted");
		err = HERE_ERROR_CANCELED;
		break;
	case CONNECTION_ERROR_DHCP_FAILED:
		MAPS_LOGD("DHCP failed");
		break;
	case CONNECTION_ERROR_INVALID_KEY:
		MAPS_LOGD("Invalid key");
		err = HERE_ERROR_KEY_NOT_AVAILABLE;
		break;
	case CONNECTION_ERROR_NO_REPLY:
		MAPS_LOGD("No Reply");
		err = HERE_ERROR_RESOURCE_BUSY;
		break;
	case CONNECTION_ERROR_NOT_SUPPORTED:
		MAPS_LOGD("Not Supported");
		err = HERE_ERROR_NOT_SUPPORTED;
		break;
	default:
		MAPS_LOGD("Unknown");
		break;
	}
	//MAPS_LOGD("nErrorCode = 0x%08X", nErrorCode);

	return err;
}

here_error_e HereManager::SetProxyAddress()
{
	int errorCode = CONNECTION_ERROR_NONE;

	char *proxy_address = NULL;

	if (!m_hConnection)
	{
		errorCode = connection_create(&m_hConnection);
		if (errorCode == CONNECTION_ERROR_NONE)
		{
			errorCode = connection_set_type_changed_cb(m_hConnection, NetworkStateChangedIndCb, this);

		}
	}
	if (errorCode != CONNECTION_ERROR_NONE)
		return ConvertNetworkErrorCode(errorCode);

	errorCode = connection_get_proxy(m_hConnection, CONNECTION_ADDRESS_FAMILY_IPV4, &proxy_address);
	if (errorCode == CONNECTION_ERROR_NONE)
	{
		MAPS_LOGD("Proxy = %s", (proxy_address ? proxy_address : "(null)"));
		Tizen::Maps::HereConfig::SetProxyAddress(proxy_address);
	}
	g_free(proxy_address);

	return ConvertNetworkErrorCode(errorCode);
}

void HereManager::NetworkStateChangedIndCb(connection_type_e type, void *user_data)
{
	MAPS_LOGD("Network state is changed. type=%d", type);

	if (!user_data) return;

	HereManager *pManager = (HereManager*)user_data;

	if ((type != CONNECTION_TYPE_DISCONNECTED) && (type != CONNECTION_TYPE_BT))
		pManager->SetProxyAddress();
}

HERE_PLUGIN_END_NAMESPACE

