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

#ifndef TILEKEY_H_
#define TILEKEY_H_

#include "common/HereMaps_global.h"
#include "maps/GeoTiledMap.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates information that identifies a map tile in a grid
 * reflecting the normalized Mercator projection. The projection represents the
 * surface of the globe as a set of squares. The size of the grid depends on the
 * map zoom level.  At the lowest zoom level, the entire globe is
 * shown in one square, which means that the tile grid consists of one row and
 * one column. At the next higher zoom level, the tile grid contains two rows
 * and two columns per row, at the next, four rows and four columns per row, and
 * so on -- in other words, the number of rows and columns doubles at each
 * higher zoom level.
 */
class TileKey
{
public:
    /**
     * This is a constructor. It initializes a new instance of the tile key with
     * the zoom level and the x and y coordinates of the tile at that zoom level.
     * 
     * @param aLevel A value indicating the zoom level.
     * 
     * @param aX A value indicating the x coordinate in the map tile grid.
     * 
     * @param aY A value indicating the y coordinate in the map tile grid.
     *
     * @param aMapLanguage A value indicating the map language.
     *
     * @param aMapLanguage A value indicating the map type.
     */ 
    TileKey(int aLevel,
            int aX,
            int aY,
            String sMapLanguage = String("eng"),
            GeoTiledMap::MapType aMapType = GeoTiledMap::MT_Normal_Day)
    {
        m_aLevel = aLevel;
        m_aX = aX;
        m_aY = aY;
        m_sMapLanguage = sMapLanguage;
        m_aMapType = aMapType;
    }

    /** 
     * This method is a copy constructor.
     * 
     * @param rRhs A constant reference to an object whose contents are to be
     *        copied into the present instance.
     */
    TileKey(const TileKey& rRhs)
    {
        operator = (rRhs);
    }

    /**
     * This method retrieves a tile hash value based on the tile key properties.
     * 
     * @return An integer value representing the tile hash.
     */
    int GetHash() const
    {
        int hashValue = (((int)m_aMapType) << 25) +
                (m_aLevel << 16) +
                (m_aY << 8) +
                m_aX;
        return hashValue;
    }

    /** 
     * This is an equality operator.
     * 
     * @param rRhs A constant reference to an object that is to be compared to
     *       the present instance.
     * 
     * @return <code>true</code> if the given instance and the right-hand object
     *       are identical, otherwise <code>false</code>.
     */
    bool operator == (const TileKey& rRhs) const
    {
        return m_aLevel == rRhs.m_aLevel &&
                m_aX == rRhs.m_aX &&
                m_aY == rRhs.m_aY &&
                m_sMapLanguage == rRhs.m_sMapLanguage &&
                m_aMapType == rRhs.m_aMapType;
    }

    /** 
     * This is an assignment operator.
     * 
     * @param rRhs A constant reference to an object whose contents are to be
     *        copied into the present instance.
     * 
     * @return A reference to the given instance of the class after the assignment.
     */
    TileKey& operator = (const TileKey& rRhs)
    {
        if (&rRhs != this)
        {
            m_aLevel = rRhs.m_aLevel;
            m_aX = rRhs.m_aX;
            m_aY = rRhs.m_aY;
            m_sMapLanguage = rRhs.m_sMapLanguage;
            m_aMapType = rRhs.m_aMapType;
        }
        return *this;
    }

    /**
     * This member variable holds a value indicating the tile zoom level.
     */ 
    int m_aLevel;

    /**
     * This member variable holds a value indicating the x coordinate of the tile.
     */ 
    int m_aX;

    /**
     * This member variable holds a value indicating the y coordinate of the tile.
     */ 
    int m_aY;

    /**
     * This member variable holds a value indicating the map language.
     */
    String m_sMapLanguage;

    /**
     * This member variable holds a value indicating the map type.
     */
    GeoTiledMap::MapType m_aMapType;
};

HERE_MAPS_END_NAMESPACE

#endif // TILEKEY_H_
