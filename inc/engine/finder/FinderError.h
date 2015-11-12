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

#ifndef FINDER_ERROR_H_
#define FINDER_ERROR_H_

#include "common/HereMaps_global.h"

#include "common/ErrorBase.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates error information reflecting an error that
 * may arise when a parsing a finder request.
 * 
 * \ingroup finder
 */
class EXPORT_API FinderError : public ErrorBase
{
public:

    /**
     * This enumeration defines identifiers for the recognized error types.
     */
    enum ErrorType
    {
        ET_InvalidQueryArguments, ///< Indicates invalid query argument.
        ET_ParserError,           ///< Indicates that an internal parser error occurred.
        ET_InvalidCredentials,    ///< Indicates that credentials are not correct or empty
        ET_UnknownError           ///< Indicate an unkown error
    };

    /**
     * This method is a constructor.
     *
     * @param sStr A constant reference to a string containing an error message.
     */
    FinderError(ErrorType etype);

    /**
     * This method is a constructor.
     *
     * @param aType A value indicating the error type.
     *
     * @param sDescription A constant reference to a string containing the error
     *        description.
     */
    FinderError(ErrorType eType, const String& sDescription);

    /**
     * This method is a (virtual) destructor. 
     */
    virtual ~FinderError();

    /**
     * This method retrieves a string representation of the given instance of
     * the class. 
     * 
     * @return A string containing the error information held in the given
     *        instance of the class. 
     */
    virtual String ToString() const;

    /**
     * This method sets the error description.
     *
     * @param sDsc A constant reference to a string containing the
     *        description of the error.
     */
    void SetDescription(const String& sDsc);

    /**
     * This method retrieves the error description.
     *
     * @return A constant reference to a string containing the
     *        description of the error.
     */
    String GetDescription() const;

    /**
     * This method retrieves the error type.
     *
     * @return A value indicating the error type.
     */
    ErrorType GetErrorType() const;

    /**
     * This method sets the error type.
     *
     * @param aType An error type.
     */
    void SetErrorType(ErrorType aType);

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(FinderError);

    class FinderErrorImpl;
    FinderErrorImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif // FINDER_ERROR_H_
