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

#ifndef EDITORIAL_CONTENT_H_
#define EDITORIAL_CONTENT_H_

#include <vector>

#include "common/HereMaps_global.h"
#include "finder/BaseContent.h"

HERE_MAPS_BEGIN_NAMESPACE

class EditorialContent;

/**
 * This typedef defines a list of editorial content items as a type. 
 */
typedef std::vector<EditorialContent> EditorialContentList;

/**
 * This class encapsulates editorial content relating to a place.
 * 
 * \ingroup finder
 */
class EXPORT_API EditorialContent : public BaseContent
{
public:

    /**
     * This is the default constructor. 
     */
    EditorialContent();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    EditorialContent(const EditorialContent& rRhs);

    /**
     * This method is a (virtual) destructor.
     */
    virtual ~EditorialContent();

    /**
     * This is the assignment operator.
     *
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     *
     * @return A reference to the given instance of the class after its contents
     *        have been updated.
     */
    EditorialContent& operator=(const EditorialContent& rRhs);

    /**
     * This method retrieves the description (the contents of an editorial
     * item). 
     * 
     * @return A string containing the description.
     */
    String GetDescription() const;

    /**
     * This method retrieves the identifier of the language of the editorial
     * item. The identifier is a string containing a BCP 47 language code (see
     * also http://tools.ietf.org/html/rfc5646).
     * 
     * @return A string containing the language identifier.
     */
    String GetLanguage() const;

    /**
     * This method sets the description (the contents of an editorial
     * item). 
     * 
     * @param sText A constant reference to a string containing the description.
     */
    void SetDescription(const String& sText);

    /**
     * This method retrieves the identifier of the language of the editorial
     * item. The identifier is a string containing a BCP 47 language code (see
     * also http://tools.ietf.org/html/rfc5646).
     * 
     * @param rLanguage A constant reference to a string containing the language
     *       identifier.
     */
    void SetLanguage(const String& rLanguage);

private:
    class EditorialContentImpl;
    EditorialContentImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // EDITORIAL_CONTENT_H_
