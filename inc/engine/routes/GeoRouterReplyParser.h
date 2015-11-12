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

#ifndef GEOROUTERREPLYPARSER_H
#define GEOROUTERREPLYPARSER_H

#include "common/HereMaps_global.h"

#include "common/GeoCoordinates.h"
#include "common/GeoBoundingBox.h"
#include "routes/RouteSegment.h"

#include <libxml/tree.h>
#include <libxml/xpath.h>

HERE_MAPS_BEGIN_NAMESPACE

class ErrorBase;
class ParserError;
class GeoRoute;


/**
 * This class encapsulates a parser of replies to routing requests.  It provides
 * methods dedicated to parsing specific nodes of the reply data and populating
 * a destination object supplied by the caller.
 * 
 * \ingroup routes
 */
class GeoRouterReplyParser
{
public:

    /**
     * This method retrieves the route details held in the XML node supplied by
     * the caller.
     * 
     * @param pNode A pointer to the XML node to parse. 
     * 
     * @param rDst A reference to an object which is to receive the results.
     * 
     * @param pCtx A pointer to the XPath context.
     * 
     * @param pError A pointer to an object that is populated
     *        with error information should parsing fail.
     * 
     * @return <code>true</code> on success, otherwise <code>false</code> (in
     *        which case the last argument to the method can be used to retrieve
     *        the error information.
     */
    static bool ParseRouteEntry(xmlNodePtr pNode, GeoRoute& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves a route summary entry held in the XML node supplied
     * by the caller.
     * 
     * @param pNode A pointer to the XML node to parse. 
     * 
     * @param rDst A reference to an object which is to receive the results.
     * 
     * @param pCtx A pointer to the XPath context.
     * 
     * @param pError A pointer to an object that is populated
     *        with error information should parsing fail.
     * 
     * @return <code>true</code> on success, otherwise <code>false</code> (in
     *        which case the last argument to the method can be used to retrieve
     *        the error information.
     */
    static bool ParseSummary(xmlNodePtr pNode, GeoRoute& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves a route travel mode held in the XML node supplied
     * by the caller.
     * 
     * @param pNode A pointer to the XML node to parse. 
     * 
     * @param rDst A reference to an object which is to receive the results.
     * 
     * @param pCtx A pointer to the XPath context.
     * 
     * @param pError A pointer to an object that is populated
     *        with error information should parsing fail.
     * 
     * @return <code>true</code> on success, otherwise <code>false</code> (in
     *        which case the last argument to the method can be used to retrieve
     *        the error information.
     */
    static bool ParseMode(xmlNodePtr pNode, GeoRoute& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves the route shape definition from the XML node
     * supplied by the caller.
     * 
     * @param pNode A pointer to the XML node to parse. 
     * 
     * @param rDst A reference to an object which is to receive the results.
     * 
     * @param pCtx A pointer to the XPath context.
     * 
     * @param pError A pointer to an object that is populated
     *        with error information should parsing fail.
     * 
     * @return <code>true</code> on success, otherwise <code>false</code> (in
     *        which case the last argument to the method can be used to retrieve
     *        the error information.
     */
    static bool ParseShape(xmlNodePtr pNode, GeoCoordinateList& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves a route bounding box from the XML node
     * supplied by the caller.
     * 
     * @param pNode A pointer to the XML node to parse. 
     * 
     * @param rDst A reference to an object which is to receive the results.
     * 
     * @param pCtx A pointer to the XPath context.
     * 
     * @param pError A pointer to an object that is populated
     *        with error information should parsing fail.
     * 
     * @return <code>true</code> on success, otherwise <code>false</code> (in
     *        which case the last argument to the method can be used to retrieve
     *        the error information.
     */
    static bool ParseBoundingBox(xmlNodePtr pNode, GeoBoundingBox& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves a route waypoint defined in the XML node supplied
     * by the caller.
     * 
     * @param pNode A pointer to the XML node to parse. 
     * 
     * @param rDst A reference to an object which is to receive the results.
     * 
     * @param pCtx A pointer to the XPath context.
     * 
     * @param pError A pointer to an object that is populated
     *        with error information should parsing fail.
     * 
     * @return <code>true</code> on success, otherwise <code>false</code> (in
     *        which case the last argument to the method can be used to retrieve
     *        the error information.
     */
    static bool ParseCoordinate(xmlNodePtr pNode, GeoCoordinates& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves a route leg defined in the XML node supplied by the
     * caller.
     * 
     * @param pNode A pointer to the XML node to parse. 
     * 
     * @param rDst A reference to an object which is to receive the results.
     * 
     * @param pCtx A pointer to the XPath context.
     * 
     * @param pError A pointer to an object that is populated
     *        with error information should parsing fail.
     * 
     * @return <code>true</code> on success, otherwise <code>false</code> (in
     *        which case the last argument to the method can be used to retrieve
     *        the error information.
     */
    static bool ParseLeg(xmlNodePtr pNode, RouteSegment& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves the details of a maneuver defined in the XML node
     * supplied by the caller.
     * 
     * @param pNode A pointer to the XML node to parse. 
     * 
     * @param rDst A reference to an object which is to receive the results.
     * 
     * @param pCtx A pointer to the XPath context.
     * 
     * @param pError A pointer to an object that is populated
     *        with error information should parsing fail.
     * 
     * @return <code>true</code> on success, otherwise <code>false</code> (in
     *        which case the last argument to the method can be used to retrieve
     *        the error information.
     */
    static bool ParseManeuver(xmlNodePtr pNode, Maneuver& rDst, GeoCoordinateList& vSegmentPath, xmlXPathContextPtr pCtx, ParserError*& pError);

private:
    static bool ExtractContent(xmlNodePtr pNode, String& sDst, ParserError*& pError);
    static xmlNodePtr FindChildNode(xmlNodePtr pNode, const char* pUTF8Literal);

    static void AppendOrSet(ParserError*& pError, ParserError* pLoc);

    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoRouterReplyParser);

};

HERE_MAPS_END_NAMESPACE

#endif // GEOROUTERREPLYPARSER_H
