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

#ifndef _LOCATION_HERE_BASE_H_
#define _LOCATION_HERE_BASE_H_

//plug-in header
#include "here_utils.h"
#include <common/BaseReply.h>

HERE_PLUGIN_BEGIN_NAMESPACE

class HereBase
{
public:
	/**
	 *This is the default constructor for Geocoder.
	 */

	HereBase();

	/**
	 *This is the default destructor for Geocoder.
	 */

	virtual ~HereBase();

	void TerminateService(void);

	gint GetReqId(void);
	gint GetRestReqId(void);
	gint GetErrorCode(const BaseReply& Reply);

protected:
	gint m_nReqId;
	gint m_nRestReqId;
	void* m_pCbFunc;
	void* m_pUserData;
	gboolean m_bCanceled;
};

HERE_PLUGIN_END_NAMESPACE

#endif //_LOCATION_HERE_BASE_H_

