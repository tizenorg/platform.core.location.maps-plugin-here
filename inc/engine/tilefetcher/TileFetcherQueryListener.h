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

#ifndef TILEFETCHERQUERYLISTENER_H
#define TILEFETCHERQUERYLISTENER_H

#include "common/HereMaps_global.h"
#include "common/QueryListener.h"

HERE_MAPS_BEGIN_NAMESPACE

class TileFetcherReply;

/**
 * This class encapsulates an object that is notified when a response to a query
 * has become available. The derived classes must implement the methods defined
 * on this class to provide handling of the replies from the server.
 * 
 * \ingroup tilefetcher
 */
class TileFetcherQueryListener : public QueryListener
{
public:

    /**
     * This is the default constructor.
     */
    TileFetcherQueryListener();

    /**
     * This method is the destructor.
     */
    ~TileFetcherQueryListener();

    /**
     * This method is a callback invoked when data have arrived in response to a
     * tile fetch request.
     *
     * @param rReply A Constant reference to an object containing the response data.
     */
    virtual void OnTileFetcherReply(const TileFetcherReply& rReply) = 0;

private:

    void OnReplySuccess(BaseReply& rReply);

};

HERE_MAPS_END_NAMESPACE

#endif
