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

#ifndef BASEREPLY_H
#define BASEREPLY_H

#include "common/HereMaps_global.h"
#include "common/QueryListener.h"

#ifdef TIZEN_MIGRATION
#include <base/HereObject.h>
#else
#include <FBaseObject.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class ErrorBase;

/**
 * This class is the base class that encapsulates a reply to a REST-based query.
 * 
 * @ingroup TODO
 */
class EXPORT_API BaseReply
{
public:
    /**
     * This method is a destructor.
     */
    virtual ~BaseReply();

    /**
     * This method retrieves error information associated with the query
     * response received from the server.
     * 
     * @return A constant pointer to an object containing the error details.
     */
    const ErrorBase* GetError() const;

    /**
     * This method sets (saves) a pointer to user data associated with the
     * reply to the query.
     *
     * @param pUserData A pointer to user data.
     */
     void SetUserData(Tizen::Maps::HereObject* pUserData);

    /**
     * This method retrieves the pointer the user data.
     *
     * @return A pointer to the user data.
     */
    Tizen::Maps::HereObject* GetUserData() const;

protected:
    /**
     * This method is the default constructor. 
     */
    BaseReply();

    /**
     * This method appends information about an error associated with the server
     * response. 
     *
     * @param rError A reference to an object containing the error details.
     */
    void Append(ErrorBase& rError);

private:
    virtual bool OnDataReceived(const unsigned char* pBuffer, size_t uSize) = 0;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(BaseReply);
    friend class RestItem;

    class BaseReplyImpl;
    BaseReplyImpl* m_pImpl;
};

typedef std::tr1::shared_ptr<BaseReply> BaseReplyPtr;

HERE_MAPS_END_NAMESPACE

#endif // BASEREPLY_H
