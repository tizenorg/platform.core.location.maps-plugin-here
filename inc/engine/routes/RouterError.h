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

#ifndef ROUTERERROR_H
#define ROUTERERROR_H

#include "common/HereMaps_global.h"
#include "common/ErrorBase.h"

HERE_MAPS_BEGIN_NAMESPACE


/**
 * This class encapsulates an error condition that may arise when processing a
 * routing request.
 *
 * \ingroup routes
 */
class EXPORT_API RouterError : public ErrorBase
{
public:

    /**
     * This enumeration defines identifiers for the recognized error types.
     */
    enum ErrorCode
    {
        EC_ParseError,             ///< Indicates a parsing error.
        EC_UnsupportedOptionError, ///< Indicates that an attempt to use an
                                   ///  unsupported option was detected. 
        EC_UnknownError            ///< Indicates an unknown error.
    };

    /**
     * This method is a constructor that initializes a new instance of the class
     * using the error code value supplied by the caller.
     * 
     * @param aErrorCode A value indicating the error type to use when
     *        initializing the new instance of the class.
     */
    RouterError(ErrorCode aErrorCode);

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~RouterError();

    /**
     * This method retrieves the error code.
     * 
     * @return A value indicating the error type. 
     */
    ErrorCode GetErrorCode() const;

    /**
     * This method obtains a string representation of the given instance.
     * The method must be implemented by derived classes.
     * 
     * @return A string containing the text representation of the given instance
     *        of the class.
     */
    virtual String ToString() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(RouterError);

    class RouterErrorImpl;
    RouterErrorImpl* m_pImpl;

};

HERE_MAPS_END_NAMESPACE

#endif
