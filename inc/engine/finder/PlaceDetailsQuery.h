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

#ifndef PLACE_DETAILS_QUERY_H
#define PLACE_DETAILS_QUERY_H

#include "common/HereMaps_global.h"
#include "common/BaseQuery.h"

HERE_MAPS_BEGIN_NAMESPACE

class PlaceDetailsReply;
class FinderQueryListener;
class FinderError;

/**
 * This class encapsulates a request for detailed information about a specific
 * place. 
 * 
 * \ingroup finder
 */ 
class EXPORT_API PlaceDetailsQuery : public BaseQuery
{
public:

    /**
     * This method is the default constructor.
     */
    PlaceDetailsQuery();

    /**
     * This method is a copy constructor.
     * 
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    PlaceDetailsQuery(const PlaceDetailsQuery& rRhs);

    /**
     * This method is the destructor.
     */
    ~PlaceDetailsQuery();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     * 
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    PlaceDetailsQuery& operator=(const PlaceDetailsQuery& rRhs);

    /** 
     * This method sets the place id.
     * 
     * @param rPlaceId A constant reference to a string containing the unique
     *       identifier of the place whose details are to be obtained.
     */
    void SetPlaceId(const String& rPlaceId);

    /** 
     * This method retrieves the place id.
     * 
     * @return A string containing the unique identifier of the place whose
     *       details are to be obtained.
     */
    String GetPlaceId() const;

    /**
     * This method retrieves a BCP 47 code representing the search language.
     *
     * @return A string containing a BCP 47 identifier of the language.
     */
    String GetLanguage() const;

    /**
     * This method sets the langauge, using a BCP 47 identifier.
     *
     * @param sSearch A constant reference to a string containing a BCP 47
     *        identifier of the language.
     */
    void SetLanguage(const String& sLang);

    /**
     * This method attempts to establish a connection with the server and then,
     * if the connection has been established, builds and submits a query.
     * 
     * @param rListener A reference to an object that is to be notified when the
     *        reply to the query has arrived from the server.
     * 
     * @param pUserData A pointer to user data to be passed back within the
     *        corresponding reply object.
     *
     * @return Identifier of issued request.
     */
    RestItemHandle::RequestId Execute(FinderQueryListener& rListener, Tizen::Maps::HereObject* pUserData = NULL, const char* pUrl="") const;

    /**
     * This method retrieves error information associated with the query parameters
     *
     * @return A constant pointer to an object containing the error details.
     */
    const FinderError* GetError() const;

    /**
     * This static method returns the base URI to be used for all subsequent
     * place detail queries.
     *
     * @return A string containing the base URI.
     */
    static String GetBaseUri();

    /**
     * This static method returns the base URI to be used for all subsequent
     * place detail queries.
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
    class PlaceDetailsQueryImpl;
    PlaceDetailsQueryImpl* m_pImpl;

    static String s_sBaseUri;

};

HERE_MAPS_END_NAMESPACE

#endif // PLACE_DETAILS_QUERY_H
