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

#ifndef FINDERQUERYLISTENER_H
#define FINDERQUERYLISTENER_H

#include "common/HereMaps_global.h"

#include "common/QueryListener.h"

HERE_MAPS_BEGIN_NAMESPACE

class DiscoveryReply;
class PlaceDetailsReply;

/**
 * This class encapsulates an object that is notified when a response to a query
 * has become available. The derived classes must implement the methods defined
 * on this class to handle the replies from the server.
 */
class EXPORT_API FinderQueryListener : public QueryListener
{
public:

    /**
     * This is the default constructor.
     */
    FinderQueryListener();

    /**
     * This method is the destructor.
     */
    ~FinderQueryListener();

    /**
     * This method is a callback invoked when data have arrived in response to a
     * places search request.
     *
     * @param rReply A constant reference to an object containing the response data.
     */
    virtual void OnDiscoverReply(const DiscoveryReply& rReply) = 0;

    #ifdef TIZEN_MIGRATION
    /**
     * This method is a callback invoked when geocoding request is failed.
     *
     * @param rReply A Constant reference to an object containing the response data.
     */
    virtual void OnDiscoverFailure(const DiscoveryReply& rReply) = 0;
    #endif

    /**
     * This method is a callback invoked when data have arrived in response to a
     * places details request.
     *
     * @param rReply A constant reference to an object containing the response data.
     */
    virtual void OnPlaceDetailsReply(const PlaceDetailsReply& rReply) = 0;

    #ifdef TIZEN_MIGRATION
    /**
     * This method is a callback invoked when geocoding request is failed.
     *
     * @param rReply A Constant reference to an object containing the response data.
     */
    virtual void OnPlaceDetailsFailure(const PlaceDetailsReply& rReply) = 0;
    #endif

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(FinderQueryListener);

    void OnReplySuccess(BaseReply& rReply);

    #ifdef TIZEN_MIGRATION
    void OnFailure(const BaseReply& rReply);
    #endif
};

HERE_MAPS_END_NAMESPACE

#endif
