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

#ifndef JSON_PARSER_H_
#define JSON_PARSER_H_

#include "common/HereMaps_global.h"
#include "finder/Category.h"
#include "finder/ContactDetails.h"
#include "finder/ExtendedAttribute.h"
#include "finder/ImageContent.h"
#include "finder/ReviewContent.h"
#include "finder/EditorialContent.h"
#include "finder/PlaceItem.h"
#include "finder/SearchItem.h"
#include "finder/PlaceDetails.h"

#ifndef TIZEN_MIGRATION
#include <FBase.h>
#include <FWeb.h>
#endif
#include <vector>
#include <map>

#ifdef TIZEN_MIGRATION
#include "base/BaseByteBuffer.h"
#include <json.h>

#define JsonArray  json_object
#define JsonNumber json_object
#define JsonObject json_object
#define IJsonValue json_object
#define JsonBool   json_object

using namespace Tizen::Maps;
#else
using namespace Tizen::Base;
using namespace Tizen::Base::Utility;
using namespace Tizen::Web::Json;
#endif

HERE_MAPS_BEGIN_NAMESPACE

class DiscoveryReply;
class BaseContent;
class Address;
class GeoCoordinates;
class BaseQuery;
class GeoLocation;
class LinkObject;
class Ratings;
class GeoBoundingBox;
class SearchContext;
class FinderError;

/**
 * Parses Places API Json data.
 *
 * @ingroup Search / Online / Parser
 */
class JsonParser
{
public:

    /**
     * Parse discover search results.
     * @param json_stream ByteBuffer.
     * @param results_page Parsed Discovery query.
     * @param error A pointer to an object that is populated
     *        with error information should parsing fail.
     */
    static bool ParseDiscoverySearch( ByteBuffer& buf, DiscoveryReply& results_page, FinderError*& error);

    /**
     * Parse place result.
     * @param json_stream ByteBuffer.
     * @param place_data Parsed place data.
     * @param error A pointer to an object that is populated
     *        with error information should parsing fail.
     */
    static bool ParsePlaceResult( ByteBuffer& buf, PlaceDetails& place_data, FinderError*& error);

private:

    static void ParseGeocodeSearch( ByteBuffer& json_stream,
                                           std::vector< GeoLocation >& results );

    static void ParseReverseGeocodeSearch( ByteBuffer& json_stream, Address& address );


    static void ParseTextSuggestions( ByteBuffer& json, std::vector< String >& suggestions );


    static void ParseDiscoverySearch( IJsonValue* json, DiscoveryReply& results_page );

    static void ParsePlaceResult( IJsonValue* json, PlaceDetails& place_data );

    static void ParseAlternativeNames( JsonArray* json_data,
                                         PlaceDetails::AlternativeNames& alternative_names );

    static void ParsePlaceLocation( JsonObject* json_data, GeoLocation& location );

    static void ParsePosition( JsonObject* json_data, GeoCoordinates& position );

    static void ParseAddress( JsonObject* json_data, Address& address );

    static void ParseContacts( JsonArray* json_data, const String& key,
                               ContactDetailsList& contacts );
#ifndef TIZEN_MIGRATION
    static void ParseLinkObject( IJsonValue* json_data,
                                   const char* object_name,
                                   LinkObject& link_object );
#endif
    static void ParseLinkObject( JsonObject* json_data, LinkObject& link_object );
#ifndef TIZEN_MIGRATION
    static void ParseLinkObject( JsonObject* json_data,
                                   const char* object_name,
                                   LinkObject& link_object );
#endif
    static void ParseRatings( JsonObject* json_data, Ratings& ratings );

    static void ParseCategories( JsonArray* json_data, CategoryList& categories );

    static void ParseCategory( JsonObject* json_data, Category& category );

    static void ParseAttributes( JsonObject* json_data, ExtendedAttributeList& attributes );

    static void ParseSearchContext( JsonObject* json_data, SearchContext& results_context );

    static void ParseBbox( JsonObject* json_data, GeoBoundingBox& bbox );

    static void ParseResultsItemPlace( JsonObject* json_data, PlaceItem& place_result );

    static void ParseResultsItemSearch( JsonObject* json_data, SearchItem& search_result );

    static void ParsePlaceRelated( JsonObject* json_data, PlaceDetails& place_data );

    static void ParsePlaceMedia( JsonObject* json_data, PlaceDetails& place_data );

    static void ParsePlaceEditorials( JsonObject* json_data, EditorialContentList& editorials );

    static void ParsePlaceImages( JsonObject* json_data, ImageContentList& images );

    static void ParsePlaceReviews( JsonObject* json_data, ReviewContentList& reviews );

    static void ParsePlaceEditorial( JsonObject* json_data, EditorialContent& editorial );

    static void ParsePlaceImage( JsonObject* json_data, ImageContent& image );

    static void ParsePlaceReview( JsonObject* json_data, ReviewContent& review );

    static void ParsePlaceBaseContent( JsonObject* json_data, BaseContent& media );

    static void TraverseRootNode( ByteBuffer& json_stream, IJsonValue* root );
    static void ParseCoordinates( IJsonValue* json_location, GeoLocation& loc );
    static void ParseBoundingBox( IJsonValue* json_location, GeoLocation& loc );
    static void ParseAddress( IJsonValue* json_location, GeoLocation& loc );

    static void ParsePlaceResults(JsonArray* pObject, PlaceItemList&, SearchItemList& );

private:
    static void GetStringValue(JsonObject* pObject, const String& sKey, String& value );
    static void GetUriValue(JsonObject* pObject, const String& sKey, Uri& uri );
    static bool GetValuePtr(JsonObject* pObject, const String& sKey, IJsonValue*& pValue );
};

HERE_MAPS_END_NAMESPACE

#endif // JSON_PARSER_H_
