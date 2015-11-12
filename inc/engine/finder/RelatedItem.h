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

#ifndef RELATED_ITEM_H_
#define RELATED_ITEM_H_

#include "common/HereMaps_global.h"

#ifndef TIZEN_MIGRATION
#include <FBase.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates an item related to a place returned as part of a
 * response to a query. 
 * 
 * \ingroup finder
 */
class EXPORT_API RelatedItem
{
public:

    /**
     * This method is the default constructor.
     */
    RelatedItem();

    /**
     * This method is the copy constructor.
     *
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    RelatedItem(const RelatedItem& rRhs);

    /**
     * This method is the destructor.
     */
    ~RelatedItem();

    /**
     * This is the assignment operator.
     *
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     *
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    RelatedItem& operator=(const RelatedItem& rRhs);

    /** 
     * This method retrieves the title/name of the related/recommended item. 
     * 
     * @return A string containing the title or name.
     */
    String GetTitle() const;

    /** 
     * This method retrieves the type specifier for the related/recommended item.
     * 
     * @return A string containing the type specifier for the
     *       related/recommended item.
     */
    String GetType() const;

    /** 
     * This method retrieves a hyperlink that refers to the resource
     * represented by the related/recommended item.
     * 
     * @return A string containing a hyperlink that refers to the resource
     *        represented by the related/recommended item.
     */
    String GetHref() const;

    /** 
     * This method sets the title/name of the related/recommended item. 
     * 
     * @param sTitle A constant reference to a string containing the title or
     *        name.
     */
    void SetTitle(const String& sTitle);

    /** 
     * This method sets the type specifier for the related/recommended item.
     * 
     * @param sType A constant reference to a string containing the type
     *       specifier for the related/recommended item.
     */
    void SetType(const String& sType);

    /** 
     * This method sets a hyperlink that refers to the resource
     * represented by the related/recommended item.
     * 
     * @param uHref A constant reference to an object containing a hyperlink that
     *        refers to the resource represented by the related/recommended
     *        item.
     */
    void SetHref(const String& uHref);

private:
    class RelatedItemImpl;
    RelatedItemImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // RELATED_ITEM_H_

