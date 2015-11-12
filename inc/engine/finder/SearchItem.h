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

#ifndef SEARCH_ITEM_H_
#define SEARCH_ITEM_H_

#include <vector>
#include "common/HereMaps_global.h"
#ifndef TIZEN_MIGRATION
#include <FBase.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class LinkObject;

class SearchItem;
/** 
 * This typedef defines a list of search items as a type.
 */
typedef std::vector< SearchItem > SearchItemList;

/**
 * This class encapsulates a search item returned by the server as part of a
 * response to a discovery query. 
 *
 * \ingroup finder
 */
class SearchItem
{
public:

    /**
     * This method is the default constructor.
     */
    SearchItem();

    /**
     * This method is the copy constructor.
     *
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    SearchItem(const SearchItem& rRhs);

    /**
     * This method is the destructor.
     */
    ~SearchItem();

    /**
     * This is the assignment operator.
     *
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     *
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    SearchItem& operator=(const SearchItem& rRhs);

    /**
     * This method retrieves the link object from the given search item. The
     * link points to another resource.
     * 
     * @return An object containing a link to another resource.
     */
    LinkObject GetLinkObject() const;

    /**
     * This method retrieves the URI to the detailed information about the place
     * to which the given search item refers.
     * 
     * @return The URI of the detailed information about the
     *        place to which the given search item refers.
     */
    String GetPlacesPath() const;

    /**
     * This method retrieves a value representing the weighting of the given
     * search item.
     * 
     * @return A value that represents the weighting of the given
     *        search item. 
     */
    double GetWeight() const;

    /**
     * This method sets the link object from the given search item. The
     * link points to another resource.
     * 
     * @param uLink A constant reference to an object containing a link to
     *        another resource.
     */
    void SetLinkObject(const LinkObject& uLink);

    /**
     * This method sets the URI to the detailed information about the place
     * to which the given search item refers.
     * 
     * @param uPlacesPath A constant reference to an object containing the URI
     *        of the detailed information about the place to which the given
     *        search item refers.
     */
    void SetPlacesPath(const String& uPlacesPath);

    /**
     * This method sets a value representing the weighting of the given
     * search item.
     * 
     * @param dWeight A value that represents the weighting of the given search
     *        item.
     */
    void SetWeight(double dWeight);

private:

    class SearchItemImpl;
    SearchItemImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // SEARCH_ITEM_H_
