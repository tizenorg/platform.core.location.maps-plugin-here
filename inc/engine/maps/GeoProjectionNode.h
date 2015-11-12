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

#ifndef GEOPROJECTIONNODE_P_H
#define GEOPROJECTIONNODE_P_H

#include <vector>
#include <tr1/memory>

#include "common/HereMaps_global.h"

#ifndef TIZEN_MIGRATION
#include <FGraphics.h>
#include <FMediaImage.h>
#endif

#include "internal/DoublePoint.h"
#include "internal/DoublePoint3.h"
#ifdef TIZEN_MIGRATION
// chanywa #include "base/BaseByteBuffer.h"
#endif

#include "maps/GeoTile.h"

HERE_MAPS_BEGIN_NAMESPACE

class GeoProjectionNode
{
public:
    GeoProjectionNode();
    GeoProjectionNode(const DrawableBitmapPtr& image);
    ~GeoProjectionNode();

    std::vector<DoublePoint3> m_points;
    std::vector<DoublePoint3> m_subPoints;

    DrawableBitmapPtr m_image;
    DrawableBitmapPtr m_layer;
    double m_r;
    double m_x;
    double m_y;
    bool m_clipped;
    bool m_culled;
    bool m_split;
    bool m_requestImage;
    bool m_peekImage;
    bool m_postdrawing;
    bool m_drawing;
    bool m_predrawing;
    int m_splitCount;
    int m_tx;
    int m_ty;
    int m_stx;
    int m_sty;
    int m_rtx;
    int m_rty;
    int m_rlevel;
    int m_level;
    float m_opacity;

    enum{ NUM_OF_CHILDREN = 4 };
    GeoProjectionNode* m_children[NUM_OF_CHILDREN];

    void setImage(const DrawableBitmapPtr& image);
    void applyImage(const DrawableBitmapPtr& image,const float opacity);

    bool requestImage(){ return m_requestImage; }
    bool peekImage(){ return m_peekImage; }
    bool split(){ return m_split; }
    bool postdrawing(){ return m_postdrawing && m_image != 0; }
    bool drawing(){ return m_drawing && m_image != 0; }
    bool predrawing(){ return m_predrawing && m_image != 0; }

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoProjectionNode);
};

HERE_MAPS_END_NAMESPACE

#endif // QGEOPROJECTED_P_H
