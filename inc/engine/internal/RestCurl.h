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

TIZEN_MAPS_BEGIN_NAMESPACE

using namespace Tizen::Maps;

typedef struct MemoryStruct {
	MemoryStruct() : memory(NULL), size(0), http_code(0), error(0) {};

	char *memory;
	size_t size;
	long http_code;
	int error;
} MemoryStruct_s;

class RestCurl
{
public:
	RestCurl();
	virtual ~RestCurl();

	static RestCurl& GetInstance();
	bool Commit(void *pArgs);
	void Abort(const Here::Maps::RestItemHandle::RequestId aRequestId);
	void Clear();
	void Join();
	void Shutdown();
private:
	int EasyCurl(String sUrl, MemoryStruct_s* pChunk
		#ifdef TIZEN_SUPPORT_POST_METHOD
		, bool bPost = false, String sPostData = ""
		#endif
	);
	static void *ThreadFunc(void *pArgs);
	static size_t WriteMemoryCb(void *pContents, size_t nSize, size_t nNmemb, void *pUser);
	static int XferInfoCb(void *pUser, curl_off_t dlTotal, curl_off_t dlNow,
	                                   curl_off_t ulTotal, curl_off_t ulNow);
	String UrlEncode(String sStr);
	bool CreateDetachedThread(void* (*pFunc)(void*), void *pArgs);

	#ifdef TIZEN_SUPPORT_CRYPTO_LOCK
	static void CryptoMutexLock(int mode, int type, char *file, int line);
	static void CryptoInitMutexLocks(void);
	static void CryptoKillMutexLocks(void);
	static unsigned long CryptoThreadId(void);
	#endif

	class RestCurlImpl;
	RestCurlImpl* m_pImpl;
};

TIZEN_MAPS_END_NAMESPACE

#endif /* REST_CURL_H */
