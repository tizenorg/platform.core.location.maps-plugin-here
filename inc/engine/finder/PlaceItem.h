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

#ifndef PLACE_ITEM_H_
#define PLACE_ITEM_H_

#include <vector>
#include "common/HereMaps_global.h"
#ifndef TIZEN_MIGRATION
#include <FBase.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class GeoCoordinates;
class Category;
class LinkObject;
class GeoBoundingBox;

class PlaceItem;
/**
 * This typedef defines a vector of place items as a type.
 * 
 * \ingroup finder
 */
typedef std::vector< PlaceItem > PlaceItemList;

/**
 * This class encapsulates information about a place that has been returned as
 * part of a reply to a search query (an item in a search result). This
 * information can be used to obtain place details.
 * 
 * \ingroup finder
 */
class EXPORT_API PlaceItem
{
public:

    /**
     * This method is the default constructor.
     */
    PlaceItem();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    PlaceItem(const PlaceItem& rRhs);

    /**
     * This method is the destructor.
     */
    ~PlaceItem();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     * 
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    PlaceItem& operator=(const PlaceItem& rRhs);

    /**
     * This method retrieves the geographic coordinates of the given place.
     * 
     * @return An object containing the geographic coordinates of the place. 
     */
    GeoCoordinates GetPosition() const;

    /**
     * This method retrieves the distance in meters between the given place and
     * the search context (center).
     * 
     * @return A value indicating how far the given place lies from the search
     *        context (center).
     */
    double GetDistance() const;

    /**
     * This method retrieves a value that represents the average rating of the
     * place by users.
     * 
     * @return A value that represents the average rating of the place by users.
     */
    double GetAverageRating() const;

    /**
     * This method retrieves an object representing the category to which the
     * given place is assigned.
     * 
     * @return An object representing the category to which the given place is
     *        assigned.
     */
    Category GetCategory() const;

    /**
     * This method retrieves a link to a resource associated with the given
     * place item.
     * 
     * @return An object encapsulating a link to a resource.
     */
    LinkObject GetLinkObject() const;

    /**
     * This method retrieves text describing the location of the place. The text
     * is typically derived from the address of the place, but may also contain
     * any other information that can help the user understand, where the place is
     * located.
     *
     * @return A string containing the description of the vicinity (location) of
     *       the place.
     */
    String GetVicinity() const;

    /** 
     * This method retrieves a Boolean value indicating if the given search
     * result is sponsored or not.
     * 
     * @return <code>true</code> if the given search result is sponsored,
     *        otherwise <code>false</code>.
     */
    bool GetIsSponsored() const;

    /** 
     * This method retrieves the bounding box enclosing the given place. 
     * 
     * @return An object representing the bounding box (defined in terms of the
     *       geographical coordinates of its top-left and bottom-right corners)
     *       that encloses the given place.
     */
    GeoBoundingBox GetBBox() const;

    /**
     * This method sets the geographic coordinates of the given place.
     * 
     * @param rPosition GeoCoordinates A constant reference to a object
     *        containing the geographic coordinates of the place.
     */
    void SetPosition(const GeoCoordinates& rPosition);

    /**
     * This method sets the distance in meters between the given place and
     * the search context (center).
     * 
     * @param dDistance A value indicating how far the
     *        given place lies from the search context (center).
     */
    void SetDistance(double dDistance);

    /**
     * This method sets a value that represents the average rating of the
     * place by users.
     * 
     * @param dAverageRating A value that represents the average rating of the
     *        place by users.
     */
    void SetAverageRating(double dAverageRating);

    /**
     * This method sets an object representing the category to which the
     * given place is assigned.
     * 
     * @param rCategory A constant reference to an object representing the
     *        category to which the given place is assigned.
     */
    void SetCategory(const Category& rCategory);

    /**
     * This method sets text describing the location of the place. The text
     * is typically derived from the address of the place, but may also contain
     * any other information that may help the user understand, where the place is
     * located.
     *
     * @param sVicinity A constant reference to a string containing the
     *       description of the vicinity (location) of the place.
     */
    void SetVicinity(const String& sVicinity);

    /**
     * This method sets a link to a resource associated with the given
     * place item.
     * 
     * @param rLinkObject A constant reference to an object encapsulating a link
     *        to a resource.
     */
    void SetLinkObject(const LinkObject& rLinkObject);

    /** 
     * This method sets a Boolean value indicating if the given search
     * result item is sponsored or not.
     * 
     * @param bIsSponsored <code>true</code> if the given search result item is
     *        sponsored, otherwise <code>false</code>.
     */
    void SetIsSponsored(bool bIsSponsored);

    /** 
     * This method sets the bounding box enclosing the given place. 
     * 
     * @param rBbox A constant reference to an object representing the bounding
     *       box (defined in terms of the geographical coordinates of its
     *       top-left and bottom-right corners) that encloses the given place.
     */
    void SetBBox(const GeoBoundingBox& rBbox);

private:
    class PlaceItemImpl;
    PlaceItemImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // PLACE_ITEM_H_
