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

#ifndef TILEFETCHERMETAREPLY_H
#define TILEFETCHERMETAREPLY_H

#include "common/HereMaps_global.h"
#include "common/BaseReply.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates a reply to a map tile metadata request.
 * 
 * 
 * \ingroup tilefetcher
 */
class TileFetcherMetaReply : public BaseReply
{
public:
    /** 
     * This method is a constructor that initialize the class instance.
     */
    TileFetcherMetaReply();

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~TileFetcherMetaReply();

    /**
     * This method retrieves the hash key which should be used for map tile
     * requests.
     * 
     * @return  A string representing the hash key.
     */
    String GetHash() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(TileFetcherMetaReply);

    virtual bool OnDataReceived(const unsigned char* pBuffer, size_t uSize);

    class TileFetcherMetaReplyImpl;
    TileFetcherMetaReplyImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
