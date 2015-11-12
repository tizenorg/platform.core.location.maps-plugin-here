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

#ifndef DISCOVERY_QUERY_H_
#define DISCOVERY_QUERY_H_

#include "common/HereMaps_global.h"
#include "common/BaseQuery.h"
#include "finder/Category.h"
#ifdef TIZEN_CUSTOMIZATION
#include "common/GeoBoundingArea.h"
#endif

HERE_MAPS_BEGIN_NAMESPACE

class QueryListener;
class GeoCoordinates;
class FinderQueryListener;
class FinderError;

/**
 * This class encapsulates a places discovery query.
 * 
 * \ingroup finder
 */
class EXPORT_API DiscoveryQuery : public BaseQuery
{
public:
   /** 
    * This enumeration defines identifiers for the supported discovery query
    * types. 
    */
    enum QueryType
    {
        QT_SEARCH = 0, ///< Indicates a search query (based on the search terms
                       ///  supplied by the application user); results are
                       ///  paginated.
        QT_HERE,       ///< Indicates query that searches for places at or
                       ///  within 200 meters of a specific location; a category
                       ///  can be specified as an option.
        QT_AROUND,     ///< Indicates a query that searches for places within a
                       ///  certain radius around a location; results are
                       ///  paginated; a category can be specified as an option.
        QT_EXPLORE     ///< Indicates a query that searches for popular places
                       ///  based on a location context provided by the
                       ///  application user; results are paginated; a category
                       ///  can be specified as an option.
    };

    /**
     * This enumeration defines identifiers for the supported discovery query
     * result types.
     */
    /*
     * The identifiers are not valid for search QueryTypes.
     */
    enum ResultTypes
    {
        SIT_PLACE = 0,      ///< Indicates that the result contains only place items
        SIT_SEARCH,         ///< Indicates that the result contains only search items
        SIT_PLACEANDSEARCH  ///< Indicates that the result contains place and search items
    };

public:

    /**
     * This method is the default constructor.
     */
    DiscoveryQuery();

    /**
     * This method is a constructor. It constructs a valid <code>DiscoveryQuery</code> from
     * a URL provided by the caller.
     *
     * @param sUrl A constant reference to the URL of the location whose details
     *        are to be retrieved from the server
     */
    DiscoveryQuery(const  String& sUrl);

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~DiscoveryQuery();

    /**
     * This method retrieves a value indicating the query type.
     * 
     * @return A value indicating the query type.
     */
    QueryType GetType() const;

    /**
     * This method sets the query type.
     * 
     * @param eType A value indicating the query type.
     */
    void SetType(QueryType eType);

    /** 
     * This method sets the search text (terms).
     * 
     * @param sSearch A constant reference to a string containing the search
     *        terms.
     */ 
    void SetSearchText(const String& sSearch);

    /** 
     * This method retrieves the search text (terms).
     * 
     * @return A string containing the search terms.
     */ 
    String GetSearchText() const;

    /** 
     * This method retrieves the search proximity.
     * 
     * @return An object containing the geographic coordinates of the location
     *        around which the search is/was to be conducted and within whose
     *        proximity the results must lie.
     */ 
    GeoCoordinates GetProximity() const;

    /** 
     * This method sets search proximity.
     * 
     * @param rCoord An object containing the geographic coordinates of the
     *        location around which the search is/was to be conducted and within
     *        whose proximity the results must lie.
     */ 
    void SetProximity(const GeoCoordinates& rCoord);

#ifdef TIZEN_CUSTOMIZATION
    /** 
     * This method retrieves the bounding area.
     * 
     * @return An object containing the geographic bounding area of the location
     *        around which the search is/was to be conducted and within whose
     *        area the results must lie.
     */ 
    GeoBoundingArea* GetArea() const;

    /** 
     * This method sets search bounding area.
     * 
     * @param rArea An object containing the geographic bounding area of the
     *        location around which the search is/was to be conducted and within
     *        whose bounding area the results must lie.
     */ 
    void SetArea(const GeoBoundingArea &rArea);
#endif

    /**
     * This method retrieves a BCP 47 identifier of the search language.
     *
     * @return A string containing a BCP 47 identifier of the language.
     */
    String GetLanguage() const;

    /**
     * This method sets the langauge, using a BCP 47 langauge code.
     *
     * @param sSearch A constant reference to a string containing a BCP 47
     *        identifier of the language.
     */
    void SetLanguage(const String& sLang);

    /**
     * This method retrieves a value that indicates the maximum number of search
     * results to be retrieved in response to the query.
     * 
     * @return An integer indicating the maximum number of results to be
     *        retrieved.
     */
    size_t GetMaxResults() const;

    /**
     * This method sets a value that indicates the maximum number of search
     * results to be retrieved in response to the query.
     * 
     * @param uMaxResults An integer indicating the maximum number of results to
     *        be retrieved.
     */
    void SetMaxResults(size_t uMaxResults);

    /**
     * This method retrieves a value that indicates the search item types
     *  to be retrieved in response to the query.
     *
     * @return A value indicating the search item type of results to be
     *        retrieved.
     */
    ResultTypes GetResultTypes() const;

    /**
     * This method sets a value that indicates the search item types
     * to be retrieved in response to the query.
     *
     * @param eItemType A value indicating the search item type of results to
     *        be retrieved.
     */
    void SetResultTypes(ResultTypes eItemType);

    /**
     * This method retrieves a list of categories used by the query.
     * 
     * @return An object containing a list of POI categories used by the query. 
     */
    CategoryList GetCategoriesFilter() const;

    /**
     * This method sets a list of categories used by the query.
     * 
     * @param filters A constant reference to an object containing a list of POI
     *          categories used by the query.
     */
    void SetCategoriesFilter(const CategoryList& filters);

    /**
     * This method attempts to establish a connection
     * with the server and then, if the connection has been established, it
     * builds and submits a query.     
     * 
     * @param rDst A reference to an object that is to be notified when the
     *        reply to the query has arrived from the server.
     * 
     * @param pUserData A pointer to user data to be passed back within the
     *        corresponding reply object.
     *
     * @return Identifier of issued request.
     */
    RestItemHandle::RequestId Execute(FinderQueryListener& rListener, Tizen::Maps::HereObject* pUserData = NULL) const;

    /**
     * This method retrieves error information associated with the query.
     *
     * @return A constant pointer to an object containing the error details.
     */
    const FinderError* GetError() const;

    /**
     * This static method returns the base URI to be used for all subsequent
     * discovery queries.
     *
     * @return A string containing the base URI.
     */
    static String GetBaseUri();

    /**
     * This static method returns the base URI to be used for all subsequent
     * discovery queries.
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

    bool AppendService(DiscoveryQuery::QueryType eType, String& sDst) const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(DiscoveryQuery);

    class DiscoveryQueryImpl;
    DiscoveryQueryImpl* m_pImpl;

    friend class DiscoveryReply;

    static String s_sBaseUri;

};

HERE_MAPS_END_NAMESPACE

#endif // DISCOVERY_QUERY_H_
