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

#ifndef PLACE_DETAILS_H_
#define PLACE_DETAILS_H_

#include "finder/ContactDetails.h"
#include "finder/PlacesGlobals.h"
#include "finder/Category.h"
#include "finder/ImageContent.h"
#include "finder/ReviewContent.h"
#include "finder/EditorialContent.h"
#include "finder/ExtendedAttribute.h"
#include "common/HereMaps_global.h"
#include "internal/StringHelper.h"

#include <map>

HERE_MAPS_BEGIN_NAMESPACE

class Ratings;
class GeoLocation;
class ExtendedAttribute;
class RelatedItem;
class BaseContent;

/**
 * This class encapsulates detailed information about a place, including name,
 * id, contact, category, location, ratings, review(s) and image(s).
 * 
 * \ingroup finder
 */
class EXPORT_API PlaceDetails
{
public:
    /**
     * This typedef defines a map holding alternative place names as a type.
     */ 
   typedef std::map< String, std::vector< String >, TSPredicate > AlternativeNames;

public:
    /**
     * This method is the default constructor.
     */
    PlaceDetails();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    PlaceDetails(const PlaceDetails& rRhs);

    /**
     * This method is the destructor.
     */
    ~PlaceDetails();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     * 
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    PlaceDetails& operator=(const PlaceDetails& rRhs);

    /**
     * This method retrieves the name of the place.
     * 
     * @return A string containing the place name.
     */ 
    String GetName() const;

    /**
     * This method retrieves the place id, which is a unique identifier in the
     * Places database and can be used to obtain the complete information
     * about the place.
     * 
     * @return A string containing the unique id of the place.
     */ 
    String GetPlaceId() const;    

    /**
     * This method retrieves a link to a representation of the
     * place that can be viewed by end users.
     * 
     * @return A string containing a link to a view of the place.
     */ 
    String GetView() const;

    /**
     * This method retrieves a map object containing the alternative names of the
     * place.  
     * 
     * @return An object containing the alternative names of the place.
     */ 
    AlternativeNames GetAlternativeNames() const;

    /**
     * This method retrieves detailed location information for the place.
     * 
     * @return An object containing the address and the geographical coordinates
     *       of the place.
     */ 
    GeoLocation GetLocation() const;

    /**
     * This method retrieves basic information about the place.
     * 
     * @return An object containing basic information about the place.
     */ 
    BaseContent GetBaseContent() const;

    /**
     * This method retrieves a list of contact types available for the given
     * place. Contact types can include telephone, e-mail, website, site, etc.
     * 
     * @return A list of strings containing contact type identifiers. The
     *       possible values for contact type identifiers are "phone",
     *       "website", "fax", or "email".
     */
    StringList GetContactTypes() const;

    /**
     * This method retrieves a list of contact details for the given place. 
     * 
     * @return A vector containing instances of <code>ContactDetails</code>.
     */ 
    ContactDetailsList GetContactDetails() const;

    /**
     * This method retrieves a list of categories applicable to the given place.
     * 
     * @return A vector containing instances of <code>Category</code>
     */ 
    CategoryList GetCategories() const;

    /**
     * This method retrieves information on user rating of the given place.
     * 
     * @return An object containing user rating information.
     */ 
    Ratings GetRatings() const;

    /**
     * This method retrieves the URI of the icon that represents the given
     * place.
     * 
     * @return A URI of the place icon.
     */ 
    String GetIconPath() const;

    /**
     * This method retrieves a list object containing image content information
     * for images relating to the given place.
     * 
     * @return An object containing a vector of instances of
     *        <code>ImageContent</code>.
     */ 
    ImageContentList GetImageContent() const;

    /**
     * This method retrieves a list object containing review content
     * relating to the given place.
     * 
     * @return An object containing a vector of instances of
     *        <code>ReviewContent</code>.
     */ 
    ReviewContentList GetReviewContent() const;

    /**
     * This method retrieves a list object containing editorial content
     * relating to the given place.
     * 
     * @return An object containing a vector of instances of
     *        <code>EditorialContent</code>.
     */ 
    EditorialContentList GetEditorialContent() const;

    /**
     * This method retrieves a list of strings, each containing an identifier of
     * an extended attribute type applicable to the given place.
     * 
     * @return A list of strings containing extended attribute type identifiers.
     */ 
    StringList GetExtendedAttributeTypes() const;

    /**
     * This method retrieves a list object containing extended attributes
     * applicable to the given place. 
     * 
     * @return An object containing a vector of instances of
     *        <code>ExtendedAttribute</code>.  
     */ 
    ExtendedAttributeList GetExtendedAttributes() const;

    /**
     * This method retrieves an object containing a list of places that
     * are related to the given place (or places that may be be interesting to
     * users who have looked at the given place).
     * 
     * @return An object encapsulating places related to the given place. 
     */ 
    RelatedItem GetRelatedItem() const;

    /**
     * This method sets the name of the place.
     * 
     * @param rsName A constant reference to a string containing the place name.
     */ 
    void SetName(const String& rsName);

    /**
     * This method sets the place id, which is a unique identifier in the
     * Places database and can be used to obtain the complete information
     * about the place.
     * 
     * @param rsIdentifier A constant reference to a string containing the
     *        unique id of the place.
     */ 
    void SetPlaceId(const String& rsIdentifier);

    /**
     * This method sets a link to a representation of the
     * place that can be viewed by end users.
     * 
     * @param rsView A constant reference to a string containing a link to a
     *        view of the place.
     */ 
    void SetView(const String& rsView);

    /**
     * This method sets a map object containing the alternative names of the
     * place.  
     * 
     * @param vNames A constant reference to an object containing the alternative
     *        names of the place.
     */ 
    void SetAlternativeNames(const AlternativeNames& vNames);

    /**
     * This method sets the location details for the place.
     * 
     * @param rLocation A constant reference to an object containing the address
     *       and the geographical coordinates of the place.
     */ 
    void SetLocation(const GeoLocation& rLocation);

    /**
     * This method sets basic information about the place.
     * 
     * @param rContent A constant reference to an object containing basic
     *        information about the place.
     */ 
    void SetContent(const BaseContent& rContent);

    /**
     * This method sets a list of contact details for the given place. 
     * 
     * @param vDetails A constant reference to a vector containing instances of
     *    <code>ContactDetails</code>.
     */ 
    void SetContactDetails(const ContactDetailsList& vDetails);

    /**
     * This method sets a list of (POI) categories applicable to the given place.
     * 
     * @param rvCategories A constant reference to a vector containing instances
     *        of <code>Category</code>
     */ 
    void SetCategories(const CategoryList& rvCategories);

    /**
     * This method sets information on user rating of the given place.
     * 
     * @param rRatings A constant reference to an object containing user rating
     *        information.
     */ 
    void SetRatings(const Ratings& rRatings);

    /**
     * This method sets the URI of the icon that represents the given
     * place.
     * 
     * @param rIcon A constant reference to an object containing the URI of the
     *        place icon.
     */ 
    void SetIconPath(const String rIcon);

    /**
     * This method sets a list object containing image content data
     * for images relating to the given place.
     * 
     * @param rContent A constant reference to a vector of
     *        instances of <code>ImageContent</code>.
     */ 
    void SetImageContent(const ImageContentList& rContent);

    /**
     * This method sets a list object containing review content
     * relating to the given place.
     * 
     * @param rContent A constant reference to a vector of
     *        instances of <code>ReviewContent</code>.
     */ 
    void SetReviewContent(const ReviewContentList& rContent);

    /**
     * This method sets a list object containing editorial content
     * relating to the given place.
     * 
     * @param rContent A constant reference to a vector of
     *          instances of <code>EditorialContent</code>.
     */ 
    void SetEditorialContent(const EditorialContentList& rContent);

    /**
     * This method sets a list object containing extended attributes
     * applicable to the given place. 
     * 
     * @param rAttribute A constant reference to a vector of
     *        instances of <code>ExtendedAttribute</code>.
     */ 
    void SetExtendedAttributes(const ExtendedAttributeList& rAttribute);

    /**
     * This method sets an object containing a list of places that
     * are related to the given place (or places that may be of interest to
     * users who have looked at the given place).
     * 
     * @param rAttribute A constant reference to a object encapsulating places
     *        related to the given place.
     */ 
    void SetRelatedItem(const RelatedItem& rAttribute);

private:
    class PlaceDetailsImpl;
    PlaceDetailsImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // PLACE_DETAILS_H_
