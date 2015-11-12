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

#ifndef DISCOVERY_REPLY_H_
#define DISCOVERY_REPLY_H_

#include "finder/BaseFinderReply.h"
#include "finder/SearchItem.h"
#include "finder/PlaceItem.h"
#include "finder/DiscoveryQuery.h"

HERE_MAPS_BEGIN_NAMESPACE

class SearchContext;

/**
 * This class encapsulates a response to a discovery query. The response is a
 * page of link objects, each containing information about one place. It also
 * includes a link to the next page of results, if available.  
 * 
 * \ingroup finder
 */
class EXPORT_API DiscoveryReply : public BaseFinderReply
{
public:

    /**
     * This is the default constructor. 
     */
    DiscoveryReply();

    /**
     * This is the (virtual) destructor.
     */
    virtual ~DiscoveryReply();

    /**
     * This method retrieves a list of search result items that can lead an
     * application user to detailed information about specific places.
     * 
     * @return A vector of instances of <code>SearchItem</code> which represent
     *       individual search results.
     */
    SearchItemList GetSearchItems() const;

    /**
     * This method retrieves a list of objects each of which contains
     * information about a single place.
     * 
     * @return A vector of instances of <code>PlaceItem</code> which represent
     *       individual places.
     */
    PlaceItemList GetPlaceItems() const;

    /**
     * This method retrieves a string that contains the URL to the next page of
     * search result items. 
     * 
     * @return A string containing the URL to a page containing the next set of
     *       results.
     */
    String GetNextResultsString() const;

    /**
     * This method retrieves the offset (index) of the first item on the
     * current page of results
     * 
     * @return An integer indicating the index of the first result item on the
     *       current page.
     */
    size_t GetOffset() const;

    /**
     * This method retrieves an object that defines the search context used in
     * the original query.
     * 
     * @return An object containing the search context.
     */
    SearchContext GetSearchContext() const;

    /**
     * This method retrieves a query object that can be used to retrieve the
     * next page of results.
     * 
     * @return A pointer to an object encapsulating a query to the next page of
     *       results.
     */
    DiscoveryQuery* GetNextPageQuery() const;

private:
    void SetSearchItems(const SearchItemList&);
    void SetPlaceItems(const PlaceItemList&);
    void SetNextResults(const String&);
    void SetOffset(size_t);
    void SetSearchContext(const SearchContext& sContext);
    
private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(DiscoveryReply);
    friend class TestDiscoveryReply;

    virtual bool OnDataReceived(const unsigned char* pBuffer, size_t uSize);

    class DiscoveryReplyImpl;
    DiscoveryReplyImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // DISCOVERY_REPLY_H_
