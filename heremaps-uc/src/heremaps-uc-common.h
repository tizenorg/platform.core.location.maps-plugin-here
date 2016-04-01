/*
 * heremaps-uc
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jongmun Woo <jongmun.woo@samsung.com>, Young-Ae Kang <youngae.kang@samsung.com>
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
 *
 */



#ifndef HEREMAPS_UC_COMMON_H_
#define HEREMAPS_UC_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <app.h>
#include <dlog.h>
#include <glib.h>
#include <vconf.h>
#include <vconf-internal-location-keys.h>
#ifndef Eina_Bool
#include <stdbool.h>
#endif
#include <Elementary.h>
#include <Elementary.h>
#include <libintl.h>
#include <stdio.h>
#include <string.h>
#include <efl_extension.h>
#include <system_info.h>

#if !defined(HEREMAPS_UC_PKG)
#define HEREMAPS_UC_PKG "org.tizen.heremaps-uc"
#endif

#define DOMAIN_NAME HEREMAPS_UC_PKG

#define TAG_HEREMAPS_UC "HEREMAPS_UC"
#define HEREMAPS_UC_DLOG_DEBUG

#ifdef HEREMAPS_UC_DLOG_DEBUG        /**< if debug mode, show filename & line number */

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG TAG_HEREMAPS_UC
#endif

#define LS_LOGD(fmt,args...)  LOGD(fmt, ##args)
#define LS_LOGW(fmt,args...)  LOGW(fmt, ##args)
#define LS_LOGI(fmt,args...)  LOGI(fmt, ##args)
#define LS_LOGE(fmt,args...)  LOGE(fmt, ##args)

#elif HEREMAPS_UC_DLOG_RELEASE      /* if release mode */

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG TAG_HEREMAPS_UC
#endif

#define LS_LOGD(fmt,args...)  LOGD(fmt, ##args)
#define LS_LOGW(fmt,args...)  LOGW(fmt, ##args)
#define LS_LOGI(fmt,args...)  LOGI(fmt, ##args)
#define LS_LOGE(fmt,args...)  LOGE(fmt, ##args)
#else                       /* if do not use dlog */
#define LS_LOGD(...)  g_debug(__VA_ARGS__)
#define LS_LOGW(...)  g_warning(__VA_ARGS__)
#define LS_LOGI(...)  g_message(__VA_ARGS__)
#define LS_LOGE(...)  g_error(__VA_ARGS__)
#endif

#define P_(s)			dgettext(HEREMAPS_UC_PKG, s)
#define S_(s)			dgettext("sys_string", s)
#define dgettext_noop(s)	(s)
#define N_(s)			dgettext_noop(s)

#define KEY_ENABLED	1
#define KEY_DISABLED 0

#define LS_FUNC_ENTER 	LS_LOGD("(%s) ENTER", __FUNCTION__);
#define LS_FUNC_EXIT 	LS_LOGD("(%s) EXIT", __FUNCTION__);

#define SAFE_STRDUP(src) (src) ? strdup(src) : NULL

#define LS_MEM_FREE(ptr)	\
	do { \
		if (ptr != NULL) {	\
			free((void *)ptr);	\
			ptr = NULL;	\
		}	\
	} while (0)


#define LS_MEM_NEW(ptr, num_elements, type)	 \
	do { \
		if ((int)(num_elements) <= 0) { \
			ptr = NULL; \
		} else { \
			ptr = (type *) calloc(num_elements, sizeof(type)); \
		} \
	} while (0)


#define LS_RETURN_IF_FAILED(point) do { \
		if (point == NULL) { \
			LS_LOGE("critical error : LS_RETURN_IF_FAILED"); \
			return; \
		} \
	} while (0)

#define LS_RETURN_VAL_IF_FAILED(point, val) do { \
		if (point == NULL) { \
			LS_LOGE("critical error : NAVI_RETURN_VAL_IS_FAILED"); \
			return val; \
		} \
	} while (0)

typedef struct appdata
{
	app_control_h app_control;

	Evas_Object *win_main;
	Evas_Object *conformant;
	Evas_Object *layout_main;

	Evas_Object *popup;
} heremaps_uc_app_data;

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* HEREMAPS_UC_COMMON_H_ */
