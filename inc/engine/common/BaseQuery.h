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

#ifndef BASEQUERY_H
#define BASEQUERY_H

#include "common/HereMaps_global.h"
#include "common/QueryListener.h"
#include "common/RestItemHandle.h"
#ifdef TIZEN_MIGRATION
#include "base/HereObject.h"
#else
#include <FBase.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class BaseReply;
class QueryListener;
class GeoCoordinates;
class GeoBoundingBox;

/**
 * This class is the base class representing any rest based query class
 * in this library
 */
class BaseQuery
{
public:
    typedef int RequestId;

    /**
     * This is the destructor.
     */
    virtual ~BaseQuery();

    /**
     * This method creates the query URI. It is to be implemented be derived classes.
     *
     * @return URI string.
     */
    virtual String CreateUri() const = 0;

protected:
    /**
     * This constant represents an illegal URL (an empty string).
     */
    static const String ILLEGAL_URL;

    /**
     * This is the default constructor.
     */
    BaseQuery();

    /**
     * This method appends authentication credentials to the query. The
     * authentication credentials are <code>app_id</code> and
     * <code>app_code</code>. The method obtains the credentials set at
     * initialization and copies them to the destination provided by the caller,
     * following the standard query-parameter format:
     * <code>app_id=app_id_value&app_code=app_code_value<code>
     *
     * @param sDst A reference to a string to receive the authentication
     * credentials.
     *
     * @return <code>true</code> if the destination string has been set with the
     *        authentication credentials, <code>false</code> if the the
     *        <code>ApplicationContext</code> is uninitialized.
     */
    bool AppendCredentials(String& sDst) const;

#ifndef TIZEN_MIGRATION
    /**
     * This method retrieves the user data associated with the query.
     *
     * @return A pointer to an object containing the user data.
     */
    Tizen::Maps::HereObject* GetUserData() const;
#endif

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(BaseQuery);

    class BaseQueryImpl;
    BaseQueryImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif // BASEQUERY_H
