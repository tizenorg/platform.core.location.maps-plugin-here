/* Copyright 2014 Samsung Electronics Co., Ltd All Rights Reserved
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

/**
 * @file	heremaps-uc-dbus.h
 * @brief	This file contains the internal definitions and structures related to heremaps-uc-dbus.
 */
#ifndef __UC_DBUS_H__
#define __UC_DBUS_H__

#include <gio/gio.h>
#include <tizen_error.h>
#include <dlog.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAPS_LOGD(fmt,args...)  LOGD(fmt, ##args)
#define MAPS_LOGW(fmt,args...)  LOGW(fmt, ##args)
#define MAPS_LOGI(fmt,args...)  LOGI(fmt, ##args)
#define MAPS_LOGE(fmt,args...)  LOGE(fmt, ##args)
#define MAPS_SECLOG(fmt,args...)  SECURE_LOGD(fmt, ##args)

#define MAPS_FUNC_ENTER     MAPS_LOGD("(%s) ENTER", __FUNCTION__);
#define MAPS_FUNC_EXIT      MAPS_LOGD("(%s) EXIT", __FUNCTION__);

/**
* @brief        Error and handle for heremaps-uc-dbus
*/
typedef enum {
    HEREMAPS_UC_DBUS_ERROR_NONE,
    HEREMAPS_UC_DBUS_ERROR_MEMORY,
    HEREMAPS_UC_DBUS_ERROR_CONNECTION,
    HEREMAPS_UC_DBUS_ERROR_DBUS_CALL,
} heremaps_uc_dbus_error_e;


/**
* @brief        API to launch heremaps-uc-launcher.
* @return       int
* @retval       HEREMAPS_UC_DBUS_ERROR_NONE if success
				HEREMAPS_UC_DBUS_ERROR_MEMORY if failure
				HEREMAPS_UC_DBUS_ERROR_CONNECTION if failure
                HEREMAPS_UC_DBUS_ERROR_DBUS_CALL if failure
*/
int heremaps_uc_dbus_launch_receiver();

#ifdef __cplusplus
}
#endif
#endif /* __UC_DBUS_H__ */
