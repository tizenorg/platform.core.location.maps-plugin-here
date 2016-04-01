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

#ifndef GEOOPENGLRENDERER_H
#define GEOOPENGLRENDERER_H

#include "common/HereMaps_global.h"

#include <vector>

#ifdef TIZEN_MIGRATION
#include "graphic/FloatRectangle.h"
#include "graphic/Color.h"
#else
#include <FGraphics.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

class GlTexture;
class GeoTiledMap;
class GeoMapObjectMarker;
class GeoProjectionNode;
class DrawableBitmap;

/**
 * This class encapsulates an Open GL renderer used to render map tiles.
 * 
 * \ingroup maps
 */
class GeoOpenGlRenderer
{
public:
    /**
     * This method is the default constructor.
     */
    GeoOpenGlRenderer();

    /**
     * This method is the default destructor.
     */
    ~GeoOpenGlRenderer();

    /**
     * This method creates an EGL texture from the image associated with the
     * caller-supplied bitmap drawable.
     * 
     * @param rDrawableBitmap A reference to a bitmap object that contains the
     *        image to be drawn.
     * 
     * @return <code>true</code> if the image has been made drawable,
     *        <code>false</code> if a texture could not be associated with the supplied
     *        bitmap object.
     */
    bool MakeDrawable(DrawableBitmap& rDrawableBitmap);

    /**
     * This method renders the image(s) provided by the caller. The caller can
     * specify the size of the area to render (the visible map area).
     * 
     * @param nodes A list of objects containing images to render.
     * 
     * @param width A value indicating the width of the area to render.
     * 
     * @param height A value indicating the height of the area to render.
     */
    bool Render(const std::vector<GeoProjectionNode*>& nodes,
                unsigned int width,
                unsigned int height);

    /**
     * This method renders a square, using the rectangle and texture specified
     * by the caller.
     *
     * @param aRect A constant reference to the rectangle to render.
     *
     * @param rTexture A constant reference to the texture object to apply.
     *
     * @param sx0 A value providing the x coordinate of the top left corner of
     *        the rectangle in the tile grid.
     *
     * @param sy0 A value providing the y coordinate of the top left corner of
     *        the rectangle in the tile grid.
     *
     * @param sx1 A value providing the x coordinate of the bottom right corner of
     *        the rectangle in the tile grid.
     *
     * @param sy1 A value providing the y coordinate of the bottom right corner of
     *        the rectangle in the tile grid.
     */
    bool RenderQuad(const Tizen::Maps::FloatRectangle& aRect, const GlTexture& rTexture, float sx0=0.f, float sy0=1.f, float sx1=1.f, float sy1=0.f);

    /**
     * This method renders a square, using the rectangle and texture specified
     * by the caller.
     *
     * @param aRect A constant reference to the rectangle to render.
     *
     * @param uTexture A value of the id of the texture object to apply.
     *
     * @param sx0 A value providing the x coordinate of the top left corner of
     *        the rectangle in the tile grid.
     *
     * @param sy0 A value providing the y coordinate of the top left corner of
     *        the rectangle in the tile grid.
     *
     * @param sx1 A value providing the x coordinate of the bottom right corner of
     *        the rectangle in the tile grid.
     *
     * @param sy1 A value providing the y coordinate of the bottom right corner of
     *        the rectangle in the tile grid.
     */
    bool RenderQuad(const Tizen::Maps::FloatRectangle& aRect, unsigned int uTextureId, float sx0=0.f, float sy0=1.f, float sx1=1.f, float sy1=0.f);

    /**
     * This method changes the color that will be used by the gl clear method.
     */
    void SetClearColor(const Tizen::Maps::Color& color);

    /**
     * This method clears the screen.
     */
    void Clear();

private:
    bool Initialize();
    
private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoOpenGlRenderer);
    class GeoOpenGlRendererImpl;
    GeoOpenGlRendererImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif // GEOOPENGLRENDERER_P_H
