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

#ifndef _SIZE_H_
#define _SIZE_H_

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

/** 
 * This class encapsulates a image size defined in terms of its width and
 * height. It can apply to a map, an overlay or an icon.
 */ 
class Size
{
public:
    /**
     * This method is the default constructor.
     */
    Size();

    /**
     * This method is a constructor that initializes the new instance with the
     * width and height supplied by the caller.
     * 
     * @param aWidth A value specifying the image width in pixels.
     * 
     * @param aHeight A value specifying the image height in pixels. 
     */
    Size(int aWidth, int aHeight);

    /**
     * This method is a copy constructor that initializes the new instance by
     * copying the properties of the instance supplied by the caller.
     * 
     * @param rRhs A constant reference to an object whose properties are to be
     *        copied to initialize the new instance.
     */
    Size(const Size& rRhs);

    /**
     * This method is the destructor.
     */
    ~Size();

    /**
     * This method sets the properties of the given instance of the class.
     * 
     * @param aWidth A value specifying the image width in pixels.
     * 
     * @param aHeight A value specifying the image height in pixels. 
     */
    void SetSize(int aWidth, int aHeight);

    /**
     * This method retrieves the width of the image. 
     *
     * @return A value representing the width of the image.
     */
    int GetWidth() const;

    /**
     * This method retrieves the height of the image. 
     *
     * @return A value representing the height of the image.
     */
    int GetHeight() const;

    /**
     * This is the assignment operator. 
     * 
     * @param rRhs A constant reference to an object whose properties are to be copied
     *        to the given instance.
     * 
     * @return A Reference to the given instance of the class after its
     *        properties have been updated.
     */
    Size& operator = (const Size& rRhs);

    /**
     * This is the quality operator. It check if the given instance of the class
     * is identical to the right-hand-side object.
     * 
     * @param rRhs A constant reference to an object whose properties are to be
     *        compared to the properties of the given instance.
     * 
     * @return <code>true</code> if the objects are identical, otherwise
     *         <code>false</code>.
     */
    bool operator == (const Size& rRhs) const;

private:
    class SizeImpl;
    SizeImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif /* _SIZE_H_ */
