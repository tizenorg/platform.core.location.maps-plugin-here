//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef REST_CURL_H
#define REST_CURL_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <glib.h>
#include <curl/curl.h>
#include <curl/easy.h>

#include "common/HereMaps_global.h"

#include "common/RestItemHandle.h"
#include "base/BaseByteBuffer.h"
#include "base/EventDrivenThread.h"

#define RESTCURL_CRYPTO_LOCK

TIZEN_MAPS_BEGIN_NAMESPACE

using namespace Tizen::Maps;

typedef struct MemoryStruct {
	char *memory;
	size_t size;
	long http_code;
} MemoryStruct_s;

class RestCurl
{
public:
	RestCurl();
	virtual ~RestCurl();
	bool Commit(void *pArgs);
	void Clear();
	void Shutdown();
	void Abort(const Here::Maps::RestItemHandle::RequestId aRequestId);
	int EasyCurl(String sUrl, MemoryStruct_s* pChunk);
	String UrlEncode(String sStr);
	static RestCurl& GetInstance();

private:
	static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
	static void *ThreadFunc(void *pArgs);

	class RestCurlImpl;
	RestCurlImpl* m_pImpl;
};

TIZEN_MAPS_END_NAMESPACE

#endif /* REST_CURL_H */
