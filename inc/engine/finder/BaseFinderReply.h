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

#ifndef BASEFINDERREPLY_H
#define BASEFINDERREPLY_H

#include "common/BaseReply.h"

HERE_MAPS_BEGIN_NAMESPACE

/** 
 * This class encapsulates a basic reply to a places search query. 
 */
class BaseFinderReply : public BaseReply
{
public:
    /**
     * This enumeration defines identifiers for supported reply types.
     */
    enum ReplyType
    {
        RT_Discovery = 0, // Indicates a reply to a discovery query.
        RT_PlaceDetails   // Indicates a reply to a request for place details.
    };
    /**
     * This method is the constructor.
     */
    BaseFinderReply(ReplyType aReplyType);

    /**
     * This method is a virtual destructor.
     */
    virtual ~BaseFinderReply();

    /**
     * This method retrieves the reply type.
     * 
     * @return A value that ientifies the reply type.
     */
    ReplyType GetFinderReplyType() const;

private:

    ReplyType m_aReplyType;

};

HERE_MAPS_END_NAMESPACE

#endif // BASEFINDERREPLY_H
