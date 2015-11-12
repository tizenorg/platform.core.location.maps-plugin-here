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

#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include "common/HereMaps_global.h"
#ifdef TIZEN_MIGRATION
#include "common/GeoCoordinates.h"
#include "common/GeoBoundingBox.h"
#include "common/GeoBoundingCircle.h"
#else
//#include "common/GeoCoordinates.h"
//#include "common/GeoBoundingBox.h"
#endif

#include <sstream>
#ifndef TIZEN_MIGRATION
#include <string>
#endif
#include <algorithm>
#ifndef TIZEN_MIGRATION
#include <iomanip>      // std::setprecision
#endif

HERE_MAPS_BEGIN_NAMESPACE

struct TSPredicate
{
   bool operator()(const String& key, const String& value)
   {
      return key.compare(value) < 0;
   }
};

class StringHelper
{
public:
    static void ToLower(std::string& sStr);

    template<class T>
    static T ToNumber(const std::wstring& sStd);

    template<class T>
    static T ToNumber(const std::string& sStd);

#ifndef TIZEN_MIGRATION
    template<class T>
    static T ToNumber(const Tizen::Base::String& sStd);
#endif

    template<class T>
    static void ToString(T aNumber, std::wstring& sDst);

    template<class T>
    static void ToString(T aNumber, std::string& sDst);

#ifndef TIZEN_MIGRATION
    template<class T>
    static void ToString(T aNumber, Tizen::Base::String& rDst);
#endif

#ifdef TIZEN_MIGRATION
    /**
     * This method retrieves a string representation of an object containing the
     * geographic coordinates of a location.
     *
     * @param rCoordinate A constant reference to an object containing
     *        geographic coordinates of a location; the object to be converted.
     *
     * @param sDst A reference to a string object to which the result of the
     *        conversion is to be copied.
     */
    static void ToString(const GeoCoordinates& rCoordinate, String& sDst);

    /**
     * This method converts a bounding box object to string.
     *
     * @param rBoundingBox A constant reference to the object whose string
     *        representation is to be obtained.
     *
     * @param sDst A reference to a string object to which the result of the
     *        conversion is to be copied.
     */
    static void ToString(const GeoBoundingBox& rBoundingBox, String& sDst);

    static void ToString(const GeoBoundingCircle& rBoundingCircle, String& sDst);
#endif
};

#ifdef TIZEN_MIGRATION
//-----------------------------------------------------------------------------
inline void StringHelper::ToString(const GeoCoordinates& rCoordinate, String& sDst)
{
    String sLatitude;
    ToString(rCoordinate.GetLatitude(), sLatitude);

    String sLongitude;
    ToString(rCoordinate.GetLongitude(), sLongitude);

    sDst = sLatitude + "," + sLongitude;
}

//-----------------------------------------------------------------------------
inline void StringHelper::ToString(const GeoBoundingBox& rBoundingBox, String& sDst)
{
    String sTopLeft;
    ToString(rBoundingBox.GetTopLeft(), sTopLeft);

    String sBottomRight;
    ToString(rBoundingBox.GetBottomRight(), sBottomRight);

    sDst = sTopLeft + ";" + sBottomRight;
}

//-----------------------------------------------------------------------------
inline void StringHelper::ToString(const GeoBoundingCircle& rBoundingCircle, String& sDst)
{
    String sCenter;
    ToString(rBoundingCircle.GetCenter(), sCenter);

    String sRadius;
    ToString(rBoundingCircle.GetRadius(), sRadius);

    sDst = sCenter + ";r=" + sRadius;
}
#else
/*
//-----------------------------------------------------------------------------
inline void StringHelper::ToString(const GeoBoundingBox& rBoundingBox, Tizen::Base::String& sDst)
{
    Tizen::Base::String sTopLeft;
    ToString(rBoundingBox.GetTopLeft(), sTopLeft);

    Tizen::Base::String sBottomRight;
    ToString(rBoundingBox.GetBottomRight(), sBottomRight);

    sDst = sTopLeft + ";" + sBottomRight;
}
*/
#endif

//-----------------------------------------------------------------------------
inline void StringHelper::ToLower(String& sStr)
{
    std::transform(sStr.begin(), sStr.end(), sStr.begin(), ::tolower);
}

//-----------------------------------------------------------------------------
template<class T>
inline T StringHelper::ToNumber(const std::wstring& sStr)
{
    T t;
    std::wstringstream aStream;
    aStream << sStr;
    aStream >> t;
    return t;
}

//-----------------------------------------------------------------------------
template<class T>
inline T StringHelper::ToNumber(const std::string& sStr)
{
    T t;
    std::stringstream aStream;
    aStream << sStr;
    aStream >> t;
    return t;
}


//-----------------------------------------------------------------------------
#ifndef TIZEN_MIGRATION
template<class T>
inline T StringHelper::ToNumber(const Tizen::Base::String& sStd)
{
    std::wstring sTmp = sStd.GetPointer();
    return ToNumber<T>(sTmp);
}
#endif

//-----------------------------------------------------------------------------
template<class T>
inline void StringHelper::ToString(T aNumber, std::wstring& sDst)
{
    std::wstringstream aStream;
    aStream << aNumber;
    sDst = aStream.str();
}

//-----------------------------------------------------------------------------
template<class T>
inline void StringHelper::ToString(T aNumber, std::string& sDst)
{
    std::stringstream aStream;
    aStream << aNumber;
    sDst = aStream.str();
}

//-----------------------------------------------------------------------------
#ifndef TIZEN_MIGRATION
template<class T>
inline void StringHelper::ToString(T aNumber, Tizen::Base::String& rDst)
{
    std::wstring sTemp;
    ToString(aNumber, sTemp);
    rDst = sTemp.c_str();
}
#endif

HERE_MAPS_END_NAMESPACE

#endif
