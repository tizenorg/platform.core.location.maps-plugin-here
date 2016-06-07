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

#ifndef HERE_VIEW_H
#define HERE_VIEW_H

#include <deque>

//plug-in header
#include "here_manager.h"
#include "here_base.h"
#include "here_view_objects.h"

//maps-service header
#include <maps_service.h>
#include <maps_view.h>
#include <maps_view_plugin.h>

//map engine header
#include <maps/GeoTiledMap.h>
#include <Ecore.h>
#include <Ecore_Evas.h>
#include <graphic/Grp_Util.h>
#include <maps/GeoMapObjectMarker.h>
#include <maps/GeoMapObjectPolygon.h>
#include <maps/GeoMapObjectPolyline.h>

HERE_PLUGIN_BEGIN_NAMESPACE

using namespace HERE_MAPS_NAMESPACE_PREFIX;

class HereView
: public HereBase
{
public:
	HereView();
	~HereView();

	here_error_e Init(maps_view_h hView, maps_plugin_map_view_ready_cb pCbFunc);
	here_error_e Close(maps_view_h hView);
	here_error_e RenderMap(maps_view_h hView, const maps_coordinates_h mapsCoord, double dZoom, double dAngle);
	here_error_e RenderMapByArea(maps_view_h hView, const maps_area_h hArea, double dZoom, double dAngle);
	here_error_e DrawMap(maps_view_h hView, Evas* pCanvas, int x, int y, int nWidth, int nHeight);
	here_error_e MoveCenter(maps_view_h hView, int delta_x, int delta_y);
	here_error_e GetCenter(maps_view_h hView, maps_coordinates_h *center);
	here_error_e SetScalebar(maps_view_h hView, bool enable);
	here_error_e GetScalebar(maps_view_h hView, bool *enabled);
	here_error_e ScreenToGeolocation(maps_view_h hView, int x, int y, maps_coordinates_h *mapsCoord);
	here_error_e GeolocationToScreen(maps_view_h hView, const maps_coordinates_h mapsCoord, int *x, int *y);

	here_error_e GetMinZoomLevel(maps_view_h hView, int *nMinZoomLevel);
	here_error_e GetMaxZoomLevel(maps_view_h hView, int *nMaxZoomLevel);
	here_error_e OnViewObject(maps_view_h hView, const maps_view_object_h object, maps_view_object_operation_e operation);

private:
	here_error_e __initOpenGL();
	here_error_e __initOpenGLSurface(maps_view_h hView);
	here_error_e __initMap(maps_view_h hView, maps_plugin_map_view_ready_cb pCbFunc);
	static void __readyMapCb(maps_view_h hView);
	static Eina_Bool __idlerCb(void *data);
	static void __renderingCb(void *data);
	static void __pixelGetCb(void *data, Evas_Object *obj);
	static void __processViewObject(maps_view_h hView, const maps_view_object_h object, maps_view_object_operation_e operation);
	void __setMapType(maps_view_h hView);

private:
	Here::Maps::GeoTiledMap *__map;

	Evas_Object     *__img;
	Evas_GL_Context *__ctx;
	Evas_GL_Surface *__sfc;
	Evas_GL_Config  *__cfg;
	Evas_GL         *__gl;
	Evas_GL_API     *__api;

	bool __isInitialized;

	int __x, __y, __w, __h;
	double __lat, __lng, __zoom, __angle;

	HereViewObjects __visualObjects;
	PendingObjects __pendingObjects;
	Ecore_Idler *__idler;
	bool __redraw;

	maps_plugin_map_view_ready_cb __readyCb;
};

HERE_PLUGIN_END_NAMESPACE

#endif
