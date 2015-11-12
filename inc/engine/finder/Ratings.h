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

#ifndef RATINGS_H_
#define RATINGS_H_

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates place ratings contributed by users. 
 * 
 * \ingroup finder
 */
class EXPORT_API Ratings
{
public:

    /**
     * This method is the default constructor.
     */
    Ratings();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    Ratings(const Ratings& rRhs);

    /**
     * This method is the destructor.
     */
    ~Ratings();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     * 
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    Ratings& operator=(const Ratings& rRhs);

    /**
     * This method retrieves the average rating for a place.
     * 
     * @return A value reflecting the average user rating for a place. 
     */
    double GetAverage() const;

    /**
     * This method retrieves a value indicating how many users have rated a place.
     * 
     * @return A value indicating how many users have rated a place.
     */
    size_t GetCount() const;

    /**
     * This method sets the average rating for a place.
     * 
     * @param aAverage A value reflecting the average user rating for a place.
     */
    void SetAverage(double aAverage);

    /**
     * This method sets a value indicating how many users have rated a place.
     * 
     * @param aCount A value indicating how many users have rated a place.
     */
    void SetCount(size_t aCount);

private:
    class RatingsImpl;
    RatingsImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // RATINGS_H_
