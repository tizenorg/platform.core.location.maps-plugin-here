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

#ifndef GEOROUTEREPLY_H
#define GEOROUTEREPLY_H

#include "common/HereMaps_global.h"
#include "common/BaseReply.h"
#include "routes/GeoRoute.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoRouteQuery;

/**
 * This class encapsulates a response to a route calculation request query. 
 * 
 * \ingroup routes
 */
class EXPORT_API GeoRouteReply : public BaseReply
{
public:

    /**
     * This is the default constructor. 
     */
    GeoRouteReply();

    /**
     * This is the (virtual) destructor.
     */
    virtual ~GeoRouteReply();

    /** 
     * This method retrieves the original route query request.
     * 
     * @return An object that encapsulates the original route query request.
     */
    GeoRouteQuery GetRequest() const;

    /**
     * This method retrieves a list of routes calculated in response to the
     * request (see <code>GetRequest</code>).
     * 
     * @return A reference a an object containing the calculated routes.
     */
    GeoRouteList& GetRoutes() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoRouteReply);
    friend class TestGeoRouteReply;

    virtual bool OnDataReceived(const unsigned char* pBuffer, size_t uSize);

    void SetRequest(const GeoRouteQuery& aGeoRouteQuery);
    void SetRoutes(const GeoRouteList& rRoutes);

private:
    class GeoRouteReplyImpl;
    GeoRouteReplyImpl* m_pImpl;

    friend class GeoRouteReplyImpl;
    friend class GeoRouteQuery;
};

HERE_MAPS_END_NAMESPACE

#endif /* GEOROUTEREPLY_H */
