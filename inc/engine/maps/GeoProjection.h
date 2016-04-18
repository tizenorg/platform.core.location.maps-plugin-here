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

#ifndef GEOPROJECTION_H
#define GEOPROJECTION_H

#include <vector>

#include "common/HereMaps_global.h"

#ifdef TIZEN_MIGRATION
#include "graphic/DoubleMatrix4.h"
#include "graphic/Dimension.h"
#include "graphic/Point.h"
#else
#include <FGraphics.h>
#include <FBaseDoubleMatrix4.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class DoublePoint;
class DoublePoint3;
class GeoCoordinates;
class GeoProjectionNode;

class GeoProjection
{
public:
    GeoProjection();
    virtual ~GeoProjection();

    virtual Tizen::Maps::Point geoToPixel(const GeoCoordinates& geo) const = 0;
    virtual GeoCoordinates pixelToGeo(const Tizen::Maps::Point& pixel) const = 0;

    virtual std::vector<GeoProjectionNode*> projectRoot();
    virtual GeoProjectionNode* projectQuad(GeoProjectionNode* parent, int quad);

    virtual void setTileSize(const Tizen::Maps::Dimension& size);
    Tizen::Maps::Dimension tileSize() const;

    virtual void setScreenSize(const Tizen::Maps::Dimension& size);
    Tizen::Maps::Dimension screenSize() const;

    virtual void setLevel(double value);
    double level() const;

    virtual void setMaximumLevel(double value);
    double maximumLevel() const;

    virtual void setMinimumLevel(double value);
    double minimumLevel() const;

    virtual void setHeading(double value);
    double heading() const;

    virtual void setGeoCenter(const GeoCoordinates& value);
    GeoCoordinates geoCenter() const;

    virtual bool setGeoCenterInPx(const Tizen::Maps::Point& value);
    Tizen::Maps::Point screenCenter() const;

    DoublePoint projectPoint(const DoublePoint& point) const;

protected:
    virtual void filter(GeoProjectionNode& transform,const std::vector<DoublePoint3>& points) = 0;
    virtual DoublePoint3 projectPoint(double x, double y, double z=0) const = 0;

    Tizen::Maps::DoubleMatrix4& GetMatrix();
    const Tizen::Maps::DoubleMatrix4& GetMatrix() const;
    Tizen::Maps::DoubleMatrix4& GetInverse();
    const Tizen::Maps::DoubleMatrix4& GetInverse() const;

    Tizen::Maps::Dimension& GetTileSize();
    Tizen::Maps::Dimension& GetScreenSize();
    GeoCoordinates& GetGeoCenter();
    double& GetLevel();
#ifdef TIZEN_MIGRATION
public:
#endif
    double& GetHeading();

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoProjection);
    friend class TestGeoProjection;

    class GeoProjectionImpl;
    GeoProjectionImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif // GEOPROJECTION_P_H
