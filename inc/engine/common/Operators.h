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

#ifndef OPERATORS_H
#define OPERATORS_H

#include "common/HereMaps_global.h"

#include <iostream>

HERE_MAPS_BEGIN_NAMESPACE

class Result;
class Address;
class MetaInfo;
class GeoLocation;
class GeoCoordinates;

HERE_MAPS_END_NAMESPACE

//add operators to global namespace

/**
 * This is an operator that inserts the contents of a <code>Result</code> object
 * into the output steam.
 * 
 * @param os A reference to the output stream to which the right-hand object is inserted.
 * 
 * @param rResult A constant reference to an object whose contents are to be
 *        inserted (output).
 * 
 * @return A reference to the output stream after insertion.
 */
std::ostream& operator<<(std::ostream& os, const HERE_MAPS_NAMESPACE_PREFIX::Result& rResult);

/**
 * This is an operator that inserts the contents of a <code>MetaInfo</code>
 * object into the output steam.
 * 
 * @param os A reference to the output stream to which the right-hand object is
 *        inserted.
 * 
 * @param rMetaInfo A constant reference to an object whose contents are to be
 *        inserted (output).
 * 
 * @return A reference to the output stream after insertion.
 */
std::ostream& operator<<(std::ostream& os, const HERE_MAPS_NAMESPACE_PREFIX::MetaInfo& rMetaInfo);

/**
 * This is an operator that inserts the contents of a <code>GeoLocation</code>
 * object into the output steam.
 * 
 * @param os A reference to the output stream to which the right-hand object is
 *        inserted.
 * 
 * @param rLocation A constant reference to an object whose contents are to be
 *        inserted (output).
 * 
 * @return A reference to the output stream after insertion.
 */
std::ostream& operator<<(std::ostream& os, const HERE_MAPS_NAMESPACE_PREFIX::GeoLocation& rLocation);

/**
 * This is an operator that inserts the contents of an <code>Address</code>
 * object into the output steam.
 * 
 * @param os A reference to the output stream to which the right-hand object is
 *        inserted.
 * 
 * @param rAddress A constant reference to an object whose contents are to be
 *        inserted (output).
 * 
 * @return A reference to the output stream after insertion.
 */
std::ostream& operator<<(std::ostream& os, const HERE_MAPS_NAMESPACE_PREFIX::Address& rAddress);

/**
 * This is an operator that inserts the contents of a
 * <code>GeoCoordinates</code> object into the output steam.
 * 
 * @param os A reference to the output stream to which the right-hand object is
 *        inserted.
 * 
 * @param rCoord A constant reference to an object whose contents are to be
 *        inserted (output).
 * 
 * @return A reference to the output stream after insertion.
 */
std::ostream& operator<<(std::ostream& os, const HERE_MAPS_NAMESPACE_PREFIX::GeoCoordinates& rCoord);

#endif
