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

#ifndef MULTIREVERSEQUERYLISTENER_H
#define MULTIREVERSEQUERYLISTENER_H

#include "common/HereMaps_global.h"
#include "common/QueryListener.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class MultiReverseReply;

/**
 * This class encapsulates a listener facility that is informed when the results
 * of a query become available.
 *
 * The class exposes a callback method that must be implemented by the derived
 * classes to process the data received from the server.
 *
 * @ingroup geocoding
 */
class EXPORT_API MultiReverseQueryListener : public Here::Maps::QueryListener
{
public:
    /**
     * This method is the default constructor.
     */
    MultiReverseQueryListener();

    /**
     * This method is the destructor.
     */
    ~MultiReverseQueryListener();

    /**
     * This method is a callback invoked when data have arrived in response to a
     * geocoding request.
     *
     * @param rReply A Constant reference to an object containing the response data.
     */
    virtual void OnMultiReverseReply(const MultiReverseReply& rReply) = 0;

    #ifdef TIZEN_MIGRATION
    /**
     * This method is a callback invoked when geocoding request is failed.
     *
     * @param rReply A Constant reference to an object containing the response data.
     */
    virtual void OnMultiReverseFailure(const MultiReverseReply& rReply) = 0;
    #endif

private:

    void OnReplySuccess(Here::Maps::BaseReply& rReply);

    #ifdef TIZEN_MIGRATION
    void OnFailure(const Here::Maps::BaseReply& rReply);
    #endif

};

TIZEN_MAPS_END_NAMESPACE

#endif
