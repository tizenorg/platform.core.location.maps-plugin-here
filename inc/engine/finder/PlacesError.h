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

#ifndef PLACES_ERROR_H_
#define PLACES_ERROR_H_

#include "common/HereMaps_global.h"
#include "common/ErrorBase.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates an error condition that may arise when submitting
 * places-related queries and retrieving results.
 * 
 * \ingroup finder
 */
class PlacesError : public ErrorBase
{
public:
    /** 
     * This enumeration defines identifiers for both success and error
     * conditions. 
     */ 
    enum ErrorCode
    {
        EC_NoError,                   ///< Indicates success.
        EC_PlaceDoesNotExistError,    ///< Indicates that the play does not exist.
        EC_CategoryDoesNotExistError, ///< Indicates that the category does not exist.
        EC_ParseError,                ///< Indicates a parsing error.
        EC_PermissionsError,          ///< Indicates that the required
                                      ///  permissions are not in place.
        EC_UnsupportedError,          ///< Indicates that a query/operation is
                                      ///  not supported.
        EC_BadArgumentError,          ///< Indicates that an argument supplied
                                      ///  by the caller is bad or not recognized.
        EC_CancelError,               ///< Indicates that an error occurred when
                                      ///  attempting to cancel a request. 
        EC_UnknownError               ///< Indicates an unspecified/unknown error.
    };

    /** 
     * This is a constructor for the class.
     *
     * @param aErrorCode A value representing the error code with which to
     *       initialize a new instance of the class.
     */
    PlacesError(ErrorCode aErrorCode);

    /** 
     * This method is the (virtual) destructor for the class.
     */
    virtual ~PlacesError();

    /**
     * This method retrieves a value representing the error code assigned to
     * the given instance of the class.
     * 
     * @return A value representing the error code assigned to
     *        the given instance of the class.
     */
    ErrorCode GetErrorCode() const;

    /**
     * This method retrieves a string representation of the given instance of
     * the class.
     * 
     * @return A String representation of
     *        the given instance of the class. The possible values are 
     *        "No Error", "Place Doesn't exist", "Category doesn't exist",
     *        "Parse error", "Permissions error", "Unsupported error",
     *        "Bad argument", "Cancel error", "Unknown error",
     *        or "No defined error".
     */
    virtual String ToString() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(PlacesError);

    class PlacesErrorImpl;
    PlacesErrorImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif // PLACES_ERROR_H_
