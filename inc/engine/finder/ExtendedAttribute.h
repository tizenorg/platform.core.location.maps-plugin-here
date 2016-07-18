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

#ifndef EXTENDED_ATTRIBUTE_H_
#define EXTENDED_ATTRIBUTE_H_

#include "common/HereMaps_global.h"
#include <vector>

HERE_MAPS_BEGIN_NAMESPACE

class ExtendedAttribute;
/**
 * This typedef defines a list of extended attributes as a type.
 */
typedef std::vector< ExtendedAttribute > ExtendedAttributeList;

/**
 * This class encapsulates an extended attribute relating to a place. 
 *
 * Extended attributes can be used to provide additional information about a
 * place. They contain a localized label and a text field that can be displayed
 * without modification.
 * 
 * \ingroup finder
 */
class EXPORT_API ExtendedAttribute
{
public:
    /**
     * This method is the default constructor.
     */
    ExtendedAttribute();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    ExtendedAttribute(const ExtendedAttribute& rRhs);

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~ExtendedAttribute();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     * 
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    ExtendedAttribute& operator=(const ExtendedAttribute& rRhs);

    /**
     * This method retrieves a string that indicates the type of the extended
     * attribute. 
     * 
     * @return A string containing the attribute type identifier.
     */
    String GetAttributeType() const;

    /**
     * This method retrieves the extended attribute label, which is a localized
     * string identifying the attribute.
     * 
     * @return A string containing the extended attribute label.
     */
    String GetLabel() const;

    /**
     * This method retrieves the extended attribute text, which can be displayed
     * without modification.
     * 
     * @return A string containing the extended attribute text.
     */
    String GetText() const;

    /**
     * This method sets the type of the extended attribute.
     * 
     * @rsType A constant reference to a string containing the attribute type
     *        identifier.
     */
    void SetAttributeType(const String& rsType);

    /**
     * This method sets the extended attribute label, which is a localized
     * string identifying the attribute.
     * 
     * @param rsLabel A constant reference to a string containing the extended
     *        attribute label.
     */
    void SetLabel(const String& rsLabel);

    /**
     * This method sets the extended attribute text, which can be displayed
     * without modification.
     * 
     * @param rsText A constant reference to a string containing the extended
     *        attribute text.
     */
    void SetText(const String& rsText);

private:
    class ExtendedAttributeImpl;
    ExtendedAttributeImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // EXTENDED_ATTRIBUTE_H_
