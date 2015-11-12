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

#ifndef DRAWABLE_BITMAP_H
#define DRAWABLE_BITMAP_H

#include "common/HereMaps_global.h"
#ifdef TIZEN_MIGRATION
#include "graphic/Bitmap.h"
#else
#include <FGraphics.h>
#endif

#include <tr1/memory>

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates a bitmap that can be drawn on the map.
 */
class DrawableBitmap
{
public:
    /**
     * This typedef defines a rendering handle as a type.
     */
    typedef UInt RenderHandle;

    /**
     * This is a copy constructor. It creates a new instance of the class, using
     * an existing bitmap.
     * 
     * @param bitmap A pointer to an existing bitmap.
     */
#ifdef TIZEN_MIGRATION
    DrawableBitmap(std::unique_ptr<Tizen::Maps::Bitmap>& bitmap);
#else
    DrawableBitmap(std::auto_ptr<Tizen::Graphics::Bitmap>& bitmap);
#endif
    /**
     * This is the destructor.
     */
    ~DrawableBitmap();

    /**
     * This method retrieves a pointer to the bitmap encapsulated in the given
     * instance of the class.
     */
#ifdef TIZEN_MIGRATION
    Tizen::Maps::Bitmap* GetBitmap() const;
#else
    Tizen::Graphics::Bitmap* GetBitmap() const;
#endif
    /**
     * This method sets the rendering handle.
     *
     * @param aRenderHandle A value representing the rendering handle to set.
     */
    void SetRenderHandle(RenderHandle aRenderHandle);

    /**
     * This method retrieves the rendering handle.
     * 
     * @return A value representing the rendering handle to set.
     */
    RenderHandle GetRenderHandle() const;

    /**
     * This method resets the rendering handle on the given object.
     */
    void ResetRenderHandle();

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(DrawableBitmap);

    class DrawableBitmapImpl;
    DrawableBitmapImpl* m_pImpl;
};

typedef std::tr1::shared_ptr<DrawableBitmap> DrawableBitmapPtr;

HERE_MAPS_END_NAMESPACE

#endif
