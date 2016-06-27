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

#ifndef RESTITEMHANDLE_H
#define RESTITEMHANDLE_H

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class represents a handle to a REST request. 
 *
 */
class EXPORT_API RestItemHandle
{
public:
    /**
     * This typedef defines a type that represents a REST request id.
     */
    typedef int RequestId;

    /**
     * This constant represents a passive REST request item.
     */
    static const RequestId PASSIVE_RESTITEM;

    /**
     * This constant represents an invalid REST request item.
     */
    static const RequestId INVALID_RESTITEM;

    /**
     * This method is a virtual destructor. 
     */
    virtual ~RestItemHandle();

    /**
     * This methos cancels a request with the id specified by the caller.
     *
     * @param aRequestId A value indicating the id of the request to cancel.
     */
    static void Cancel(RequestId aRequestId);

    /**
     * This method checks if the request id provided by the caller is valid.
     *
     * @param aRequestId A value indicating the id of the request to cancel.
     */
    static bool IsValid(RequestId aRequestId);

private:
    RestItemHandle();
};

HERE_MAPS_END_NAMESPACE

#endif