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

#ifndef ENCODING_CONVERSION_H
#define ENCODING_CONVERSION_H

#include "common/HereMaps_global.h"

#include <string>

#ifndef TIZEN_MIGRATION
namespace Tizen{ namespace Base{ class ByteBuffer; } }
#endif

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class offers encoding conversion utilities between UTF-8 and platform
 * default string encoding.
 */
class EncodingConversion
{
public:
    /**
     * This method converts a platform string to UTF-8.
     *
     * @param sSrc A constant reference to a platform string to convert.
     *
     * @param sDst A reference to a string object holding the results of
     *        conversion to UTF-8.
     *
     * @return Always <code>true</code>.
     */
    static bool ToUTF8(const WString& sSrc, std::string& sDst);


    /**
     * This method converts a UTF-8 string to a platform string.
     * 
     * @param sSrc A constant reference to an unsigned character buffer
     *        containing the string to convert. 
     * 
     * @param uLen A value representing the length of the buffer containing the
     *        string to covert.
     * 
     * @param sDst A reference to a string object holding the results of
     *        conversion from UTF-8.
     * 
     * @return Always <code>true</code>.
     */
    static bool FromUTF8(const char* pSrc, size_t uLen, WString& sDst);

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(EncodingConversion);
};


HERE_MAPS_END_NAMESPACE

#endif
