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
#include <map_view.h>

//map engine header
#include <maps/GeoTiledMap.h>
#include <maps/GeoMapObjectMarker.h>
#include <maps/GeoMapObjectPolygon.h>
#include <maps/GeoMapObjectPolyline.h>


HERE_PLUGIN_BEGIN_NAMESPACE

using namespace HERE_MAPS_NAMESPACE_PREFIX;


typedef std::map<map_object_h, const GeoMapObject*> VisualObjects;
typedef std::pair<map_object_h, const map_object_operation_e> PendingObject;
typedef std::deque<PendingObject> PendingObjects;
// to remove // typedef std::deque<map_object_h> UpdatedObjects;

class HereViewObjects
{
public:
	HereViewObjects();
	virtual ~HereViewObjects();

	void set(GeoTiledMap *map, Evas *evas);
	// to remove // void update(UpdatedObjects objects);

	here_error_e add(map_object_h hObj);
	here_error_e move(map_object_h hObj);
	here_error_e update(map_object_h hObj);
	here_error_e setVisible(map_object_h hObj);
	here_error_e remove(map_object_h hObj);
	here_error_e removeAll();

private:
	here_error_e __add(map_object_h hObj);
	here_error_e __remove(map_object_h hObj);
	here_error_e __update(map_object_h hObj, GeoMapObject *hereObject);
	here_error_e __updateMarker(map_object_h hMarker, GeoMapObjectMarker *hereMarker);
	here_error_e __updatePolygon(map_object_h hPolygon, GeoMapObjectPolygon *herePolygon);
	here_error_e __updatePolyline(map_object_h hPolyline, GeoMapObjectPolyline *herePolyline);
	here_error_e __updateRoute(map_object_h hRoute);
	here_error_e __setVisible(map_object_h hObj, bool bVisible);

	static bool __foreachForCoordinates(int index, maps_coordinates_h coordinates, void *user_data);
	static bool __foreachForAddingGroupObjects(int index, int total, map_object_h object, void *user_data);
	static bool __foreachForRemovingGroupObjects(int index, int total, map_object_h object, void *user_data);
	static bool __foreachForUpdatingGroupObjects(int index, int total, map_object_h object, void *user_data);
	static bool __foreachForSettingVisibleGroupObjects(int index, int total, map_object_h object, void *user_data);

	VisualObjects __currentObjects;
	GeoTiledMap *__map;
	Evas *__evas;
	pthread_mutex_t __mutex;
};

HERE_PLUGIN_END_NAMESPACE

#endif /* HERE_VIEW_OBJECTS_H */

