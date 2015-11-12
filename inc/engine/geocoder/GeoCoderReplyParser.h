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

#ifndef GEOCODERREPLYPARSER_H
#define GEOCODERREPLYPARSER_H

#include "common/HereMaps_global.h"

#include <libxml/tree.h>
#include <libxml/xpath.h>

HERE_MAPS_BEGIN_NAMESPACE

class Result;
class Address;
class MetaInfo;
class ErrorBase;
class ParserError;
class GeoLocation;
class GeoCoordinates;
class GeoBoundingBox;

/**
 * This class encapsulates a request reply parser. It provides methods dedicated
 * to parsing specific nodes of the reply data and populating a destination
 * object supplied by the caller.
 * 
 * \ingroup geocoding
 */
class GeoCoderReplyParser
{
public:
    /**
     * This method retrieves reply meta info held in the XML node supplied
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
    static bool ParseMetaInfo(xmlNodePtr pNode, MetaInfo& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves a result entry held in the XML node supplied
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
    static bool ParseResultEntry(xmlNodePtr pNode, Result& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves an address held in the XML node supplied
     * by the caller 
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
    static bool ParseAddress(xmlNodePtr pNode, Address& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves geographic coordinates held in the XML node supplied
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
     * This method retrieves location information held in the XML node supplied
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
    static bool ParseLocation(xmlNodePtr pNode, GeoLocation& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves match quality information held in the XML node supplied
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
    static bool ParseMatchQualitites(xmlNodePtr pNode, Result& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

    /**
     * This method retrieves  held in the XML node supplied
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
    static bool ParseBoundingBox(xmlNodePtr pNode, GeoBoundingBox& rDst, xmlXPathContextPtr pCtx, ParserError*& pError);

private:
    static bool ExtractContent(xmlNodePtr pNode, String& sDst, ParserError*& pError);
    static bool ExtractNodeName(xmlNodePtr pNode, String& sDst, ParserError*& pError);
    static xmlNodePtr FindChildNode(xmlNodePtr pNode, const char* pUTF8Literal);

    static void AppendOrSet(ParserError*& pError, ParserError* pLoc);

    HERE_MAPS_NO_COPY_NO_ASSIGN(GeoCoderReplyParser);
};

HERE_MAPS_END_NAMESPACE

#endif
