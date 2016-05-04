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

HereView::HereView(void *pCbFunc, void *pUserData, int nReqId)
{
	m_pCbFunc = pCbFunc;
	m_pUserData = pUserData;
	m_nReqId = nReqId;
}

HereView::~HereView()
{
}

here_error_e HereView::Init(maps_view_h hView, maps_plugin_map_view_ready_cb pCbFunc)
{
	GLData *m_pImpl = NULL;

	if (!hView)
		return HERE_ERROR_INVALID_PARAMETER;

	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl)
	{
		m_pImpl = new (std::nothrow) GLData();

		if (!m_pImpl)
			return HERE_ERROR_INVALID_PARAMETER;

		maps_view_set_maps_plugin_view_handle(hView, (void *)m_pImpl);

		m_pImpl->idler = ecore_idler_add(__idlerCb, (void*)hView);
		m_pImpl->readyCb = NULL;
	} else
		return HERE_ERROR_INVALID_OPERATION;

	here_error_e error = HERE_ERROR_NONE;
	int error2 = MAPS_ERROR_NONE;

	do {
		error2 = maps_view_get_viewport(hView, &m_pImpl->img);
		if (error2 != MAPS_ERROR_NONE) break;

		error2 = maps_view_get_screen_location(hView, &m_pImpl->x, &m_pImpl->y, &m_pImpl->w, &m_pImpl->h);
		if (error2 != MAPS_ERROR_NONE) break;

		error = InitOpenGL(m_pImpl);
		if (error != HERE_ERROR_NONE) break;

		error = InitOpenGLSurface(hView);
		if (error != HERE_ERROR_NONE) break;

		error = InitMap(hView, m_pImpl, pCbFunc);
	} while(0);

	if (error == HERE_ERROR_NONE && error2 != MAPS_ERROR_NONE)
		error = (here_error_e)ConvertToHereError(error2);

	return error;
}

here_error_e HereView::InitOpenGL(GLData *gld)
{
	if (!gld)
		return HERE_ERROR_INVALID_PARAMETER;


	gld->cfg = evas_gl_config_new();
	if (!gld->cfg)
	{
		MAPS_LOGE("evas_gl_config_new() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	gld->cfg->color_format = EVAS_GL_RGBA_8888;    // Surface Color Format
	gld->cfg->depth_bits   = EVAS_GL_DEPTH_NONE;   // Surface Depth Format
	gld->cfg->stencil_bits = EVAS_GL_STENCIL_NONE; // Surface Stencil Format
	gld->cfg->options_bits = EVAS_GL_OPTIONS_DIRECT; // Configuration options (here, no extra options)

	gld->gl = evas_gl_new(evas_object_evas_get(gld->img));
	if (!gld->gl)
	{
		MAPS_LOGE("evas_gl_new() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	gld->api = evas_gl_api_get(gld->gl);
	if (!gld->api)
	{
		MAPS_LOGE("evas_gl_api_get() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	gld->ctx = evas_gl_context_create(gld->gl, NULL);
	if (!gld->ctx)
	{
		MAPS_LOGE("evas_gl_context_create() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	return HERE_ERROR_NONE;
}

here_error_e HereView::InitOpenGLSurface(maps_view_h hView)
{
	if (!hView)
		return HERE_ERROR_INVALID_PARAMETER;

	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->gl || !m_pImpl->cfg || !m_pImpl->img || !m_pImpl->ctx)
		return HERE_ERROR_INVALID_PARAMETER;

	evas_object_image_pixels_get_callback_set(m_pImpl->img, NULL, NULL);

	if (m_pImpl->sfc)
	{
		evas_object_image_native_surface_set(m_pImpl->img, NULL);
		evas_gl_surface_destroy(m_pImpl->gl, m_pImpl->sfc);
	}

	m_pImpl->w = MAX(m_pImpl->w, 1);
	m_pImpl->h = MAX(m_pImpl->h, 1);

	evas_object_image_size_set(m_pImpl->img, m_pImpl->w, m_pImpl->h);

	Evas_Native_Surface ns;
	m_pImpl->sfc = evas_gl_surface_create(m_pImpl->gl, m_pImpl->cfg, m_pImpl->w, m_pImpl->h);
	if (!m_pImpl->sfc)
	{
		MAPS_LOGE("evas_gl_surface_create() failed");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	if (!evas_gl_native_surface_get(m_pImpl->gl, m_pImpl->sfc, &ns))
	{
		evas_gl_make_current(m_pImpl->gl, NULL, NULL);
		evas_gl_surface_destroy(m_pImpl->gl, m_pImpl->sfc);
		m_pImpl->sfc = NULL;
		MAPS_LOGE("evas_gl_native_surface_get() faile");
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	}

	evas_object_image_native_surface_set(m_pImpl->img, &ns);

	evas_object_image_pixels_get_callback_set(m_pImpl->img, __pixelGetCb, hView);

	m_pImpl->isInitialized = true;
	//MAPS_LOGD("initializing is Done!!!");

	return HERE_ERROR_NONE;
}

here_error_e HereView::InitMap(maps_view_h hView, GLData *gld, maps_plugin_map_view_ready_cb pCbFunc)
{
	if (!hView || !gld)
		return HERE_ERROR_INVALID_PARAMETER;

	gld->map = new (std::nothrow) GeoTiledMap();

	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!gld->map)
		return HERE_ERROR_OUT_OF_MEMORY;

	gld->readyCb = pCbFunc;

	gld->map->SetReadyMapSignal((GeoTiledMap::ReadyMapSignalFunctor)__readyCb, (void *)hView);

	gld->map->SetEvasGlApi(gld->api);

	MAPS_LOGD("gld->api=%p, m_pImpl->api=%p", gld->api, m_pImpl->api);

	gld->map->SetMapSize(Dimension(gld->w,gld->h));

	//gld->map->SetUpdateMapSignal(RenderingCb, this);

	m_pImpl->visualObjects.set(gld->map, evas_object_evas_get(gld->img));

	return HERE_ERROR_NONE;
}

here_error_e HereView::Close(maps_view_h hView)
{
	if (!hView)
		return HERE_ERROR_INVALID_PARAMETER;

	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl)
		return HERE_ERROR_INVALID_OPERATION;

	if (m_pImpl)
	{
		m_pImpl->isInitialized = false;

		if (m_pImpl->map)
		{
			m_pImpl->map->SetUpdateMapSignal(NULL);
		}

		m_pImpl->visualObjects.set(NULL, NULL);

		if (m_pImpl->img)
		{
			evas_object_image_pixels_get_callback_set(m_pImpl->img, NULL, NULL);
		}

		if (m_pImpl->idler)
		{
			ecore_idler_del(m_pImpl->idler);
			m_pImpl->idler = NULL;
		}

		if (m_pImpl->map)
		{
			m_pImpl->map->SetUpdateMapSignal(NULL);
			delete m_pImpl->map;
			m_pImpl->map = NULL;
		}

		if (m_pImpl->gl)
		{
			evas_gl_make_current(m_pImpl->gl, m_pImpl->sfc, m_pImpl->ctx);

			if (m_pImpl->sfc)
			{
				evas_object_image_native_surface_set(m_pImpl->img, NULL);
				evas_gl_surface_destroy(m_pImpl->gl, m_pImpl->sfc);
				m_pImpl->sfc = NULL;
			}

			if (m_pImpl->ctx)
			{
				evas_gl_context_destroy(m_pImpl->gl, m_pImpl->ctx);
				m_pImpl->ctx = NULL;
			}

			evas_gl_free(m_pImpl->gl);
			m_pImpl->gl = NULL;
		}

		if (m_pImpl->cfg)
		{
			evas_gl_config_free(m_pImpl->cfg);
			m_pImpl->cfg = NULL;
		}

		delete m_pImpl;
		m_pImpl = NULL;
	}

	return HERE_ERROR_NONE;
}

void HereView::__readyCb(void *data)
{
	if (!data)
		return;

	maps_view_h hView = (maps_view_h)data;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (m_pImpl->readyCb)
		m_pImpl->readyCb(hView);
}

void HereView::__pixelGetCb(void *data, Evas_Object *obj)
{
	if (!data)
		return;

	maps_view_h hView = (maps_view_h)data;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->map) return;
	if (!m_pImpl->gl || !m_pImpl->sfc || !m_pImpl->ctx) return;

	evas_gl_make_current(m_pImpl->gl, m_pImpl->sfc, m_pImpl->ctx);
	m_pImpl->map->PaintMap(m_pImpl->w, m_pImpl->h);
}

void HereView::__renderingCb(void *data)
{
	if (!data) return;
	evas_object_image_pixels_dirty_set((Evas_Object*)data, EINA_TRUE);
}

void HereView::__setMapType(maps_view_h hView)
{
	if (!hView)
		return;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	/* When the theme is changed, clear cache */
	maps_view_type_e map_type;
	maps_view_get_type(hView, &map_type);

	bool buildings_enabled = false;
	maps_view_get_buildings_enabled(hView, &buildings_enabled);

	bool traffic_enabled = false;
	maps_view_get_traffic_enabled(hView, &traffic_enabled);

	bool public_transit_enabled = false;

	GeoTiledMap::MapType hereMapType = HereUtils::Convert(map_type, buildings_enabled,
						traffic_enabled, public_transit_enabled);

	if (hereMapType != m_pImpl->map->GetMapType())
	{
		MAPS_LOGD("Clear cache, because map type is changed.");
		m_pImpl->map->ClearCache();
#ifdef TIZEN_SUPPORT_TILE_FILE_CACHE
		m_pImpl->map->ClearTileFileCache();
#endif
		m_pImpl->map->SetMapType(hereMapType);
	}
}

here_error_e HereView::RenderMap(maps_view_h hView, const maps_coordinates_h mapsCoord, double dZoom, double dAngle)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map || !m_pImpl->api)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (!mapsCoord)
		return HERE_ERROR_INVALID_PARAMETER;

	/* set map type */
	__setMapType(hView);

	/* resize window */
	int x, y, w, h;
	maps_view_get_screen_location(hView, &x, &y, &w, &h);
	m_pImpl->w = MAX(m_pImpl->w, 1);
	m_pImpl->h = MAX(m_pImpl->h, 1);

	if (x != m_pImpl->x || y != m_pImpl->y || w != m_pImpl->w || h != m_pImpl->h)
	{
		m_pImpl->x = x;
		m_pImpl->y = y;
		m_pImpl->w = w;
		m_pImpl->h = h;

		m_pImpl->api->glViewport(0, 0, m_pImpl->w, m_pImpl->h);
		m_pImpl->map->SetMapSize(Dimension(m_pImpl->w,m_pImpl->h));
		InitOpenGLSurface(hView);
	}

	/* callback */
	GeoTiledMap::UpdateMapSignalFunctor callback = std::tr1::bind(&__renderingCb, m_pImpl->img);
	m_pImpl->map->SetUpdateMapSignal(callback);

	/* zoom level */
	if (m_pImpl->map->GetZoomLevel() != dZoom)
	{
		m_pImpl->zoom = dZoom;
		m_pImpl->map->SetZoomLevel(dZoom, false);
	}

	/* angle */
	if (m_pImpl->angle != dAngle) {
		m_pImpl->angle = dAngle;
		m_pImpl->map->SetAngle(dAngle);
	}

	/* center */
	double lat, lng;
	maps_coordinates_get_latitude(mapsCoord, &lat);
	maps_coordinates_get_longitude(mapsCoord, &lng);

	GeoCoordinates geoCoord(lat, lng);
	m_pImpl->lat = lat;
	m_pImpl->lng = lng;
	m_pImpl->map->SetCenter(geoCoord);

	return HERE_ERROR_NONE;
}

here_error_e HereView::RenderMapByArea(maps_view_h hView, const maps_area_h hArea, double dZoom, double dAngle)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map || !m_pImpl->map->GetRootPixmap() || !m_pImpl->api)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (!hArea)
		return HERE_ERROR_INVALID_PARAMETER;

	return HERE_ERROR_NONE;
}

here_error_e HereView::MoveCenter(maps_view_h hView, int delta_x, int delta_y)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map || !m_pImpl->map->GetRootPixmap() || !m_pImpl->api)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (delta_x == 0 && delta_y == 0)
		return HERE_ERROR_NONE;

	m_pImpl->map->Pan(delta_x, delta_y);

	return HERE_ERROR_NONE;
}

here_error_e HereView::SetScalebar(maps_view_h hView, bool enable)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	m_pImpl->map->SetScalebar(enable);

	return HERE_ERROR_NONE;
}

here_error_e HereView::GetScalebar(maps_view_h hView, bool *enabled)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map || !enabled)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	*enabled = m_pImpl->map->GetScalebar();
	return HERE_ERROR_NONE;
}

here_error_e HereView::DrawMap(maps_view_h hView, Evas* pCanvas, int x, int y, int nWidth, int nHeight)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map || !m_pImpl->map->GetRootPixmap() || !m_pImpl->api)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (!pCanvas || nWidth <= 0 || nHeight <= 0)
		return HERE_ERROR_INVALID_PARAMETER;

	if (m_pImpl->w <= 0 || m_pImpl->h <= 0)
		return HERE_ERROR_INVALID_PARAMETER;

	unsigned char* srcimg_data = (unsigned char*)malloc(m_pImpl->w*m_pImpl->h*4);
	if (!srcimg_data)
		return HERE_ERROR_OUT_OF_MEMORY;

	Evas_Object *dstimg = evas_object_image_filled_add(pCanvas);
	if (!dstimg)
	{
		g_free(srcimg_data);
		return HERE_ERROR_INVALID_OPERATION;
	}

	unsigned char *dstimg_data = (unsigned char *)evas_object_image_data_get(dstimg, EINA_TRUE);
	if (!dstimg_data)
	{
		g_free(srcimg_data);
		return HERE_ERROR_INVALID_OPERATION;
	}

	int w = nWidth;
	int h = nHeight;

	if (m_pImpl->w < w) w = m_pImpl->w;
	if (m_pImpl->h < h) h = m_pImpl->h;

	m_pImpl->api->glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, srcimg_data);

	try {
		for (int i = 0; i < h; i++)
			memcpy(dstimg_data+(i*w), srcimg_data+(i*m_pImpl->w+x), w*4);
	}
	catch (std::exception &e) {
		MAPS_LOGD("Exception caught: %s", e.what());
	}
	g_free(srcimg_data);

	return HERE_ERROR_NONE;
}

here_error_e HereView::GetCenter(maps_view_h hView, maps_coordinates_h *center)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!center)
		return HERE_ERROR_INVALID_PARAMETER;

	GeoCoordinates geoCoord = m_pImpl->map->GetCenter();

	if (*center == NULL)
	{
		maps_coordinates_create(geoCoord.GetLatitude(), geoCoord.GetLongitude(), center);
	}
	else
	{
		maps_coordinates_set_latitude(*center, geoCoord.GetLatitude());
		maps_coordinates_set_longitude(*center, geoCoord.GetLongitude());
	}

	return HERE_ERROR_NONE;
}

here_error_e HereView::ScreenToGeolocation(maps_view_h hView, int x, int y, maps_coordinates_h *mapsCoord)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (!mapsCoord)
		return HERE_ERROR_INVALID_PARAMETER;

	Tizen::Maps::Point mapsPoint(x, y);
	GeoCoordinates hereCoord = m_pImpl->map->ScreenPositionToCoordinate(mapsPoint);
	double lat = hereCoord.GetLatitude();
	double lng = hereCoord.GetLongitude();

#if 1
	int error = maps_coordinates_create(lat, lng, mapsCoord);
	if (error != MAPS_ERROR_NONE)
		return (here_error_e)ConvertToHereError(error);
#else
	maps_coordinates_h __mapsCoord;
	int error = maps_coordinates_create(lat, lng, &__mapsCoord);
	if (error != MAPS_ERROR_NONE)
		return (here_error_e)ConvertToHereError(error);

	if (*mapsCoord) {
		/* maps_coord is already allocated in heap memory */
		maps_coordinates_get_latitude(__mapsCoord, &lat);
		maps_coordinates_get_longitude(__mapsCoord, &lng);
		maps_coordinates_set_latitude(*mapsCoord, lat);
		maps_coordinates_set_longitude(*mapsCoord, lng);
	} else {
		/* maps_coord is not allocated yet */
		maps_coordinates_clone(__mapsCoord, mapsCoord);
	}
	maps_coordinates_destroy(__mapsCoord);
#endif

	return HERE_ERROR_NONE;
}

here_error_e HereView::GeolocationToScreen(maps_view_h hView, const maps_coordinates_h mapsCoord, int *x, int *y)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (!x || !y)
		return HERE_ERROR_INVALID_PARAMETER;

	double lat, lng;
	maps_coordinates_get_latitude(mapsCoord, &lat);
	maps_coordinates_get_longitude(mapsCoord, &lng);
	GeoCoordinates hereCoord(lat, lng);
	Tizen::Maps::Point mapsPoint = m_pImpl->map->CoordinateToScreenPosition(hereCoord);

	*x = mapsPoint.x;
	*y = mapsPoint.y;

	return HERE_ERROR_NONE;
}

here_error_e HereView::GetMinZoomLevel(maps_view_h hView, int *nMinZoomLevel)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (!nMinZoomLevel)
		return HERE_ERROR_INVALID_PARAMETER;

	*nMinZoomLevel = (int)m_pImpl->map->GetMinimumZoomLevel();

	return HERE_ERROR_NONE;
}

here_error_e HereView::GetMaxZoomLevel(maps_view_h hView, int *nMaxZoomLevel)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (!nMaxZoomLevel)
		return HERE_ERROR_INVALID_PARAMETER;

	*nMaxZoomLevel = (int)m_pImpl->map->GetMaximumZoomLevel();

	return HERE_ERROR_NONE;
}

here_error_e HereView::OnViewObject(maps_view_h hView, const maps_view_object_h object, maps_view_object_operation_e operation)
{
	if (!hView)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->isInitialized || !m_pImpl->map)
		return HERE_ERROR_SERVICE_NOT_AVAILABLE;

	if (!object || operation < MAPS_VIEW_OBJECT_ADD || operation > MAPS_VIEW_OBJECT_REMOVE)
		return HERE_ERROR_INVALID_PARAMETER;

	if (m_pImpl->map->GetRootPixmap())
		__processViewObject(hView, object, operation);
	else
		m_pImpl->pendingObjects.push_back(std::make_pair(object, operation));

	return HERE_ERROR_NONE;
}

Eina_Bool HereView::__idlerCb(void *data)
{
	if (!data) return false;
	maps_view_h hView = (maps_view_h)data;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

	if (!m_pImpl || !m_pImpl->map || !m_pImpl->map->GetRootPixmap()) return true;

	while (m_pImpl->pendingObjects.size())
	{
		PendingObject pending = m_pImpl->pendingObjects.front();
		m_pImpl->pendingObjects.pop_front();
		maps_view_object_h object = pending.first;
		maps_view_object_operation_e operation = pending.second;

		__processViewObject(hView, object, operation);
	}

	return true;
}

void HereView::__processViewObject(maps_view_h hView, const maps_view_object_h object, maps_view_object_operation_e operation)
{
	if (!hView)
		return;
	GLData *m_pImpl = NULL;
	maps_view_get_maps_plugin_view_handle(hView, (void **)&m_pImpl);

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
	case MAPS_VIEW_OBJECT_ADD:				m_pImpl->visualObjects.add(object); break;
	case MAPS_VIEW_OBJECT_SET_VISIBLE:		m_pImpl->visualObjects.setVisible(object); break;
	case MAPS_VIEW_OBJECT_CHANGE:			m_pImpl->visualObjects.update(object); break;
	case MAPS_VIEW_OBJECT_REMOVE:			m_pImpl->visualObjects.remove(object); break;
	default:			break;
	}
}

HERE_PLUGIN_END_NAMESPACE
