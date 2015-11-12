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

#ifndef TILEFETCHERERROR_H
#define TILEFETCHERERROR_H

#include "common/HereMaps_global.h"
#include "common/ErrorBase.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates information related to an error condition that may
 * arise when requesting map tiles from the server.
 * 
 * \ingroup tilefetcher
 */
class EXPORT_API TileFetcherError : public ErrorBase
{
public:

    /**
     * This enumeration defines identifiers for error conditions related to the
     * tile fetcher.
     */
    enum ErrorEntity
    {
        TFE_COULD_NOT_DECODE_SRC_IMAGE, ///< Indicates that the source image
                                        ///  could not be decoded.
        TFE_COULD_NOT_RETRIEVE_HASH     ///< Indicates that the hash could not
                                        ///  be retrieved.
    };

    /**
     * This method is a constructor.
     * 
     * @param aItem A value rerpresenting an error condition; a value with which
     *       to initialize the given instance of the class.
     */
    TileFetcherError(ErrorEntity aItem);

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~TileFetcherError();

    /**
     * This method produces a string representation of the given instance of
     * the class. The method must be implemented by derived classes.
     *
     * @return A string containing a text representation of the given instance
     *        of the class.
     */
    virtual String ToString() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(TileFetcherError);

    class TileFetcherErrorImpl;
    TileFetcherErrorImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
