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

#ifndef GEOCODERQUERYBASE_H
#define GEOCODERQUERYBASE_H

#include "common/HereMaps_global.h"

#include "common/BaseQuery.h"

HERE_MAPS_BEGIN_NAMESPACE

class ApplicationContext;

/**
 * This is the base class for implementations of geocoding query classes. 
 *
 * The virtual method require implementation in derived classes.
 * 
 * \ingroup geocoding
 */
class EXPORT_API GeoCoderQueryBase : public BaseQuery
{
public:
    /**
     * This enumeration defines identifiers for response attribute switches that
     * indicate which attributes are to be included in query responses from the
     * server.
     */
    enum ResponseAttribute
    {
        RA_PerformedSearch,       ///< Indicates that completed searches are to be included in the response.
        RA_Label,                 ///< Indicates that labels are to be included in the response. 
        RA_DidYouMeanSuggestion,  ///< Indicates that did-you-mean suggestions are to be included in the response.
        RA_MatchQuality,          ///< Indicates that match quality is to be included in the response.
        RA_MatchType,             ///< Indicates that match type specifiers are to be included in the response.
        RA_MatchCode,             ///< Indicates that match codes are to be included in the response.
        RA_ParsedRequest,         ///< Indicates that parsed requests are to be included in the response.
        RA_All,                   ///< Indicates that all attributes are to be included in the response.
        RA_None                   ///< Indicates that no attributes are to be included in the response.
    };

    /**
     * This method is the destructor.
     *
     * @return
     */
    ~GeoCoderQueryBase();

    /**
     * This method sets the properties defining a circular area within which a
     * search is to be conducted. The area is defined in terms of its center and
     * radius.
     *
     * @param rCoord A constant reference to an object containing the latitude
     *        and longitude of the center of the proximity area (search center).
     *
     * @param rRadius A value specifying the radius of the search area in meters.
     */
    virtual void SetProximity(const GeoCoordinates& rCoord, float fRadius = 0) = 0;

    /**
     * This method detects whether coordinates/proximity (the center of search area
     * set or not).
     *
     * @return <code>true</code> if the proximity was set,
     *        otherwise <code>false</code>
     */
    virtual bool HasProximity() const = 0;

    /**
     * This method adds a language code provided by the caller to the list of
     * preferred languages.
     *
     * @param sPreferredLang A constant reference to a string containing a BCP
     *        47 language code (see also  http://tools.ietf.org/html/rfc5646). 
     *        identifying the preferred language.  
     */
    void AppendPreferredLanguage(const String& sPreferredLang);

    /**
     * This method retrieves a value indicating the number of preferred
     * languages that have been set.  
     *
     * @return A value indicating how many preferred languages have been set. 
     */
    size_t GetNumPreferredLanguages() const;

    /**
     * This method retrieves the preferred language identifier at the index
     * specified by the caller. The identifier is a BCP 47 language code (see
     * also http://tools.ietf.org/html/rfc5646).
     *
     * @param idx A value representing an index into the array of preferred
     *        languages from which to retrieve the language identifier.
     * 
     * @return A constant pointer to a string containing the language identifier
     *        or <code>NULL</code> if the supplied index is not valid.
     */
    const String* GetPreferredLanguage(size_t idx) const;

    /**
     * This method sets a value indicating the maximum number of query results
     * to be returned.
     *
     * @param uMaxResults A value indicating the maximum number of query results
     * to be returned.
     */
    void SetMaxResults(size_t uMaxResults);

    /**
     * This method sets a value indicating which page is to be returned in a
     * paging scenario. Note that the value has no effect unless a value
     * indicating the maximum number of results to retrieve has been specified
     * (see SetMaxResults).
     *
     * @param uPage An unsigned integer indicating the page number.  
     */
    void SetPageInformation(size_t uPage);
    
    /**
     * This method allows the caller to set a value that determines the 
     * functionality and data delivered by the underlying version of the RESTful
     * service.
     * 
     * @param iValue An integer value that determines the functionality of (and
     *        data delivered by) the underlying RESTful service:
     *        <ul>
     *        <li>0 - indicates the default behavior of the underlying RESTful
     *                service 
     *         </li>
     *         <li>1 - indicates the default behavior of the underlying service and:
     *         <ul><li>reverse geocoding responses include area names if addresses
     *                cannot be determined</li>
     *             <li>addresses/locations can be matched at
     *                intersection level</li>
     *         </ul>  
     *         </li>
     *         <li>2 - as 1 plus:
     *             <ul><li>reverse geocoding responses include the area
     *                 display position (center)</li>
     *                <li>map version can be requested (and
     *                   included in responses)</li>
     *            </ul>  
     *        </li>
     *        </ul>
     */
     void SetGenParameter(int iValue);


    /**
     * This method adds a response attribute specified by the caller.
     *
     * @param aAttr A value identifying the response attribute to add.
     */
    void AddResponseAttribute(ResponseAttribute aAttr);

    /**
     * This method removes the response attribute specified by the caller.
     *
     * @param aAttr A value identifying the response attribute to remove.
     */
    void RemoveResponseAttribute(ResponseAttribute aAttr);

    /**
     * This method adds a key-value pair representing an additional parameter
     * and its value.
     *
     * @param sKey A constant reference to a string containing the name/key of
     *        the additional parameter.  
     * 
     * @param sValue A constant reference to a string containing the value of the
     *        additional parameter. 
     */
    void AddAdditionalParameter(const String& sKey, const String& sValue);

    /**
     * This method returns the base URI to be used for all subsequent
     * geo coder queries.
     *
     * @return A string containing the base URI.
     */
    virtual String GetBaseUri() const = 0;

    /**
     * This method returns the base URI to be used for all subsequent
     * geo coder queries.
     *
     * @param sUri A constant reference to a string containing the base URI.
     */
    virtual void SetBaseUri(const String& sUri) = 0;

protected:

    /**
     * This method is the default constructor.
     */
    GeoCoderQueryBase();

    /**
     * This method obtains the base URL for the service named by the caller.
     *
     * @param sService A constant reference to a string that identifies the
     *        service whose base URL is to be obtained.
     *
     * @param sDst A reference to an object which is to receive the result.
     *
     * @return <code>true</code> if the base URL has been created successfully,
     *        otherwise <code>false</code>
     */
    bool CreateBaseUrl(const String& sService, String& sDst) const;


private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoCoderQueryBase);

    class GeoCoderQueryBaseImpl;
    GeoCoderQueryBaseImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
