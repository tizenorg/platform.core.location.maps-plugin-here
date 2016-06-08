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

#include "here_view.h"
#include <Elementary.h>

using namespace HERE_PLUGIN_NAMESPACE_PREFIX;

static const char SIG_LOADED[] = "loaded";


HERE_PLUGIN_BEGIN_NAMESPACE

HereView::HereView()
{
	__map = NULL;

	__img = NULL;
	__ctx = NULL;
	__sfc = NULL;
	__cfg = NULL;
	__gl = NULL;
	__api = NULL;

	__isInitialized = false;

	__x = 0;
	__y = 0;
	__w = 0;
	__h = 0;

	__lat = 0.;
	__lng = 0.;
	__zoom = 0.;
	__angle = 0.;

	__idler = NULL;
	__redraw = false;
	__readyCb = NULL;
}

HereView::~HereView()
{
}

here_error_e HereView::init(maps_view_h view, maps_plugin_map_view_ready_cb callback)
{
	if (!view)
		return HERE_ERROR_INVALID_PARAMETER;

	__idler = ecore_idler_add(__idlerCb, (void*)view);

	here_error_e error = HERE_ERROR_NONE;
	int error2 = MAPS_ERROR_NONE;

	do {
		error2 = maps_view_get_viewport(view, &__img);
		if (error2 != MAPS_ERROR_NONE) break;

		error2 = maps_view_get_screen_location(view, &__x, &__y, &__w, &__h);
		if (error2 != MAPS_ERROR_NONE) break;

		error = initOpenGL();
		if (error != HERE_ERROR_NONE) break;

		error = initOpenGLSurface(view);
		if (error != HERE_ERROR_NONE) break;

		error = initMap(view, callback);
	} while (0);

	if (error == HERE_ERROR_NONE && error2 != MAPS_ERROR_NONE)
		error = (here_error_e)ConvertToHereError(error2);

	return error;
}

here_error_e HereView::initOpenGL()
{
	__cfg = evas_gl_config_new();
	if (!__cfg) {
		MAPS_LOGE("evas_gl_config_new() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	__cfg->color_format = EVAS_GL_RGBA_8888;    // Surface Color Format
	__cfg->depth_bits   = EVAS_GL_DEPTH_NONE;   // Surface Depth Format
	__cfg->stencil_bits = EVAS_GL_STENCIL_NONE; // Surface Stencil Format
	__cfg->options_bits = EVAS_GL_OPTIONS_DIRECT; // Configuration options (here, no extra options)

	__gl = evas_gl_new(evas_object_evas_get(__img));
	if (!__gl) {
		MAPS_LOGE("evas_gl_new() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	__api = evas_gl_api_get(__gl);
	if (!__api) {
		MAPS_LOGE("evas_gl_api_get() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	__ctx = evas_gl_context_create(__gl, NULL);
	if (!__ctx) {
		MAPS_LOGE("evas_gl_context_create() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	return HERE_ERROR_NONE;
}

here_error_e HereView::initOpenGLSurface(maps_view_h view)
{
	if (!view || !__gl || !__cfg || !__img || !__ctx)
		return HERE_ERROR_INVALID_PARAMETER;

	evas_object_image_pixels_get_callback_set(__img, NULL, NULL);

	if (__sfc) {
		evas_object_image_native_surface_set(__img, NULL);
		evas_gl_surface_destroy(__gl, __sfc);
	}

	__w = MAX(__w, 1);
	__h = MAX(__h, 1);

	evas_object_image_size_set(__img, __w, __h);

	Evas_Native_Surface ns;
	__sfc = evas_gl_surface_create(__gl, __cfg, __w, __h);
	if (!__sfc) {
		MAPS_LOGE("evas_gl_surface_create() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	if (!evas_gl_native_surface_get(__gl, __sfc, &ns)) {
		evas_gl_make_current(__gl, NULL, NULL);
		evas_gl_surface_destroy(__gl, __sfc);
		__sfc = NULL;
		MAPS_LOGE("evas_gl_native_surface_get() faile");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	evas_object_image_native_surface_set(__img, &ns);
	evas_object_image_pixels_get_callback_set(__img, __pixelGetCb, view);
	__isInitialized = true;

	return HERE_ERROR_NONE;
}

here_error_e HereView::initMap(maps_view_h view,  maps_plugin_map_view_ready_cb callback)
{
	if (!view)
		return HERE_ERROR_INVALID_PARAMETER;

	__map = new (std::nothrow) GeoTiledMap();
	if (!__map)
		return HERE_ERROR_OUT_OF_MEMORY;

	__readyCb = callback;

	__map->SetReadyMapSignal((GeoTiledMap::ReadyMapSignalFunctor)__readyMapCb, (void *)view);
	__map->SetEvasGlApi(__api);
	__map->SetMapSize(Dimension(__w, __h));

	__visualObjects.set(__map, evas_object_evas_get(__img));

	return HERE_ERROR_NONE;
}

here_error_e HereView::close(maps_view_h view)
{
	if (!view)
		return HERE_ERROR_INVALID_PARAMETER;

	__isInitialized = false;

	__visualObjects.set(NULL, NULL);

	if (__img)
		evas_object_image_pixels_get_callback_set(__img, NULL, NULL);

	if (__idler)
		ecore_idler_del(__idler);

	if (__map) {
		__map->SetUpdateMapSignal(NULL);
		delete __map;
	}

	/* clear Open GL */
	if (__gl) {
		if (__sfc && __ctx)
			evas_gl_make_current(__gl, __sfc, __ctx);

		if (__sfc)
			evas_object_image_native_surface_set(__img, NULL);
			evas_gl_surface_destroy(__gl, __sfc);

		if (__ctx)
			evas_gl_context_destroy(__gl, __ctx);

		evas_gl_free(__gl);
		__gl = NULL;
	}

	if (__cfg)
		evas_gl_config_free(__cfg);

	return HERE_ERROR_NONE;
}

void HereView::__readyMapCb(void *data)
{
	HereView *hv = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle((maps_view_h)data, (void**)&hv);
	if (maps_error != MAPS_ERROR_NONE || !hv) return;

	if (hv->__readyCb)
		hv->__readyCb(data);
}

void HereView::__pixelGetCb(void *data, Evas_Object *obj)
{
	HereView *hv = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(data, (void**)&hv);
	if (maps_error != MAPS_ERROR_NONE || !hv ||
		!hv->__map || !hv->__gl || !hv->__sfc || !hv->__ctx) return;

	evas_gl_make_current(hv->__gl, hv->__sfc, hv->__ctx);
	hv->__map->PaintMap(hv->__w, hv->__h);
}

void HereView::__renderingCb(void *data)
{
	if (!data) return;
	evas_object_image_pixels_dirty_set((Evas_Object*)data, EINA_TRUE);
}

void HereView::setMapType(maps_view_h view)
{
	if (!view)
		return;

	/* When the theme is changed, clear cache */
	maps_view_type_e map_type;
	maps_view_get_type(view, &map_type);

	bool buildings_enabled = false;
	maps_view_get_buildings_enabled(view, &buildings_enabled);

	bool traffic_enabled = false;
	maps_view_get_traffic_enabled(view, &traffic_enabled);

	bool public_transit_enabled = false;
	maps_view_get_public_transit_enabled(view, &public_transit_enabled);

	GeoTiledMap::MapType hereMapType = HereUtils::Convert(map_type, buildings_enabled,
						traffic_enabled, public_transit_enabled);

	if (hereMapType != __map->GetMapType())
	{
		MAPS_LOGD("Clear cache, because map type is changed.");
		__map->ClearCache();
#ifdef TIZEN_SUPPORT_TILE_FILE_CACHE
		__map->ClearTileFileCache();
#endif
		__map->SetMapType(hereMapType);
	}
}

here_error_e HereView::renderMap(maps_view_h view, const maps_coordinates_h coord, double zoom, double angle)
{
	if (!view || !coord)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map || !__api)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	/* set map type */
	setMapType(view);

	/* resize window */
	int x, y, w, h;
	maps_view_get_screen_location(view, &x, &y, &w, &h);
	__w = MAX(__w, 1);
	__h = MAX(__h, 1);

	if (x != __x || y != __y || w != __w || h != __h) {
		__x = x;
		__y = y;
		__w = w;
		__h = h;

		__api->glViewport(0, 0, __w, __h);
		__map->SetMapSize(Dimension(__w, __h));
		initOpenGLSurface(view);
	}

	/* callback */
	GeoTiledMap::UpdateMapSignalFunctor callback = std::tr1::bind(&__renderingCb, __img);
	__map->SetUpdateMapSignal(callback);

	/* zoom level */
	if (__map->GetZoomLevel() != zoom) {
		__zoom = zoom;
		__map->SetZoomLevel(zoom, false);
	}

	/* angle */
	if (__angle != angle) {
		__angle = angle;
		__map->SetAngle(angle);
	}

	/* center */
	double lat, lng;
	maps_coordinates_get_latitude(coord, &lat);
	maps_coordinates_get_longitude(coord, &lng);

	GeoCoordinates geoCoord(lat, lng);
	__lat = lat;
	__lng = lng;
	__map->SetCenter(geoCoord);

	return HERE_ERROR_NONE;
}

here_error_e HereView::moveCenter(maps_view_h view, int delta_x, int delta_y)
{
	if (!view)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (delta_x == 0 && delta_y == 0)
		return HERE_ERROR_NONE;

	__map->Pan(delta_x, delta_y);

	return HERE_ERROR_NONE;
}

here_error_e HereView::getCenter(maps_view_h view, maps_coordinates_h *center)
{
	if (!view || !center)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	GeoCoordinates geoCoord = __map->GetCenter();
	if (*center == NULL) {
		maps_coordinates_create(geoCoord.GetLatitude(), geoCoord.GetLongitude(), center);
	} else {
		maps_coordinates_set_latitude(*center, geoCoord.GetLatitude());
		maps_coordinates_set_longitude(*center, geoCoord.GetLongitude());
	}

	return HERE_ERROR_NONE;
}

here_error_e HereView::setScalebarEnabled(maps_view_h view, bool enable)
{
	if (!view)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	__map->SetScalebar(enable);

	return HERE_ERROR_NONE;
}

here_error_e HereView::getScalebarEnabled(maps_view_h view, bool *enabled)
{
	if (!view || !enabled)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	*enabled = __map->GetScalebar();
	return HERE_ERROR_NONE;
}

here_error_e HereView::convertScreenToGeolocation(maps_view_h view, int x, int y, maps_coordinates_h *coord)
{
	if (!view || !coord)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	Tizen::Maps::Point point(x, y);
	GeoCoordinates geoCoord = __map->ScreenPositionToCoordinate(point);
	double lat = geoCoord.GetLatitude();
	double lng = geoCoord.GetLongitude();

	int error = maps_coordinates_create(lat, lng, coord);
	if (error != MAPS_ERROR_NONE)
		return (here_error_e)ConvertToHereError(error);

	return HERE_ERROR_NONE;
}

here_error_e HereView::convertGeolocationToScreen(maps_view_h view, const maps_coordinates_h coord, int *x, int *y)
{
	if (!view || !x || !y)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	double lat, lng;
	maps_coordinates_get_latitude(coord, &lat);
	maps_coordinates_get_longitude(coord, &lng);
	GeoCoordinates geoCoord(lat, lng);
	Tizen::Maps::Point point = __map->CoordinateToScreenPosition(geoCoord);

	*x = point.x;
	*y = point.y;

	return HERE_ERROR_NONE;
}

here_error_e HereView::getMinZoomLevel(maps_view_h view, int *zoom)
{
	if (!view || !zoom)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	*zoom = (int)__map->GetMinimumZoomLevel();

	return HERE_ERROR_NONE;
}

here_error_e HereView::getMaxZoomLevel(maps_view_h view, int *zoom)
{
	if (!view || !zoom)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	*zoom = (int)__map->GetMaximumZoomLevel();

	return HERE_ERROR_NONE;
}

here_error_e HereView::onViewObject(maps_view_h view, const maps_view_object_h object, maps_view_object_operation_e operation)
{
	if (!view || !object ||
		operation < MAPS_VIEW_OBJECT_ADD || operation > MAPS_VIEW_OBJECT_REMOVE)
		return HERE_ERROR_INVALID_PARAMETER;

	if (!__isInitialized || !__map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (__map->GetRootPixmap())
		__processViewObject(view, object, operation);
	else
		__pendingObjects.push_back(std::make_pair(object, operation));

	return HERE_ERROR_NONE;
}

Eina_Bool HereView::__idlerCb(void *data)
{
	HereView *hv = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(data, (void**)&hv);
	if (maps_error != MAPS_ERROR_NONE || !hv) return true;
	if (!hv->__map || !hv->__map->GetRootPixmap()) return true;

	while (hv->__pendingObjects.size()) {
		PendingObject pending = hv->__pendingObjects.front();
		hv->__pendingObjects.pop_front();
		maps_view_object_h object = pending.first;
		maps_view_object_operation_e operation = pending.second;

		__processViewObject(data, object, operation);
	}
	return true;
}

void HereView::__processViewObject(maps_view_h view, const maps_view_object_h object, maps_view_object_operation_e operation)
{
	HereView *hv = NULL;
	int maps_error = maps_view_get_maps_plugin_view_handle(view, (void**)&hv);
	if (maps_error != MAPS_ERROR_NONE || !hv) return;

	maps_view_object_type_e type;
	maps_view_object_get_type(object, &type);

	if (type < MAPS_VIEW_OBJECT_POLYLINE || type > MAPS_VIEW_OBJECT_MARKER) return;
	if (operation < MAPS_VIEW_OBJECT_ADD || operation > MAPS_VIEW_OBJECT_REMOVE) return;

	const char *oper_str[20] = { "ADD", "SET_VISIBLE", "MOVE", "CHANGE", "REMOVE"};
	const char *type_str[20] = { "POLYLINE", "POLYGON", "MARKER", "ROUTE", "UNKNOWN"};

	MAPS_LOGD("type=%s, operation=%s, object=%p",
		(type >= MAPS_VIEW_OBJECT_POLYLINE && type <= MAPS_VIEW_OBJECT_MARKER) ? type_str[type] : "?",
		(operation >= MAPS_VIEW_OBJECT_ADD && operation <= MAPS_VIEW_OBJECT_REMOVE) ? oper_str[operation] : "?",
		object);

	switch(operation)
	{
	case MAPS_VIEW_OBJECT_ADD:				hv->__visualObjects.add(object); break;
	case MAPS_VIEW_OBJECT_SET_VISIBLE:		hv->__visualObjects.setVisible(object); break;
	case MAPS_VIEW_OBJECT_CHANGE:			hv->__visualObjects.update(object); break;
	case MAPS_VIEW_OBJECT_REMOVE:			hv->__visualObjects.remove(object); break;
	default:			break;
	}
}

HERE_PLUGIN_END_NAMESPACE
