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

#ifndef RESTITEM_H
#define RESTITEM_H

#include "common/HereMaps_global.h"
#include "common/BaseReply.h"
#include "common/RestItemHandle.h"

#ifdef TIZEN_MIGRATION
#include "internal/RestCurl.h" // MemoryStruct_s
#else
#include <FNet.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class ErrorBase;
class BaseReply;
class QueryListener;
#ifndef TIZEN_MIGRATION
class RestEngine;
#endif

//this class is for internal use only - do not rely on this outside
class RestItem
#ifdef TIZEN_MIGRATION
: public Tizen::Maps::Object
#endif
{
public:
    enum RestItemStatus
    {
        RIS_Created = 0,
        RIS_RequestIssued,
        RIS_Completed
    };

    RestItem(QueryListener* rListener, BaseReplyPtr pBaseReply);
    ~RestItem();

    bool Run(const String& rUri);
    void Stop();

    void OnError(ErrorBase& rError);
    void OnResponseData(const Tizen::Maps::ByteBuffer& rBuff);

#ifndef TIZEN_MIGRATION
    bool OwnsTransaction(Tizen::Net::Http::HttpTransaction* pTransaction) const;
#endif
    QueryListener* GetListener() const;

    RestItemHandle::RequestId GetRequestId() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(RestItem);
    friend class RestEngine;

    class RestItemImpl;
    RestItemImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
