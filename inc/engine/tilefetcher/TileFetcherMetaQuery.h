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

#ifndef TILEFETCHERMETAQUERY_H
#define TILEFETCHERMETAQUERY_H

#include "common/HereMaps_global.h"
#include "common/BaseQuery.h"


HERE_MAPS_BEGIN_NAMESPACE

class TileFetcherMetaQueryListener;

/**
 * This class encapsulates a query representing a map tile metadata request.
 * 
 * \ingroup tilefetcher
 */
class TileFetcherMetaQuery : public BaseQuery
{
public:
    /**
     * This method is the constructor.
     *
     * @param sUri A constant reference to a string containing the base URL
     *        which is used in the query.
     */
    TileFetcherMetaQuery( const String& sUri );

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~TileFetcherMetaQuery();

    /**
     * This method attempts to establish a connection with the server and then,
     * if the connection has been established, it builds and submits a query.
     *
     * @param rListener A reference to a an object that is to be notified when
     *        the reply to the query has arrived from the server.
     *
     * @param pUserData A pointer to user passed data that will be received
     *        back through the reply object.
     *
     * @return <code>NULL</code> if a connection to the server cannot be
     *        established, a pointer to the request object handle if the query
     *        has been submitted successfully. Note that <code>true</code> does
     *        not indicate that a reply is available.
     */
    RequestId Execute(TileFetcherMetaQueryListener& rListener, Tizen::Maps::HereObject* pUserData = NULL) const;

    /**
     * This static method obrains the base URI to be used for all subsequent
     * tile fetcher queries.
     *
     * @return A string containing the base URI.
     */
    static String GetBaseUri();

    /**
     * This static method obtains the base URI to be used for all subsequent
     * tile fetcher queries.
     *
     * @param sUri A constant reference to a string containing the base URI.
     */
    static void SetBaseUri(const String& sUri);

private:
    /**
     * This method creates the URI for the request.
     *
     * @return URI request string.
     */
    String CreateUri() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(TileFetcherMetaQuery);

    String m_sBaseUri;
};

HERE_MAPS_END_NAMESPACE

#endif
