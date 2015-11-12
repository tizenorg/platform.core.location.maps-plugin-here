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

#ifndef TILEFETCHERQUERY_H
#define TILEFETCHERQUERY_H

#include "common/HereMaps_global.h"
#include "common/BaseQuery.h"
#include "common/TileKey.h"

HERE_MAPS_BEGIN_NAMESPACE

class TileFetcherQueryListener;

/**
 * This class encapsulates a query representing a request for a map tile. 
 * 
 * Map tiles form a grid reflecting the normalized Mercator projection, which
 * represents the surface of the globe as a set of squares. The size of the grid
 * depends on the map zoom level. At the lowest zoom level, the entire globe is
 * shown in one square, which means that the tile grid consists of one row and
 * one column. At the next higher zoom level, the tile grid contains two rows
 * and two columns per row, at the next, four rows and four columns per row, and
 * so on -- in other words, the number of rows and columns doubles at each
 * higher zoom level.
 * 
 * The map tiles are available in resolutions of 128 x 128 pixels or 256 x 256
 * pixels, depending on the size of the available memory on the target device.
 * 
 * \ingroup tilefetcher
 */
class TileFetcherQuery : public BaseQuery
{
public:
    /**
     * This method is the default constructor.
     */
    TileFetcherQuery();

    /**
     * This method is a constructor that sets the class attributes using the
     * arguments provided by the caller.
     * 
     * @param rKey A constant reference to an object that specifies the map tile
     *        row, column and zoom level.
     * 
     * @param uSize A value indicating the tile size.
     */
    TileFetcherQuery(const TileKey& rKey, size_t uSize);

    /**
     * This method is the (virtual) destructor.
     */
    virtual ~TileFetcherQuery();

    /**
     * This method sets the hash key which is used for the query.
     * If not set or string is empty, "newest" will be used.
     *
     * @param hash A string containing the hash key to be used.
     */
    void SetHash(String hash);

    /**
     * This method retrieves an object specifying the map tile row, column and
     * zoom level.
     * 
     * @return  A constant reference to an object that specifies the map tile
     *        row, column and zoom level.
     */
    const TileKey& GetKey() const;

    /**
     * This method sets an object specifying the map tile row, column and zoom
     * level.
     * 
     * @return rKey A constant reference to an object that specifies the map tile
     *        row, column and zoom level.
     */
    void SetKey(const TileKey& rKey);

    /**
     * This method sets the size of the map tile (resolution) in pixels.
     * 
     * @param uTileSize A value indicating the tile size.
     */
    void SetTileSize(size_t uTileSize);

    /**
     * This method retrieves the size of the map tile (resolution) in pixels.
     * 
     * @param uTileSize A value indicating the tile size.
     */
    size_t GetTileSize() const;

    /**
     * This method attempts to establish a connection with the server and then,
     * if the connection has been established, it builds and submits a query.
     *
     * @param rListener A reference to a an object that is to be notified when
     *        the reply to the query has arrived from the server.
     *
     * @param pUserData A pointer to an object containing user passed, which is
     *        to be echoed back through the reply object.
     *
     * @return A value representing the identifier of issued request.
     */
    virtual RestItemHandle::RequestId Execute(TileFetcherQueryListener& rListener, Tizen::Maps::HereObject* pUserData = NULL) const;

    /**
     * This method returns the base URI to be used for all subsequent
     * tile fetcher queries based on the current setting of map type in the
     * <code>TileKey</code> object.
     *
     * @return A string containing the base URI.
     */
#ifdef TIZEN_MIGRATION
    String GetBaseUri();
#else
    static String GetBaseUri();
#endif

    /**
     * This method returns the base URI to be used for all subsequent
     * tile fetcher queries based on the current setting of map type in the
     * <code>TileKey</code> object.
     *
     * @param sUri A constant reference to a string containing the base URI.
     */
#ifdef TIZEN_MIGRATION
    void SetBaseUri(const String& sUri);
#else
    static void SetBaseUri(const String& sUri);
#endif

private:
    /**
     * This method creates the URI for the request.
     *
     * @return URI request string.
     */
    String CreateUri() const;

private:
    HERE_MAPS_NO_COPY_NO_ASSIGN(TileFetcherQuery);

    class TileFetcherQueryImpl;
    TileFetcherQueryImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
