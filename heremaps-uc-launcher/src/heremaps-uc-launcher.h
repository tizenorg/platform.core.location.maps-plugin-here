/*
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jongmun Woo <jongmun.woo@samsung.com>
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



#ifndef UC_LAUNCHER_COMMON_H_
#define UC_LAUNCHER_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <app.h>
#include <dlog.h>
#include <glib.h>
#ifndef Eina_Bool
#include <stdbool.h>
#endif
#include <libintl.h>
#include <stdio.h>
#include <system_info.h>

#if !defined(UC_LAUNCHER_PKG)
#define UC_LAUNCHER_PKG "heremaps-uc-launcher"
#endif

#define DOMAIN_NAME UC_LAUNCHER_PKG

#define TAG_UC_LAUNCHER "UC_LAUNCHER"
#define UC_LAUNCHER_DLOG_DEBUG

#ifdef UC_LAUNCHER_DLOG_DEBUG        /**< if debug mode, show filename & line number */

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG TAG_UC_LAUNCHER
#endif

#define LS_LOGD(fmt, args...)  LOGD(fmt, ##args)
#define LS_LOGW(fmt, args...)  LOGW(fmt, ##args)
#define LS_LOGI(fmt, args...)  LOGI(fmt, ##args)
#define LS_LOGE(fmt, args...)  LOGE(fmt, ##args)

#elif UC_LAUNCHER_DLOG_RELEASE      /* if release mode */

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG TAG_UC_LAUNCHER
#endif

#define LS_LOGD(fmt, args...)  LOGD(fmt, ##args)
#define LS_LOGW(fmt, args...)  LOGW(fmt, ##args)
#define LS_LOGI(fmt, args...)  LOGI(fmt, ##args)
#define LS_LOGE(fmt, args...)  LOGE(fmt, ##args)
#else                       /* if do not use dlog */
#define LS_LOGD(...)  g_debug(__VA_ARGS__)
#define LS_LOGW(...)  g_warning(__VA_ARGS__)
#define LS_LOGI(...)  g_message(__VA_ARGS__)
#define LS_LOGE(...)  g_error(__VA_ARGS__)
#endif

#define P_(s)			dgettext(UC_LAUNCHER_PKG, s)
#define S_(s)			dgettext("sys_string", s)
#define dgettext_noop(s)	(s)
#define N_(s)			dgettext_noop(s)

#define LS_FUNC_ENTER 	LS_LOGD("(%s) ENTER", __FUNCTION__);
#define LS_FUNC_EXIT 	LS_LOGD("(%s) EXIT", __FUNCTION__);



#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* UC_LAUNCHER_COMMON_H_ */
