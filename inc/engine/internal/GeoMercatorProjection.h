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

#ifndef GEOMERCATORPROJECTION_H
#define GEOMERCATORPROJECTION_H

#include <cmath>

#ifdef TIZEN_OSP_BASED
#include <FGraphics.h>
#endif

#include "common/HereMaps_global.h"
#include "maps/GeoProjection.h"
#include "internal/DoublePoint.h"
#include "internal/DoublePoint3.h"

HERE_MAPS_BEGIN_NAMESPACE


/**
 * This class encapsulates the normalized mercator projection. In this
 * projection, the map is represented by a grid of square tiles (bitmap
 * images). The position of the tile in this grid depends on the map zoom level
 * and is defined by the x and y coordinates. At the lowest zoom level, there is
 * only one tile. At the next zoom level, the grid is 2 x 2. With each higher
 * zoom level the x-size and the y-size of the grid increase by a power of two.
 * 
 * \ingroup maps
 */

class GeoMercatorProjection : public GeoProjection
{
public:
    GeoMercatorProjection();

    virtual void setTileSize(const Tizen::Maps::Dimension& size);
    virtual void setScreenSize(const Tizen::Maps::Dimension& size);
    virtual void setLevel(double value);
    virtual void setGeoCenter(const GeoCoordinates& value);
    virtual void setHeading(double value);
    virtual bool setGeoCenterInPx(const Tizen::Maps::Point& value);
    virtual Tizen::Maps::Point geoToPixel(const GeoCoordinates& geo) const;
    virtual GeoCoordinates pixelToGeo(const Tizen::Maps::Point &pixel) const;
    virtual std::vector<GeoProjectionNode*> projectRoot();

protected:
    virtual GeoProjectionNode* createNodeAt(double left_x, double bottom_y);
    virtual void filter(GeoProjectionNode& transform,const std::vector<DoublePoint3>& points);
    virtual DoublePoint3 projectPoint(double x, double y, double z = 0.0) const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoMercatorProjection);

    void createProjection();
};

HERE_MAPS_END_NAMESPACE

#endif // GEOMERCATORPROJECTION_P_H
