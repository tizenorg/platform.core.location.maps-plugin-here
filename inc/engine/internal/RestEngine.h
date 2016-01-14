/*
 * Copyright (C) 2013 HERE Global B.V. All rights reserved.
 * This software, including documentation, is protected by copyright controlled by
 * HERE Global B.V. (“Software”). All rights are reserved. Copying, including reproducing,
 * storing, adapting or translating, any or all of this material requires the prior
 * written consent of HERE Global B.V. You may use this
 * Software in accordance with the terms and conditions defined in the
 * HERE Location Platform Services Terms and Conditions, available at
 * http://developer.here.com/terms-conditions-base
 *
 * As an additional permission to the above, you may distribute Software,
 * in object code format as part of an Application, according to, and subject to, terms and
 * conditions defined in the Tizen Software Development kit (“SDK”) License Agreement.
 * You may distribute such object code format Application under terms of your choice,
 * provided that the header and source files of the Software have not been modified.
 */

#ifndef RESTENGINE_H
#define RESTENGINE_H

#include "common/HereMaps_global.h"

#ifndef TIZEN_MIGRATION
#include <FBaseObject.h>
#include <FBaseRtEventDrivenThread.h>
#include <FNetHttpIHttpTransactionEventListener.h>
#endif

#include "common/QueryListener.h"
#include "common/RestItemHandle.h"

#ifdef TIZEN_MIGRATION
#include "base/BaseObject.h"
#include "base/BaseByteBuffer.h"
#include "base/EventDrivenThread.h"
#include "internal/RestCurl.h"

using namespace Tizen::Maps;
#else
using namespace Tizen::Base::Runtime;
#endif

HERE_MAPS_BEGIN_NAMESPACE

class RestItem;
class BaseReply;
class QueryListener;

class RestEngineArgument
: public Tizen::Maps::Object
{
public:
#ifdef TIZEN_SUPPORT_POST_METHOD
    RestEngineArgument(const String& sUrl, RestItem* pRestItem,
                       bool bPost = false, const String& sPostData = "")
    : m_sUrl(sUrl)
    , m_pRestItem(pRestItem)
    , m_bPost(bPost)
    , m_sPostData(sPostData)
#else
    RestEngineArgument(const String& sUrl, RestItem* pRestItem)
    : m_sUrl(sUrl)
    , m_pRestItem(pRestItem)
#endif
    {
    #ifdef TIZEN_MIGRATION
        m_aRequestId = RestItemHandle::INVALID_RESTITEM;
    #endif
    }

    RestEngineArgument(RestItemHandle::RequestId aRequestId)
    : m_aRequestId(aRequestId)
    {
    #ifdef TIZEN_MIGRATION
        m_pRestItem = NULL;
    #ifdef TIZEN_SUPPORT_POST_METHOD
        m_bPost = false;
    #endif
    #endif
    }

    RestEngineArgument(RestItem* pRestItem)
    : m_pRestItem(pRestItem)
    {
    #ifdef TIZEN_MIGRATION
        m_aRequestId = RestItemHandle::INVALID_RESTITEM;
    #ifdef TIZEN_SUPPORT_POST_METHOD
        m_bPost = false;
    #endif
    #endif
    }

    ~RestEngineArgument()
    {
    }

    String m_sUrl;
    RestItem* m_pRestItem;
    RestItemHandle::RequestId m_aRequestId;
#ifdef TIZEN_MIGRATION
    Tizen::Maps::MemoryStruct_s m_Chunk;
#endif
#ifdef TIZEN_SUPPORT_POST_METHOD
    bool m_bPost;
    String m_sPostData;
#endif
};

//this is an internal class and should not be used outside
class RestEngine
: public EventDrivenThread
#ifndef TIZEN_MIGRATION
, public Tizen::Net::Http::IHttpTransactionEventListener
#endif
{
public:
    static RestEngine& GetInstance();

#ifdef TIZEN_SUPPORT_POST_METHOD
    RestItemHandle::RequestId OpenRequest(const String& sUrl, QueryListener* pListener, BaseReplyPtr pReply,
                                          bool bPost = false, const String& sPostData = "");
#else
    RestItemHandle::RequestId OpenRequest(const String& sUrl, QueryListener* pListener, BaseReplyPtr pReply);
#endif
    size_t GetNumPendingRequests() const;
    void ShutdownEngine();
    void AbortRequest(RestItemHandle::RequestId aRequestId);
    void AbortListenerRequests(QueryListener* pListener);
    void AbortAllRequests();
    void UnregisterListener(QueryListener* pListener);

    int  CountListeners() const;

    static unsigned int GetMaxPendingRequests();

#ifdef TIZEN_MIGRATION
    void FireImpl(void* pArgs);
#ifdef TIZEN_MIGRATION_RESTENGINE_FIREIMPL_THREAD
    static void *FireImplThreadFunc(void *pArgs);
    static void FireImplThreadCleanUp(void *pArgs);
#endif
#endif

private:
    enum RequestType
    {
        RT_OpenRequest = 0,
        RT_CloseRestItem,
        RT_DeleteRestItem
    };

    bool CheckRequestIn(RestItem* pRestItem);
    RestItem* GetChechedInRequest(RestItemHandle::RequestId aRequestId) const;

    void CloseRestItemLater(RestItemHandle::RequestId aRequestId);
    void CloseRestItem(RestItemHandle::RequestId aRequestId, bool bDeleteLater = false);
    void DeleteRestItemLater(RestItem* pRestItem);

#ifdef TIZEN_MIGRATION
    void OnUserEventReceivedN(int requestType, void *pArgs);
#else
    void OnTransactionAborted(Tizen::Net::Http::HttpSession& httpSession,
                              Tizen::Net::Http::HttpTransaction& httpTransaction, result r);

    void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession& httpSession,
                                                Tizen::Net::Http::HttpTransaction& httpTransaction,
                                                Tizen::Base::String* pCert);

    void OnTransactionCompleted(Tizen::Net::Http::HttpSession& httpSession,
                                Tizen::Net::Http::HttpTransaction& httpTransaction);

    void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession& httpSession,
                                      Tizen::Net::Http::HttpTransaction& httpTransaction,
                                      int headerLen,
                                      bool bAuthRequired);

    void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession& httpSession,
                                  Tizen::Net::Http::HttpTransaction& httpTransaction,
                                  int availableBodyLen);

    void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession& httpSession,
                                   Tizen::Net::Http::HttpTransaction& httpTransaction,
                                   int recommendedChunkSize);

    void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList *pArgs);
#endif

    RestEngine();
    ~RestEngine();

    void Begin();

    void LockPendingRequests() const;
    void UnlockPendingRequests() const;

    void LockListenersRegistery() const;
    void UnlockListenersRegistery() const;

    bool OnStart();
    void OnStop();

    void RegisterListener(QueryListener* rListener);

#ifdef TIZEN_SUPPORT_POST_METHOD
    bool DoOpenRequest(const String& sUrl, RestItem* pRestItem,
                       bool bPost = false, const String& sPostData = "");
#else
    bool DoOpenRequest(const String& sUrl, RestItem* pRestItem);
#endif
    void DoCloseRestItemLater(RestItemHandle::RequestId aRequestId);
    void DoDeleteRestItemLater(RestItem* pRestItem);

    //classes allowed to access this internal instance
    friend class RestItem;
    friend class QueryListener;
#ifdef TIZEN_SUPPORT_TILE_FILE_CACHE
    friend class TileFetcherQuery;
#endif

    //members
    class RestEngineImpl;
    RestEngineImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
