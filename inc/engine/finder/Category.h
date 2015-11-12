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

#ifndef CATEGORY_H_
#define CATEGORY_H_

#include <vector>
#include "common/HereMaps_global.h"
#ifndef TIZEN_MIGRATION
#include <FBase.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class CategoryId;
class Category;


/**
 * This typedef defines a type representing a list of <code>Category</code>
 * instances. 
 * 
 * \ingroup finder
 */
typedef std::vector<Category> CategoryList;

/**
 * This class encapsulates information about a Point of Interest (POI) category
 * that can be applied to a place.
 * 
 * \ingroup finder
 */
class EXPORT_API Category
{
public:

    /**
     * This method is the default constructor.
     */
    Category();

    /**
     * This method is a constructor.
     */
    Category(const CategoryId& rId);

   /**
    * This method is a copy constructor.
    * 
    * @param rRhs An object whose contents are to be copied to the instance
    *        being created.
    */
    Category(const Category& rRhs);

   /**
    * This method is the (virtual) destructor.
    */
    virtual ~Category();

   /**
    * This is the assignment operator.
    * 
    * @param rRhs An object whose contents are to be copied to the given
    *        instance.
    * 
    * @return A reference to the given instance of the class after its contents
    *       have been updated.
    */
    Category& operator=(const Category& rRhs);

    /**
     * This method retrieves the category identifier.
     *
     * @return A string containing the identifier of the POI category. 
     */
    const CategoryId& GetCategoryId() const;

    /**
     * This method sets the category identifier.
     *
     * @param rsId A constant reference to an object containing the identifier
     *        of the POI category.
     */
    void SetCategoryId(const CategoryId& rsId);

    /**
     * This method retrieves the category name (localized).
     *
     * @return A string containing the localized name of the POI category.  
     */
    String GetTitle() const;

    /**
     * This method retrieves the URI of the category resource (icon).
     *
     * @return A string containing the URI of the icon of the POI category.  
     */
    String GetHref() const;

    /**
     * This method retrieves the resource type identifier for the given
     * category. 
     *
     * @return A string containing the type identifier, which is either a valid
     *        MIME type or a URI.
     */
    String GetType() const;

    /**
     * This method retrieves the path to the category icon.
     *
     * @return A URI object containing the path to the category icon.
     */
    String GetIconPath() const;

    /**
     * This method sets the category name (localized).
     *
     * @param sTitle A constant reference to a string containing the localized
     *        name of the POI category.
     */
    void SetTitle(const String& sTitle);

    /**
     * This method sets the URI of the category resource (icon).
     *
     * @param sHref A constant reference to a string containing the URI of the icon
     *        of the POI category.
     */
    void SetHref(const String& sHref);

    /**
     * This method sets the resource type identifier for the given
     * category. 
     *
     * @param sType A constant reference to a string containing the type
     *        identifier, which is either a valid MIME type or a URI.
     */
    void SetType(const String& sType);

    /**
     * This method sets the path to the category icon.
     *
     * @param rIcon A constant reference to a URI object containing the path to
     *        the category icon.
     */
    void SetIconPath(const String& rIcon);

private:
    class CategoryImpl;
    CategoryImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // CATEGORY_H_
