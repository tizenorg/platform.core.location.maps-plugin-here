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

#ifndef CATEGORYID_H_
#define CATEGORYID_H_

#include "common/HereMaps_global.h"

#ifdef TIZEN_MIGRATION
namespace Here { namespace PlugIn { //for plug-in
class HerePlace;
}}
#endif

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class represents a (Place of Interest or POI) category identifier.
 * \ingroup Finder
 */
class EXPORT_API CategoryId
{
public:

    /** 
     * This method is the destructor. 
     */
    virtual ~CategoryId( );

   /**
    * This method checks if the given instance of <code>CategoryId</code> is
    * valid. An instance of this class is valid if its id element is not empty.  
    * 
    * @return <code>true</code> if the instance is valid, otherwise
    *        <code>false</code>.
    */
    bool IsValid( ) const;

    /**
     * This method obtains a string representation of the given instance.
     * 
     * @return A Unicode string containing a string representation of the given
     *        instance of <code>CategoryId</code>.
     */
    String ToString( ) const;

    /**
     * This method obtains an invalid category id object.
     * 
     * @return A constant reference to an invalid category id object.
     */
    static const CategoryId& GetInvalidCategoryId( );

    /**
     * This method obtains the id of the root category from the given instance.
     * 
     * @return A constant reference to an instance of the class representing the
     *        root category id.
     */
    static const CategoryId& GetRootCategoryId( );

    // Factory methods for category filters
    /**
     * This factory method obtains a category id object representing the
     * eat-drink category. 
     * 
     * @return A constant reference to an instance of the class representing the
     *        eat-drink category id.
     */
    static const CategoryId& GetEatDrinkCategoryId();

    /**
     * This factory method obtains a category id object representing the
     * going-out category. 
     * 
     * @return A constant reference to an instance of the class representing the
     *        going-out category id.
     */
    static const CategoryId& GetGoingOutCategoryId();

    /**
     * This factory method obtains a category id object representing the
     * sights-museums category. 
     * 
     * @return A constant reference to an instance of the class representing the
     *        sights-museums category id.
     */
    static const CategoryId& GetSightsMuseumsCategoryId();

    /**
     * This factory method obtains a category id object representing the
     * transport category. 
     * 
     * @return A constant reference to an instance of the class representing the
     *        transport category id.
     */
    static const CategoryId& GetTransportCategoryId();

    /**
     * This factory method obtains a category id object representing the
     * accommodation category. 
     * 
     * @return A constant reference to an instance of the class representing the
     *        accommodation category id.
     */
    static const CategoryId& GetAccommodationCategoryId();

    /**
     * This factory method obtains a category id object representing the
     * shopping category. 
     * 
     * @return A constant reference to an instance of the class representing the
     *        shopping category id.
     */
    static const CategoryId& GetShoppingCategoryId();

    /**
     * This factory method obtains a category id object representing the
     * leisure-outdoor category. 
     * 
     * @return A constant reference to an instance of the class representing the
     *        leisure-outdoor category id.
     */
    static const CategoryId& GetLeisureOutdoorCategoryId();

    /**
     * This factory method obtains a category id object representing the
     * administrative-areas-buildings category. 
     * 
     * @return A constant reference to an instance of the class representing the
     *        administrative-areas-buildings category id.
     */
    static const CategoryId& GetAdministrativeAreasBuildingsCategoryId();

    /**
     * This factory method obtains a category id object representing the
     * natural-geographical category. 
     * 
     * @return A constant reference to an instance of the class representing the
     *        natural-geographical category id.
     */
    static const CategoryId& GetNaturalGeographicalCategoryId();

private:
    CategoryId(const CategoryId&);
    CategoryId& operator=(const CategoryId&);

    /** Create an invalid instance */
    CategoryId( const String& id);

private:
    class CategoryIdImpl;
    CategoryIdImpl* m_pImpl;

    friend class JsonParser;
    friend class Category;
    friend class TestCategoryId;
#ifdef TIZEN_MIGRATION
    friend class Here::PlugIn::HerePlace; //for plug-in
#endif
};


HERE_MAPS_END_NAMESPACE

#endif // CATEGORYID_H_
