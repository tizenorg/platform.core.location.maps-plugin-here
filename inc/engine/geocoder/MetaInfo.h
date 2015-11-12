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

#ifndef METAINFO_H
#define METAINFO_H

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates meta information included in the search responses.  
 * 
 * \ingroup geocoding
 */
class MetaInfo
{
public:
    /**
     * This method is the default constructor.
     */
    MetaInfo();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs A constant reference to an object whose contents are to be
     *        copied to the newly created instance of the class.
     */
    MetaInfo(const MetaInfo& rRhs);

    /**
     * This method is the destructor.
     */
    ~MetaInfo();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs A constant reference to an instance of
     *        <code>MetaInfo</code> whose contents are to be copied into
     *        the given instance.
     */
    MetaInfo& operator=(const MetaInfo& rRhs);

    /**
     * This methos sets a key that can be used in subsequent requests to
     * access the next n results.
     * 
     * @param n A key that can be used in subsequent requests to
     *        access the next n results.
     */
    void SetNextPageInformation(size_t n);

    /**
     * This method retrieves a key that can be used in subsequent requests to
     * access the next n results.
     * 
     * @return A key that can be used in subsequent requests to
     *        access the next n results.
     */
    bool GetNextPageInformation(size_t& rDst) const;

    /**
     * This method sets a key that can be used in subsequent requests to
     * access the previous n results.
     * 
     * @param n A key that can be used in subsequent requests to
     *        access the previous n results.
     */
    void SetPreviousPageInformation(size_t n);

    /**
     * This method retrieves a key that can be used in subsequent requests to
     * access the previous n results.
     * 
     * @return A key that can be used in subsequent requests to
     *        access the previous n results.
     */
    bool GetPreviousPageInformation(size_t& rDst) const;

    /**
     * This method sets the timestamp indicating when the search was run.
     * 
     * @param sTimestamp A constant reference to a string containing the
     *        timestamp indicating when the search was run.
     */
    void SetTimestamp(const String& sTimestamp);

    /**
     * This method retrieves the timestamp indicating when the search was run.
     * 
     * @param rDst A reference to a string to which the
     *        timestamp indicating when the search was run is to be copied.
     * 
     * @return <code>true</code> if the timestamp has been retrieved
     *        successfully, <code>false</code> if the time stamp cannot be
     *        retrieved.
     */
    bool GetTimestamp(String& rDst) const;

private:
    class MetaInfoImpl;
    MetaInfoImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
