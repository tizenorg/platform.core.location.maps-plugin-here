/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "here_view_objects.h"
#include "here_utils.h"

#include <graphic/Grp_Util.h>
#include <maps/GeoMapObjectMarker.h>
#include <maps/GeoMapObjectPolygon.h>
#include <maps/GeoMapObjectPolyline.h>


using namespace HERE_PLUGIN_NAMESPACE_PREFIX;

HERE_PLUGIN_BEGIN_NAMESPACE

HereViewObjects::HereViewObjects()
{
	pthread_mutex_init(&__mutex, NULL);
}

HereViewObjects::~HereViewObjects()
{
	pthread_mutex_destroy(&__mutex);
}

void HereViewObjects::set(GeoTiledMap *map, Evas *evas)
{
	if (!map && !evas) removeAll();
	__map = map;
	__evas = evas;
}

bool HereViewObjects::__update_to_add_callback_func(int index, int total,
					      map_view_object_h object,
					      void *user_data)
{
	if (!user_data) return false;

	HereViewObjects *__this = (HereViewObjects*)user_data;
	VisualObjects::iterator cit;

	cit = __this->__currentObjects.find(object);
	if (cit == __this->__currentObjects.end())
		__this->add(object);
	return true;
}

here_error_e HereViewObjects::add(map_view_object_h hObj)
{
 	if (!hObj) return HERE_ERROR_INVALID_PARAMETER;

	here_error_e error = HERE_ERROR_INVALID_PARAMETER;
	if (__currentObjects.find(hObj) == __currentObjects.end())
		error = __add(hObj);

	return error;
}

here_error_e HereViewObjects::__add(map_view_object_h hObj)
{
	if (!__map) return HERE_ERROR_INVALID_OPERATION;

	here_error_e error = HERE_ERROR_NONE;
	GeoMapObject *hereObject = NULL;
	map_view_object_type_e type = MAP_VIEW_OBJECT_UNKNOWN;
	map_view_object_get_type(hObj, &type);

	switch(type)
	{
	case MAP_VIEW_OBJECT_MARKER:
		hereObject = new (std::nothrow) GeoMapObjectMarker;
		error = __updateMarker(hObj, (GeoMapObjectMarker*)hereObject);
		break;

	case MAP_VIEW_OBJECT_POLYGON:
		hereObject = new (std::nothrow) GeoMapObjectPolygon;
		error = __updatePolygon(hObj, (GeoMapObjectPolygon*)hereObject);
		break;

	case MAP_VIEW_OBJECT_POLYLINE:
		hereObject = new (std::nothrow) GeoMapObjectPolyline;
		error = __updatePolyline(hObj, (GeoMapObjectPolyline*)hereObject);
		break;
#ifdef TIZEN_3_0_NEXT_MS
	case MAP_VIEW_OBJECT_ROUTE:
		for (int i=0; i < 2; i++)
		{
			hereObject = new (std::nothrow) GeoMapObjectPolyline;
			if (hereObject)
			{
				__map->AddObject(hereObject);
				error = __updateRoute(hObj);
				if (error != HERE_ERROR_NONE) break;
				pthread_mutex_lock(&__mutex);
				__currentObjects.insert(std::make_pair(hObj, (GeoMapObjectPolyline*)hereObject));
				pthread_mutex_unlock(&__mutex);
			}

			hereObject = new (std::nothrow) GeoMapObjectMarker;
			if (hereObject)
			{
				__map->AddObject(hereObject);
				error = __updateRoute(hObj);
				if (error != HERE_ERROR_NONE) break;
				pthread_mutex_lock(&__mutex);
				__currentObjects.insert(std::make_pair(hObj, (GeoMapObjectMarker*)hereObject));
				pthread_mutex_unlock(&__mutex);
			}
		}
		break;
#endif /* TIZEN_3_0_NEXT_MS */
	default:
		error = HERE_ERROR_INVALID_PARAMETER;
		break;
	}

	if (error != HERE_ERROR_NONE)
	{
		if (hereObject) delete hereObject;
		hereObject = NULL;
	}

#ifdef TIZEN_3_0_NEXT_MS
	if (hereObject && type != MAP_VIEW_OBJECT_ROUTE)
#else
	if (hereObject)
#endif /* TIZEN_3_0_NEXT_MS */
	{
		__map->AddObject(hereObject);
		pthread_mutex_lock(&__mutex);
		__currentObjects.insert(std::make_pair(hObj, hereObject));
		pthread_mutex_unlock(&__mutex);
	}

	return error;
}

here_error_e HereViewObjects::remove(map_view_object_h hObj)
{
	if (!hObj) return HERE_ERROR_INVALID_PARAMETER;
	if (!__map) return HERE_ERROR_INVALID_OPERATION;

	//MAPS_LOGD("remove");
	VisualObjects::iterator it;
	pthread_mutex_lock(&__mutex);
	while ((it = __currentObjects.find(hObj)) != __currentObjects.end())
	{
	 	__map->RemoveObject((GeoMapObject*)it->second);
 		it = __currentObjects.erase(it);
 	}
	pthread_mutex_unlock(&__mutex);
	return HERE_ERROR_NONE;
}

here_error_e HereViewObjects::removeAll()
{
	pthread_mutex_lock(&__mutex);
	__currentObjects.clear();
	__map->ClearMapObjects();
	pthread_mutex_unlock(&__mutex);
	return HERE_ERROR_NONE;
}

here_error_e HereViewObjects::move(map_view_object_h hObj)
{
	if (!hObj) return HERE_ERROR_INVALID_PARAMETER;

	VisualObjects::iterator it;
	while ((it = __currentObjects.find(hObj)) != __currentObjects.end())
	{
		MAPS_LOGD("TODO: implement moving");
 	}

	return HERE_ERROR_NONE;
}

here_error_e HereViewObjects::update(map_view_object_h hObj)
{
	if (!hObj) return HERE_ERROR_INVALID_PARAMETER;

	here_error_e error = HERE_ERROR_INVALID_PARAMETER;
	VisualObjects::iterator it = __currentObjects.find(hObj);
	if (it != __currentObjects.end())
		error = __update(hObj, (GeoMapObject*)(it->second));

	return error;
}

here_error_e HereViewObjects::__update(map_view_object_h hObj, GeoMapObject *hereObject)
{
	if (!hObj) return HERE_ERROR_INVALID_PARAMETER;

	here_error_e error = HERE_ERROR_UNKNOWN;

	do {
		map_view_object_type_e type = MAP_VIEW_OBJECT_UNKNOWN;
		map_view_object_get_type(hObj, &type);

		switch(type)
		{
		case MAP_VIEW_OBJECT_MARKER:
			error = __updateMarker(hObj, (GeoMapObjectMarker*)hereObject);
			break;

		case MAP_VIEW_OBJECT_POLYGON:
			error = __updatePolygon(hObj, (GeoMapObjectPolygon*)hereObject);
			break;

		case MAP_VIEW_OBJECT_POLYLINE:
			error = __updatePolyline(hObj, (GeoMapObjectPolyline*)hereObject);
			break;

#ifdef TIZEN_3_0_NEXT_MS
		case MAP_VIEW_OBJECT_ROUTE:
			error = __updateRoute(hObj);
			break;
#endif /* TIZEN_3_0_NEXT_MS */

		default:
			break;
		}
	} while(0);

	return error;
}

here_error_e HereViewObjects::setVisible(map_view_object_h hObj)
{
	if (!hObj) return HERE_ERROR_INVALID_PARAMETER;

	bool visible;
	map_view_object_get_visible(hObj, &visible);

	VisualObjects::iterator it;
	for (it = __currentObjects.begin(); it != __currentObjects.end(); it++)
	{
		if (it->first == hObj)
	 		((GeoMapObject*)it->second)->SetVisible(visible);
 	}

	return HERE_ERROR_NONE;
}

here_error_e HereViewObjects::__updateMarker(map_view_object_h hMarker, GeoMapObjectMarker *hereMarker)
{
	if (!hMarker || !hereMarker)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__evas || !__map)
		return HERE_ERROR_INVALID_OPERATION;


 	int error = MAPS_ERROR_NONE;
	map_view_marker_type_e type;
	int nSize = 0, w, h;
	char *szPath = NULL;
	double lat, lng;
	maps_coordinates_h mapsCoord;
	Evas_Object *img = NULL;


	do {
 		/* image */
		error = map_view_object_marker_get_type(hMarker, &type);
		if (error != MAPS_ERROR_NONE || type >= MAP_VIEW_MARKER_NONE) break;

		error = map_view_object_marker_get_file_path(hMarker, &szPath);
		if (error != MAPS_ERROR_NONE || !szPath) break;

		img = evas_object_image_add(__evas);
		evas_object_image_file_set(img, szPath, NULL);
		int err = evas_object_image_load_error_get(img);

		if (err != EVAS_LOAD_ERROR_NONE)
		{
			MAPS_LOGE("Failed to load the image file for new marker. '%s'",
				(szPath ? szPath : "null"));
			g_free(szPath);
			break;
		}
		g_free(szPath);


		evas_object_image_size_get(img, &w, &h);
		nSize = w * h * 4;

		unsigned char *src = (unsigned char*)evas_object_image_data_get(img, EINA_FALSE);
		if (!src || nSize <= 0) {
			MAPS_LOGE("Failed to get the image buffer of new marker");
			error = MAPS_ERROR_OUT_OF_MEMORY;
			break;
		}

		unsigned char *dst = (unsigned char*)malloc(nSize);
		if (!dst) {
			error = MAPS_ERROR_OUT_OF_MEMORY;
			break;
		}
		memcpy(dst, src, nSize);

		_Util::ConvertRGBA2BGRA(dst, (unsigned)w, (unsigned)h);

		Bitmap bmp;
		bmp.Construct((const unsigned char*)dst, nSize, Dimension(w, h));
		hereMarker->SetBitmap(bmp);
		if (img) evas_object_del(img);

		g_free(dst);


		/* position */
		map_view_object_marker_get_coordinates(hMarker, &mapsCoord);
		maps_coordinates_get_latitude(mapsCoord, &lat);
		maps_coordinates_get_longitude(mapsCoord, &lng);
		maps_coordinates_destroy(mapsCoord);

		if (!HereUtils::IsValidCoord(lat, lng))
		{
			error = MAPS_ERROR_INVALID_PARAMETER;
			break;
		}

		hereMarker->SetPosition(GeoCoordinates(lat, lng));


		/* origin */
		Tizen::Maps::FloatPoint fpntOrigin(0.5, 1);
		hereMarker->SetMarkerOrigin(fpntOrigin);
	} while(0);

	return (here_error_e)ConvertToHereError(error);
}

here_error_e HereViewObjects::__updatePolyline(map_view_object_h hPolyline, GeoMapObjectPolyline *herePolyline)
{
	if (!hPolyline || !herePolyline)
		return HERE_ERROR_INVALID_PARAMETER;

 	int error = MAPS_ERROR_NONE;
	GeoCoordinateList coordList;
	unsigned char r, g, b, a;
	int nThickness;

	do {
		error = map_view_object_poly_foreach_point(hPolyline, __foreachForCoordinates, &coordList);
		if (error != MAPS_ERROR_NONE) break;
		herePolyline->SetPath(coordList);

		error = map_view_object_polyline_get_color(hPolyline, &r, &g, &b, &a);
		if (error != MAPS_ERROR_NONE) break;
		herePolyline->SetStrokeColor(Color(r, g, b, a));

		error = map_view_object_polyline_get_width(hPolyline, &nThickness);
		if (error != MAPS_ERROR_NONE) break;
		herePolyline->SetStrokeThickness(nThickness);
	} while(0);

	return (here_error_e)ConvertToHereError(error);
}

here_error_e HereViewObjects::__updatePolygon(map_view_object_h hPolygon, GeoMapObjectPolygon *herePolygon)
{
	if (!hPolygon || !herePolygon)
		return HERE_ERROR_INVALID_PARAMETER;

 	int error = MAPS_ERROR_NONE;
	GeoCoordinateList coordList;
	unsigned char r, g, b, a;

	do {
		error = map_view_object_poly_foreach_point(hPolygon, __foreachForCoordinates, &coordList);
		if (error != MAPS_ERROR_NONE) break;
		herePolygon->SetPath(coordList);

		error = map_view_object_polygon_get_fill_color(hPolygon, &r, &g, &b, &a);
		if (error != MAPS_ERROR_NONE) break;
		herePolygon->SetFillColor(Color(r, g, b, a));
	} while(0);

	return (here_error_e)ConvertToHereError(error);
}

here_error_e HereViewObjects::__updateRoute(map_view_object_h hRoute)
{
#ifdef TIZEN_3_0_NEXT_MS
	if (!hRoute) return HERE_ERROR_INVALID_PARAMETER;

	VisualObjects::iterator it;

	if ((it = __currentObjects.find(hRoute)) != __currentObjects.end())
	{
		maps_route_h route = NULL;
		int ret = map_object_route_get_content(hRoute, &route);
		if (ret !=  MAPS_ERROR_NONE || !route)
			return HERE_ERROR_NONE;

		GeoCoordinateList coordList;
		GeoMapObjectPolyline *polyline_path = NULL, *polyline_seg = NULL;

		if (it->second->GetType() == GeoMapObject::GMO_Polyline)
		{
			if (!polyline_path)
			{
				MAPS_LOGD("Route Path");
				polyline_path = (GeoMapObjectPolyline*)it->second;
 				maps_route_foreach_path(route, __foreachForCoordinates, &coordList);
				polyline_path->SetPath(coordList);
				polyline_path->SetStrokeColor(Tizen::Maps::Color(255, 0, 0, 255));
				polyline_path->SetStrokeThickness(3);
			}
			else if (!polyline_seg)
			{
				MAPS_LOGD("Route Segments");
				polyline_seg = (GeoMapObjectPolyline*)it->second;
 				maps_route_foreach_path(route, __foreachForCoordinates, &coordList);
				polyline_seg->SetPath(coordList);
				polyline_seg->SetStrokeColor(Tizen::Maps::Color(0, 255, 0, 255));
				polyline_seg->SetStrokeThickness(3);
			}
		}
		else if (it->second->GetType() == GeoMapObject::GMO_Marker)
		{
			// to implement
		}
		maps_route_destroy(route);
	}

#endif /* TIZEN_3_0_NEXT_MS */
	return HERE_ERROR_NONE;
}

bool HereViewObjects::__foreachForCoordinates(int index, int total, maps_coordinates_h point, void *user_data)
{
	if (!point || !user_data)
		return false;

	if (!HereUtils::IsValid(*(maps_coordinates_s*)point))
	{
		maps_coordinates_destroy(point);
		return false;
	}


	int error;
	double lat = 0.0, lng = 0.0;

	do {
		error = maps_coordinates_get_latitude(point, &lat);
		if (error != MAPS_ERROR_NONE) break;

		error = maps_coordinates_get_longitude(point, &lng);
		if (error != MAPS_ERROR_NONE) break;
	} while(0);

	maps_coordinates_destroy(point);
	if (error != MAPS_ERROR_NONE) return false;

	MAPS_LOGD("[%d/%d] %f,%f", index+1, total, lat, lng);

	GeoCoordinateList *coordList = (GeoCoordinateList*)user_data;
	coordList->push_back(GeoCoordinates(lat, lng));
	return true;
}

HERE_PLUGIN_END_NAMESPACE
