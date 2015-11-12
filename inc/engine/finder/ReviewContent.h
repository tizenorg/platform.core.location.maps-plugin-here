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

#ifndef REVIEW_CONTENT_H_
#define REVIEW_CONTENT_H_

#include <vector>
#include "common/HereMaps_global.h"
#ifndef TIZEN_MIGRATION
#include <FBaseDateTime.h>
#endif

#include "finder/BaseContent.h"

HERE_MAPS_BEGIN_NAMESPACE

class LinkObject;

class ReviewContent;
/**
 * This typedef defines a list or review content items as a type.
 */
typedef std::vector<ReviewContent> ReviewContentList;

/**
 * This class encapsulates the content of a review related to a place.
 * 
 * \ingroup finder
 */
class EXPORT_API ReviewContent : public BaseContent
{
public:

    /**
     * This method is the default constructor.
     */
    ReviewContent();

    /**
     * This method is the copy constructor.
     *
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    ReviewContent(const ReviewContent& rRhs);

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~ReviewContent();

    /**
     * This is the assignment operator.
     *
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     *
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    ReviewContent& operator=(const ReviewContent& rRhs);

    /**
     * This method retrieves the review date as a string.
     * 
     * @return A string containing the date of the review. 
     */
    String GetDateTime() const;

    /**
     * This method retrieves the review title.
     * 
     * @return A string containing the review title.
     */
    String GetTitle() const;

    /**
     * This method retrieves the review rating.
     * 
     * @return A double containing the retrieved value of rating.
     */
    double GetRating() const;

    /**
     * This method retrieves the review description (text).
     * 
     * @return A string containing the review
     *        description (text).
     */
    String GetDescription() const;

    /**
     * This method retrieves a link to the website of the user, who submitted
     * the review. 
     * 
     * @return An object representing a link to the website of the user, who submitted
     * the review. 
     */
    LinkObject GetUser() const;

    /**
     * This method retrieves the BCP 47 identifier of the language used in the
     * review.
     * 
     * @return A string containing the identifier of the language used in the
     *        review.
     */
    String GetLanguage() const;

    /**
     * This method sets the review date as a string.
     * 
     * @param rDateTime A constant reference to a string containing the date of
     *        the review.
     */
    void SetDateTime(const String &rDateTime);

    /**
     * This method sets the review title.
     * 
     * @param rTitle A constant reference to a string containing the review
     *        title.
     */
    void SetTitle(const String& rTitle);

    /**
     * This method sets the review rating.
     * 
     * @param dRating A double containing the retrieved value of rating.
     */
    void SetRating(double dRating);

    /**
     * This method sets the review description (text).
     * 
     * @param sText A constant reference to a string containing the review
     *        description (text).
     */
    void SetDescription(const String& sText);

    /**
     * This method sets a link to the website of the user, who submitted
     * the review. 
     * 
     * @param cUser A constant reference to an object representing a link to the
     *        website of the user, who submitted the review.
     */
    void SetUser(const LinkObject& cUser);

    /**
     * This method sets the BCP 47 identifier of the language used in the
     * review.
     * 
     * @param sLanguage A constant reference to a string containing the
     *        identifier of the language used in the review.
     */
    void SetLanguage(const String& sLanguage);

private:
    class ReviewContentImpl;
    ReviewContentImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // REVIEW_CONTENT_H_
