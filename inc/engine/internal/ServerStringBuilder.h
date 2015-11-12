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

#ifndef SERVERSTRINGBUILDER_H_
#define SERVERSTRINGBUILDER_H_

#include <iostream>

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoCoordinates;
class GeoBoundingBox;
class Distance;
class Proximity;

class ServerStringBuilder
{
public:
    virtual ~ServerStringBuilder();

    std::string ToString(const GeoCoordinates& coords) const;
    std::string ToString(const GeoBoundingBox& box) const;
    std::string ToString(const Distance& distance) const;
    std::string ToString(const Proximity& proximity) const;

    static ServerStringBuilder& GetInstance();

private:
    ServerStringBuilder();

    std::string CoordinateToString(double d) const;
    std::string ToString(double d, int percision) const;

    void removeTrailingZeros(std::string& s) const;

private:
    static ServerStringBuilder* m_instance;
};

HERE_MAPS_END_NAMESPACE

#endif /* SERVERSTRINGBUILDER_H_ */
