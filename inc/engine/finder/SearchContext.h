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

#ifndef SEARCH_CONTEXT_H_
#define SEARCH_CONTEXT_H_

#include "common/HereMaps_global.h"
#ifndef TIZEN_MIGRATION
#include <FBase.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class GeoLocation;

/**
 * This class encapsulates the search context used in queries. The context
 * defines the point around which the search is conducted or an area within
 * which the search is conducted. 
 * 
 * \ingroup finder
 */
class SearchContext
{
public:

    /**
     * This method is the default constructor.
     */
    SearchContext();

    /**
     * This method is the copy constructor.
     *
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    SearchContext(const SearchContext& rRhs);

    /**
     * This method is the destructor.
     */
    ~SearchContext();

    /**
     * This is the assignment operator.
     *
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     *
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    SearchContext& operator=(const SearchContext& rRhs);

    /**
     * This method retrieves a Boolean value that indicates if the retrieved
     * location is different from the location context used in the search. The
     * retrieved location is not the same as the location context, typically when
     * the location context is implicit (derived from request headers).
     * 
     * @return <code>true</code> if the retrieved location is different from the
     *       one used in the search, otherwise <code>false</code>.
     */
    bool GetMoved() const;

    /**
     * This method retrieves an object containing the details of the search
     * context such as the geographic coordinates and street address.
     * 
     * @return An object containing the details of the search context
     *        (geographic coordinates and address if available)
     */
    GeoLocation GetLocation() const;

    /** 
     * This method retrieves the media type specifier for the given search
     * context.
     *
     * @return A string containing the media type specifier for the search
     *        context,  "urn:nlp-types:place".
     */  
    String GetType() const;

    /** 
     * This method retrieves the title of the given search context.
     * 
     * @return A string containing the title of the search context.
     */
    String GetTitle() const;

    /** 
     * This method retrieves a link to the details of the place at
     * the center of the search context. Note that the link is available only if
     * the search context points to a recognized place, rather than, for
     * example, the middle of an ocean. 
     * 
     * @return A URI (link) to the details of the place at the center of the
     *       search context, if available.
     */
    String GetHref() const;

    /**
     * This method sets a Boolean value that indicates if the retrieved
     * location is different from the location context used in the search. The
     * retrieved location is not the same as the location context, typically when
     * the location context is implicit (derived from request headers).
     * 
     * @param bMoved <code>true</code> if the retrieved location is different from the
     *       one used in the search, otherwise <code>false</code>.
     */
    void SetMoved(bool bMoved);

    /**
     * This method sets an object containing the details of the search
     * context such as the geographic coordinates and street address.
     * 
     * @return A constant reference to an object containing the details of the
     *        search context (geographic coordinates and address if available)
     */
    void SetLocation(const GeoLocation& rLocation);

    /** 
     * This method sets the media type specifier for the given search
     * context.
     *
     * @param sType A constant reference to a string containing the media type
     *        specifier for the search context, "urn:nlp-types:place".
     */  
    void SetType(const String& sType);

    /** 
     * This method sets the title of the given search context.
     * 
     * @param sTitle A constant reference to a string containing the title of
     *        the search context.
     */
    void SetTitle(const String& sTitle);

    /** 
     * This method sets a link to the details of the place at
     * the center of the search context. Note that the link is available only if
     * the search context points to a recognized place, rather than, for
     * example, the middle of an ocean. 
     * 
     * @param uHref A constant reference to a URI (link) to the details of the
     *        place at the center of the search context, if available.
     */
    void SetHref(const String& uHref);

private:
    class SearchContextImpl;
    SearchContextImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // SEARCH_CONTEXT_H_
