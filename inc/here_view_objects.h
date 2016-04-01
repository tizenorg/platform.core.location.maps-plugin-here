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

#ifndef HERE_VIEW_OBJECTS_H
#define HERE_VIEW_OBJECTS_H

#include <deque>

//plug-in header
#include "here_manager.h"
#include "here_base.h"

//maps-service header
#include <maps_service.h>
#include <maps_view.h>
#include <maps_view_object_plugin.h>

//map engine header
#include <maps/GeoTiledMap.h>
#include <maps/GeoMapObjectMarker.h>
#include <maps/GeoMapObjectPolygon.h>
#include <maps/GeoMapObjectPolyline.h>


HERE_PLUGIN_BEGIN_NAMESPACE

using namespace HERE_MAPS_NAMESPACE_PREFIX;


typedef std::map<maps_view_object_h, const GeoMapObject*> VisualObjects;
typedef std::pair<maps_view_object_h, const maps_view_object_operation_e> PendingObject;
typedef std::deque<PendingObject> PendingObjects;
// to remove // typedef std::deque<maps_view_object_h> UpdatedObjects;

class HereViewObjects
{
public:
	HereViewObjects();
	virtual ~HereViewObjects();

	void set(GeoTiledMap *map, Evas *evas);
	// to remove // void update(UpdatedObjects objects);

	here_error_e add(maps_view_object_h hObj);
	here_error_e move(maps_view_object_h hObj);
	here_error_e update(maps_view_object_h hObj);
	here_error_e setVisible(maps_view_object_h hObj);
	here_error_e remove(maps_view_object_h hObj);
	here_error_e removeAll();

private:
	here_error_e __add(maps_view_object_h hObj);
	here_error_e __remove(maps_view_object_h hObj);
	here_error_e __update(maps_view_object_h hObj, GeoMapObject *hereObject);
	here_error_e __updateMarker(maps_view_object_h hMarker, GeoMapObjectMarker *hereMarker);
	here_error_e __updatePolygon(maps_view_object_h hPolygon, GeoMapObjectPolygon *herePolygon);
	here_error_e __updatePolyline(maps_view_object_h hPolyline, GeoMapObjectPolyline *herePolyline);
	here_error_e __updateRoute(maps_view_object_h hRoute);
	here_error_e __setVisible(maps_view_object_h hObj, bool bVisible);

	static bool __foreachForCoordinates(int index, maps_coordinates_h coordinates, void *user_data);
	static bool __foreachForAddingGroupObjects(int index, int total, maps_view_object_h object, void *user_data);
	static bool __foreachForRemovingGroupObjects(int index, int total, maps_view_object_h object, void *user_data);
	static bool __foreachForUpdatingGroupObjects(int index, int total, maps_view_object_h object, void *user_data);
	static bool __foreachForSettingVisibleGroupObjects(int index, int total, maps_view_object_h object, void *user_data);

	bool __resizeMarker(maps_view_object_h hMarker, const int originWidth, const int originHeight,
						int *newWidth, int *newHeight, unsigned char **buffer);
	bool __resizeBitmap(unsigned char **curBmp, int curWidth, int curHeight, int newWidth, int newHeight);

	void __invalidate(maps_view_object_h hObj = NULL);

	VisualObjects __currentObjects;
	GeoTiledMap *__map;
	Evas *__evas;
	pthread_mutex_t __mutex;
};

HERE_PLUGIN_END_NAMESPACE

#endif /* HERE_VIEW_OBJECTS_H */

