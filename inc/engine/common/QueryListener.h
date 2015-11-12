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

#ifndef QUERYLISTENER_H
#define QUERYLISTENER_H

#include <tr1/memory>
#include "common/HereMaps_global.h"

#ifndef TIZEN_MIGRATION
#include <FBaseRtEvent.h>
#include <FBaseRtIEventListener.h>
#include <FBaseRtIEventArg.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class BaseReply;
class ErrorBase;

typedef std::tr1::shared_ptr<BaseReply> BaseReplyPtr;
/**
 * This class encapsulates an object that is notified when a response to a query
 * has become available. 
 * 
 * Derived classes must implement the virtual methods of this class.
 */
class EXPORT_API QueryListener
#ifndef TIZEN_MIGRATION
: public Tizen::Base::Runtime::Event
, public Tizen::Base::Runtime::IEventListener
#endif
{
public:
    /**
     * This is the default constructor for the class.
     */
    QueryListener();

    /**
     * This is a virtual destructor for the class.
     */
    virtual ~QueryListener();

    /**
     * This method triggers a call to the listener's method
     * <code>OnReplySuccess()</code>. 
     * 
     * @param pReply A pointer to the query reply.
     */
    void NotifyForSuccess(BaseReplyPtr pReply);

    /**
     * This method triggers a call to the listener's method
     * <code>OnReplyFailure()</code>. 
     * 
     * @param pReply A pointer to the query reply.
     */
    void NotifyForFailure(BaseReplyPtr pReply);

    /**
     * This method is a callback invoked when a query is successful. The
     * implementation of this method handles the reply to a successful query.
     * 
     * @param rReply A Reference to the query reply object.
     *
     */
    virtual void OnReplySuccess(BaseReply& rReply) = 0;

    /**
     * This method is a callback invoked when a query fails. The
     * implementation of this method handles the reply.
     *
     * @param rReply A Constant reference to the reply. Only the error and user
     *        data are valid.
     */
#ifdef TIZEN_MIGRATION
    virtual void OnFailure(const BaseReply& rReply) = 0;
#else
    virtual void OnFailure(const BaseReply& rReply);
#endif

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(QueryListener);
    class Arguments;
#ifndef TIZEN_MIGRATION
    void FireImpl(Tizen::Base::Runtime::IEventListener& rListener, const Tizen::Base::Runtime::IEventArg& rArgs);
#endif
};

HERE_MAPS_END_NAMESPACE

#endif
