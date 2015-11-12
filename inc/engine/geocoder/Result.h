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

#ifndef RESULT_H
#define RESULT_H

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoLocation;

/**
 * This class encapsulates a result item returned by the server in response to a
 * geocoding or reverse geocoding request.
 * 
 * \ingroup geocoding
 */
class EXPORT_API Result
{
public:
    /**
     * This enumeration defines identifiers for match levels -- they reflect how
     * closely (to what level of detail) the result matches the request.
     */ 
    enum MatchLevel
    {
        ML_Unknown = -1,  ///< Indicates that the match level is unknown.
        ML_Country = 0,   ///< Indicates country match.
        ML_State,         ///< Indicates state match.
        ML_County,        ///< Indicates county match.
        ML_City,          ///< Indicates city match.
        ML_District,      ///< Indicates district match.
        ML_Street,        ///< Indicates street match.
        ML_Intersection,  ///< Indicates intersection match. 
        ML_HouseNumber,   ///< Indicates house-number match.  
        ML_PostalCode,    ///< Indicates postal code match.  
        ML_Suite,         ///< Indicates suite match.  
        ML_Floor          ///< Indicates floor match.  
    };

    /** 
     * This method is the default constructor.
     */
    Result();

    /** 
     * This method is the destructor.
     */
    ~Result();

    /**
     * This method sets location details for the given result.
     * 
     * @param rLocation A constant reference to an object containing the
     *        location details.
     */
    void SetLocation(const GeoLocation& rLocation);

    /**
     * This method retrieves the location details from the given result object.
     * 
     * @param rLocation A constant reference to an object containing the
     *        location details.
     */
    const GeoLocation& GetLocation() const;

    /**
     * This method sets the relevance value on the given result.
     * 
     * @param A float indicating the relevance of the given result in the range
     *        [0..1], where 1 indicates maximum relevance.
     */
    void SetRelevance(float fValue);

    /**
     * This method retrieves a value indicating the relevance of the given result.
     * 
     * @param A float indicating the relevance of the given result; the value is
     *        in the range [0..1], where 1 indicates maximum relevance.
     */
    float GetRelevance() const;

#ifdef TIZEN_CUSTOMIZATION
    /**
     * This method sets a value representing the distance for the given result.
     * 
     * @param fValue A value indicating distance.
     */
    void SetDistance(float fValue);

    /**
     * This method retrieves a value representing the distance for the given
     * result. 
     * 
     * @return A value indicating distance.
     */
    float GetDistance() const;
#endif

    /**
     * This method sets a value representing the match level for the given
     * result. 
     * 
     * @param aLevel A value indicating match level (see also
     *        <code>Result::MatchLevel</code>).
     */
   void SetMatchLevel(MatchLevel aLevel);

    /**
     * This method sets a value representing the match level for the given
     * result. 
     * 
     * @param sLevel A constant reference to a string indicating the match level
     *        to set (see also <code>Result::MatchLevel</code>). The value of
     *        the string must be one of "country", "state", "county", "city",
     *        "street", "intersection", "housenumber", "postalcode", "suite",
     *        "floor", "district".
     */
    void SetMatchLevel(const String& sLevel);

    /**
     * This method retrieves a value representing the match level for the given
     * result. 
     * 
     * @return A value indicating match level (see also
     *        <code>Result::MatchLevel</code>).
     */
    MatchLevel GetMatchLevel() const;

    /**
     * This method adds a match level indicator and sets the associated match
     * quality value.  
     * 
     * @param aMatchLevel A value indicating the match level to set (see also 
     *        <code>Result::MatchLevel</code>).   
     * 
     * @param fQuality A float value indicating the match quality.
     */
    void AddMatchQuality(MatchLevel aMatchLevel, float fQuality);

    /**
     * This method adds a match level indicator and sets the associated match
     * qualityf value.  
     * 
     * @param sLevel A constant reference to a string indicating the match level
     *        to set (see also <code>Result::MatchLevel</code>). The value of
     *        the string must be one of "country", "state", "county", "city",
     *        "street", "intersection", "housenumber", "postalcode", "suite",
     *        "floor", "district".
     * 
     * @param fQuality A float value indicating the match quality.
     */
    void AddMatchQuality(const String& sLevel, float fQuality);

    /**
     * This method retrieves a value representing match quality of the given
     * result for the match level specified by the caller. 
     * 
     * @param aMatchLevel A value indicating the match level to set (see also 
     *        <code>Result::MatchLevel</code>).   
     * 
     * @return A float value indicating the match quality.
    */
    float GetMatchQuality(MatchLevel aMatchLevel) const;

    /**
     * This method retrieves the number of match quality values available for
     * the given result. 
     * 
     * @return A value indicating the number of match quality values.  
     */
    unsigned int GetNumMatchQualities() const;

    /**
     * This method retrieves a value identifying the match level at the index
     * specified by the caller.
     * 
     * @param uIdx A value representing the index from which to retrieve the
     *        match level indicator (value). Note that the index must not be
     *        greater than the return value from
     *        <code>Result::GetNumMatchQualities()</code>. 
     * 
     * @return  A value indicating the match level at the index specified by the
     *        caller (see also <code>Result::MatchLevel</code>).   
     */
    MatchLevel GetMatchQualityLevel(unsigned int uIdx) const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(Result);

    class ResultImpl;
    ResultImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
