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

#ifndef MULTIREVERSEREPLY_H_
#define MULTIREVERSEREPLY_H_

#include "common/HereMaps_global.h"
#include "common/BaseReply.h"

#include "geocoder/Result.h"
#include "geocoder/MetaInfo.h"

TIZEN_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates a reply to a geocoding query.
 *
 * The class receives the response data returned by the server in reply to a
 * query asynchronously. Notification that the data is available comes via a
 * listener object registered on the class by calling <code>AddListener()</code>.
 *
 * @ingroup geocoding
 */
class EXPORT_API MultiReverseReply : public Here::Maps::BaseReply
{
public:

    /**
     * This is the default constructor.
     */
    MultiReverseReply();

    /**
     * This is a destructor.
     */
    virtual ~MultiReverseReply();

    /**
     * This method retrieves a value indicating the number of results in the
     * reply to the query.
     *
     * @return An integer value indicating the number of results.
     */
    size_t GetNumResults() const;

    /**
     * This method retrieves a result at the index specified by the caller.
     *
     * @param A value indicating the index of the result to retrieve.
     *
     * @return A constant pointer to an instance of <code>Result</code>.
     */
    const Here::Maps::Result* GetResult(size_t idx) const;

    /**
     * This method retrieves the reply meta information.
     *
     * @return A constant pointer to an instance of <code>MetaInfo</code>.
     */
    const Here::Maps::MetaInfo* GetMetaInfo() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(MultiReverseReply);
    friend class TestGeoCoderParser;

    virtual bool OnDataReceived(const unsigned char* pBuffer, size_t uSize);

    class MultiReverseReplyImpl;
    MultiReverseReplyImpl* m_pImpl;
};

TIZEN_MAPS_END_NAMESPACE

#endif /* MULTIREVERSEREPLY_H_ */
