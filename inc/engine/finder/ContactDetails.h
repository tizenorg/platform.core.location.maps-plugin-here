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

#ifndef CONTACT_DETAILS_H_
#define CONTACT_DETAILS_H_

#include <vector>

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

class EXPORT_API ContactDetails;
/**
 * This typedef defines a type representing a list of <code>ContactDetails</code>
 * instances.
 */
typedef std::vector<ContactDetails> ContactDetailsList;

/**
 * This class encapsulates contact information relating to a place.
 *
 * \ingroup finder
 */
class ContactDetails
{
public:
    /**
     * This method is the default constructor.
     */
    ContactDetails();

   /**
    * This method is the copy constructor.
    *
    * @param rRhs An object whose contents are to be copied to the instance
    *        being created.
    */
    ContactDetails(const ContactDetails& rRhs);

   /**
    * This method is the destructor.
    */
     ~ContactDetails();

   /**
    * This is the assignment operator.
    *
    * @param rRhs An object whose contents are to be copied to the given
    *        instance.
    *
    * @return A reference to the given instance of the class after its contents
    *       have been updated.
    */
    ContactDetails& operator=(const ContactDetails& rRhs);

    /**
     * This method retrieves the contact type, which can be telephone, e-mail,
     * website, site, etc.
     *
     * @return A string containing the contact type identifier. The possible
     *       values are "phone", "website", "fax", or "email".
     */
    String GetContactType() const;

    /**
     * This method retrieves the contact detail label, which is a localized
     * string identifying the purpose of the contact, for example "Phone",
     * "Mobile". Note that label is accompanied by a "value" filed, which for
     * example for a "Phone" contains the telephone number.
     *
     * @return A string containing the contact label.
     */
    String GetLabel() const;

    /**
     * This method retrieves the value for the associated contact label.
     *
     * @return A string containing the value corresponding to the contact label.
     */
    String GetValue() const;

    /**
     * This method sets the contact type, which can be telephone, e-mail,
     * website, site, etc.
     *
     * @param rsName A string containing the contact type identifier.  The
     *       possible values are "phone", "website", "fax", or "email".
     */
    void SetContactType(const String& rsName);

    /**
     * This method sets the contact detail label, which is a localized
     * string identifying the purpose of the contact, for example "Phone",
     * "Mobile". Note that label is accompanied by a "value" filed, which for
     * example for a "Phone" contains the telephone number.
     *
     * @param rsLabel A string containing the contact label.
     */
    void SetLabel(const String& rsLabel);

    /**
     * This method sets the value for the contact label.
     *
     * @param rsValue A string containing the value corresponding to the contact
     *       label (for example, if the label is "Phone", the value is the
     *       telephone number).
     */
    void SetValue(const String& rsValue);

private:
    class ContactDetailsImpl;
    ContactDetailsImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // CONTACT_DETAILS_H_
