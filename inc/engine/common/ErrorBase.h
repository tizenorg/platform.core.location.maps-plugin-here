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

#ifndef ERRORBASE_H
#define ERRORBASE_H

#include "common/HereMaps_global.h"

#include <iostream>

HERE_MAPS_BEGIN_NAMESPACE

class BaseReply;
class GeoCoderReplyParser;

/**
 * This class is the base class for classes that encapsulate error conditions,
 * for example <code>CommunicationError</code>.
 */
class EXPORT_API ErrorBase
{
public:
    /**
     * This enumeration defines identifiers for error categories.
     */
    enum ErrorCategory
    {
        EC_None = 0,            ///< Indicates success.
        EC_CommunicationsError, ///< Indicates a communications error.
        EC_ParserError,         ///< Indicates a parser error.
        EC_RouterError,         ///< Indicates a router error.
        EC_TileMapError,        ///< Indicates a tile map error.
        EC_FinderError          ///< Indicates a finder/places error.
    };

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~ErrorBase();

    /**
     * This method produces a string representation of the given instance of
     * the class. The method must be implemented by derived classes. 
     * 
     * @return A string containing a text representation of the given instance
     *        of the class.  
     */
    virtual String ToString() const = 0;

    /**
     * This method prints the text representation of the given instance of the
     * class to the stream identified by the caller. 
     * 
     * \sa ToString
     * 
     * @param rSink A reference to the steam to which to output the (text
     *        representeation) of the given instance.
     */
    void Print(std::ostream& rSink) const;

    /**
     * This method retrieves a value representing the error category assigned to
     * the given instance of the class.
     * 
     * @return A value representing the error category assigned to
     *        the given instance of the class.
     */
    ErrorCategory GetErrorCategory() const;

protected:
    /**
     * This method is the default constructor.
     */
    ErrorBase();

    /**
     * This method sets the error category for the given instance of the class.
     * 
     * @param aErrorCategory A value representing the error category to be
     *        assigned to the given instance of the class.
     */
    void SetErrorCategory(ErrorCategory aErrorCategory);

private:
   // HERE_MAPS_NO_COPY_NO_ASSIGN(ErrorBase);

    friend class BaseReply;
    friend class GeoCoderReplyParser;
    friend class GeoRouterReplyParser;
    friend class JsonParser;
    friend class TestErrorBase;


    /*
     * \brief note ownership of parameter is transferred
     * \param rError error that is appended to linked list of error - must be allocated on heap
     */
    void Append(ErrorBase& rError);

    class ErrorBaseImpl;
    ErrorBaseImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
