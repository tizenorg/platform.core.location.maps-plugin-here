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

#ifndef TILEFETCHERREPLY_H
#define TILEFETCHERREPLY_H

#include <tr1/memory>

#include "common/HereMaps_global.h"
#include "common/BaseReply.h"
#include "common/TileKey.h"

#include "maps/GeoTile.h"

#ifndef TIZEN_MIGRATION
namespace Tizen{ namespace Graphics{ class Bitmap; } }
#endif

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates a reply to a request for a map tile. 
 * 
 * \ingroup tilefetcher
 */
class TileFetcherReply : public BaseReply
{
public:
    /** 
     * This method is a constructor that initialize the class instance, using
     * an object that specifies the map tile row, column, zoom level, map
     * language and map type.
     * 
     * @param rKey A constant reference to a tile key object.
     */
    TileFetcherReply(const TileKey& rKey);

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~TileFetcherReply();

    /**
     * This method retrieves the map tile as a bitmap from the reply to the
     * query.
     * 
     * @return A bitmap that contains the map tile.
     */
    DrawableBitmapPtr GetTile() const;

    /**
     * This method retrieves an object specifying the map tile
     * row, column and zoom level.
     * 
     * @return A constant reference to an object that contains the map tile row,
     *        column, zoom level, map language and map type.
     */
    const TileKey& GetKey() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(TileFetcherReply);
    friend class TestTileFetcher;

    virtual bool OnDataReceived(const unsigned char* pBuffer, size_t uSize);

    class TileFetcherReplyImpl;
    TileFetcherReplyImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
