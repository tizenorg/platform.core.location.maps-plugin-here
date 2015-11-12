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

#ifndef PARSERERROR_H
#define PARSERERROR_H

#include "HereMaps_global.h"

#include "common/ErrorBase.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates an XML parser error. It allows you to set and
 * retrieve the error message, error type and other details concerning an error
 * condition. 
 */
class EXPORT_API ParserError : public ErrorBase
{
public:
    /** 
     * This enumeration defines identifiers for the recognized error types.
     */
    enum Type
    {
        PE_InvalidXmlDocument,      ///< Indicates that the XML document is invalid.
        PE_Utf8ConversionFailed,    ///< Indicates that UTF8 conversion failed.
        PE_ExtractXMLTextNodeFail,  ///< Indicates that it an attempt to extract an XML node failed.
        PE_MissingAttribute,        ///< Indicates that an attribute is missing.
        PE_InternalParserError      ///< Indicates that an internal parser error occurred.
    };

    /**
     * This method is a constructor.
     * 
     * @param aType A value indicating the error type.
     */
    ParserError(Type aType);

    /**
     * This method is a constructor.
     * 
     * @param aType A value indicating the error type.
     * 
     * @param sParentNodename A constant reference to the parent node (XML).
     */
    ParserError(Type aType, const String& sParentNodename);

    /**
     * This method is a constructor.
     * 
     * @param aType A value indicating the error type.
     * 
     * @param sParentNodename A constant reference to a string containing the
     *        name of the parent node (XML).
     * 
     * @param sDescription A constant reference to a string containing the error description. 
     */
    ParserError(Type aType, const String& sParentNodename, const String& sDescription);

    /**
     * This method is the destructor.
     */
    virtual ~ParserError();

    /**
     * This method converts the given instance to a string. The default
     * implementation outputs a string containing the error type, description,
     * parser input and the name of the parent element.
     * 
     * @return A string representation of the given instance of the class.
     */
    virtual String ToString() const;

    /**
     * This method retrieves a value indicating the error type.
     * 
     * @return A value indicating the error type. 
     */
    Type getParserErrorType() const;

    /**
     * This method sets the parser input.
     * 
     * @param sInput A constant reference to a string containing parser input.
     */
    void setParserInput(const String& sInput);

    /**
     * This method retrieves the parser input.
     * 
     * @return A constant reference to a string containing parser input.
     */
    const String& getParserInput() const;

    /**
     * This method sets the name of the parent node.
     * 
     * @param sNodename A constant reference to a string containing name of the
     *        parent (XML) node.
     */
    void setParentElement(const String& sNodename);

    /**
     * This method retrieves the name of the parent node.
     * 
     * @return A constant reference to a string containing name of the
     *        parent (XML) node.
     */
    const String& getParentElement() const;

    /**
     * This method sets the error description.
     * 
     * @param sDsc A constant reference to a string containing the
     *        description of the error.
     */
    void setDescription(const String& sDsc);

    /**
     * This method retrieves the error description.
     * 
     * @return A constant reference to a string containing the
     *        description of the error.
     */
    const String& getDescription() const;

private:
    class ParserErrorImpl;
    ParserErrorImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
