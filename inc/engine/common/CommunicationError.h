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

#ifndef COMMUNICATIONERROR_H
#define COMMUNICATIONERROR_H

#include "common/HereMaps_global.h"
#include "common/ErrorBase.h"

#ifndef TIZEN_MIGRATION
#include <FNet.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates information about an error condition that may arise
 * in network communications between the client and the server.
 */
class EXPORT_API CommunicationError : public ErrorBase
{
public:
    /** 
     * This enumeration defines error code identifiers. 
     */
    enum ErrorCode
    {
        CE_HttpError,       ///< Indicates an HTTP error.
        CE_NetworkError,    ///< Indicates a network error.
        CE_RestEngineError, ///< Indicates a REST engine error.
        CE_MaxRequests      ///< Indicates that the maximum number of requests
                            ///  has been reached.
    };

    /**
     * This typedef defines a HTTP status code as a type.
     */
#ifdef TIZEN_MIGRATION
    typedef long HttpStatusCode;
#else
    typedef Tizen::Net::Http::NetHttpStatusCode HttpStatusCode;
#endif

    /**
     * This method is a constructor.
     * 
     * @param aErrorCode A value representing an error code.
     */
    CommunicationError(ErrorCode aErrorCode);

    /**
     * This method is a constructor.
     * 
     * @param aHttpStatusCode A value representing an HTTP status code as
     *        defined on http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html.
     */
    CommunicationError(HttpStatusCode aHttpStatusCode);

    /**
     * This method is a (virtual) destructor.
     *
     */
    virtual ~CommunicationError();

    /**
     * This method retrieves an error code.
     * 
     * @return A value representing an error code.
     */
    ErrorCode GetErrorCode() const;

    /**
     * This method retrieves a string representation of the given instance of
     * <code>CommunicationError</code>.
     *
     * @return A string representation of the given instance of
     * <code>CommunicationError</code>.
     */
    virtual String ToString() const;

    /**
     * This method sets an HTTP status code.
     *
     * @param aHttpStatusCode A value representing an HTTP status code as
     *        defined on http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html.
     */
    void SetHttpStatusCode(HttpStatusCode aHttpStatusCode);

#ifdef TIZEN_MIGRATION
    /**
     * This method retrieves the HTTP status code associated with the given
     * instance of the class. 
     *
     * @return aHttpStatusCode A value representing an HTTP status code as
     *        defined on http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html.
     */
    const HttpStatusCode GetHttpStatusCode();
#endif

    /**
     * This method associates a text string describing an error with the given
     * instance of the class. 
     * 
     * @param sDesc A constant reference to a string containing the error
     *        description.
     */
    void SetErrorDescription(const String& sDesc);

    /**
     * This method retrieves the error description associated with the given
     * instance of the class. 
     * 
     * @return A constant reference to a string containing the error
     *        description.
     */
    const String& GetErrorDescription() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(CommunicationError);

    class CommunicationErrorImpl;
    CommunicationErrorImpl* m_pImpl;

};

HERE_MAPS_END_NAMESPACE

#endif
