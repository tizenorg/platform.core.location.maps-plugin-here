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
#include <map_view.h>

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


typedef struct _GLData
{
	Here::Maps::GeoTiledMap *map;

	Evas_Object     *img;
	Evas_GL_Context *ctx;
	Evas_GL_Surface *sfc;
	Evas_GL_Config  *cfg;
	Evas_GL         *gl;
	Evas_GL_API     *api;

	bool isInitialized;

	int x, y, w, h;
	double lat, lng, zoom, angle;

	map_view_h hView;

	// to remove // UpdatedObjects updatedObjects;
	HereViewObjects visualObjects;
	PendingObjects pendingObjects;
	Ecore_Idler *idler;
	bool redraw;
} GLData;


class HereView
: public HereBase
{
public:
	HereView(void *pCbFunc, void *pUserData, int nReqId);
	~HereView();

	here_error_e Init(map_view_h hView);
	static here_error_e Close();
	here_error_e RenderMap(const maps_coordinates_h mapsCoord, const double dZoom, const double dAngle);
	here_error_e RenderMapByArea(const maps_area_h hArea, const double dZoom, const double dAngle);
	static here_error_e DrawMap(Evas* pCanvas, const int x, const int y, const int nWidth, const int nHeight);
	here_error_e MoveCenter(const int delta_x, const int delta_y);
	here_error_e GetCenter(maps_coordinates_h *center);
	here_error_e ScreenToGeography(const int x, const int y, maps_coordinates_h *mapsCoord);
	here_error_e GeographyToScreen(const maps_coordinates_h mapsCoord, int *x, int *y);

	static here_error_e GetMinZoomLevel(int *nMinZoomLevel);
	static here_error_e GetMaxZoomLevel(int *nMaxZoomLevel);
	static here_error_e OnViewObject(const map_object_h object, const map_object_operation_e operation);

	here_error_e AddObject(map_object_h obj);
	static void RenderingCb(void *data);
	static bool foreachObject(int index, int total, map_object_h object, void *user_data);
	static GLData* GetImplHandler();

private:

	here_error_e InitOpenGL(GLData *gld);
	here_error_e InitOpenGLSurface(GLData *gld);
	here_error_e InitMap(GLData *gld);
	static Eina_Bool __idlerCb(void *data);
	static void __renderingCb(void *data);
	static void __pixelGetCb(void *data, Evas_Object *obj);
	static void __processViewObject(const map_object_h object, const map_object_operation_e operation);

	static GLData *m_pImpl;

};

HERE_PLUGIN_END_NAMESPACE

#endif
