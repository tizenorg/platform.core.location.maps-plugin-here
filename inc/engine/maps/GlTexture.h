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

#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "common/HereMaps_global.h"

#ifdef TIZEN_MIGRATION
#include "graphic/Bitmap.h"
#else
#include <FGraphics.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates a GL texture that is a container for map tile bitmaps.
 * 
 * \ingroup maps
 */
class GlTexture
{
public:
    
    /**
     * This method is a constructor that initializes a new texture instance with
     * the bitmap object provided by the caller.
     * 
     * @param rBitmap A constant reference to a bitmap object.
     */
    GlTexture(const Tizen::Maps::Bitmap& rBitmap);

    /**
     * This method is the destructor.
     */
    ~GlTexture();
    
    /**
     * This method retrieves the texture id.
     * 
     * @return A value representing the texture id.
     */
    unsigned int GetTextureId() const;
    
    /**
     * This method sets the texture id.
     * 
     * @param uId A value representing the texture id.
     */
    void SetTextureId(unsigned int uId);

    /**
     * This method checks if the called instance wraps a valid GL texture
     *
     */
    bool IsValid() const;

    /**
     * This method checks if the passed texture handle is a valid GL texture
     *
     */
    static bool IsValid(unsigned int uId);

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(GlTexture);

    class GlTextureImpl;
    GlTextureImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
