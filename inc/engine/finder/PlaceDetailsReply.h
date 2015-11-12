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

#ifndef PLACE_DETAILS_REPLY_H_
#define PLACE_DETAILS_REPLY_H_

#include "common/HereMaps_global.h"
#include "finder/BaseFinderReply.h"

HERE_MAPS_BEGIN_NAMESPACE

class PlaceDetails;

/**
 * This class encapsulates a response to a request for place details
 * (<code>PlaceDetailsQuery</code>). 
 * 
 * \ingroup finder
 */
class EXPORT_API PlaceDetailsReply : public BaseFinderReply
{
public:

    /**
     * This is the default constructor. 
     */
    PlaceDetailsReply();

    /**
     * This is the destructor. 
     */
    ~PlaceDetailsReply();

    /**
     * This method retrieves the details of the place that have been returned by
     * the server.
     * 
     * @return An object containing the place details.
     */
    PlaceDetails GetPlaceDetails() const;

private:
    void SetPlaceDetails(const PlaceDetails& rPlace);
    bool OnDataReceived(const unsigned char* pBuffer, size_t uSize);

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(PlaceDetailsReply);
    friend class TestPlaceDetailsReply;

    class PlaceDetailsReplyImpl;
    PlaceDetailsReplyImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif // PLACE_DETAILS_REPLY_H_
