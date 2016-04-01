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

#include <stdio.h>
#include "heremaps-uc-dbus.h"

/**
* @brief        information for DBUS
*/
#define UC_RECEIVER_NAME	"org.tizen.lbs.Providers.HereMapsUCLauncher"
#define UC_RECEIVER_PATH	"/org/tizen/lbs/Providers/HereMapsUCLauncher"
#define UC_INTERFACE_NAME	"org.tizen.lbs.HereMapsUCLauncher"


typedef struct _heremaps_uc_dbus_s {
	GDBusConnection *conn;
	gchar *service_name;
	gchar *service_path;
	gchar *signal_path;
} heremaps_uc_dbus_s;

static void heremaps_uc_ready_cb(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	MAPS_FUNC_ENTER

	GError *error = NULL;
	g_dbus_proxy_new_finish(res, &error);
}

EXPORT_API int heremaps_uc_dbus_launch_receiver()
{
	MAPS_FUNC_ENTER

	char *bus_addr = NULL;
	GError *error = NULL;

#if !GLIB_CHECK_VERSION(2, 35, 0)
	g_type_init();
#endif

	heremaps_uc_dbus_s *handle = g_new0(heremaps_uc_dbus_s, 1);
	g_return_val_if_fail(handle, HEREMAPS_UC_DBUS_ERROR_MEMORY);

	handle->conn = NULL;

	/* get addr of dbus */
	bus_addr = g_dbus_address_get_for_bus_sync(G_BUS_TYPE_SESSION, NULL, &error);
	if (!bus_addr) {
		MAPS_LOGD("Fail to get addr of bus.");
		return HEREMAPS_UC_DBUS_ERROR_CONNECTION;
	}
	MAPS_LOGD("bus_addr: %s", bus_addr);

	/* connect and setup dbus */
	handle->conn = g_dbus_connection_new_for_address_sync(bus_addr,
							G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT |
							G_DBUS_CONNECTION_FLAGS_MESSAGE_BUS_CONNECTION,
							NULL, NULL, &error);
	if (!handle->conn) {
		if (error && error->message) {
			MAPS_LOGD("Fail to get GBus. ErrCode[%d], Msg[%s]", error->code, error->message);
			g_error_free(error);
			error = NULL;
		}
		return HEREMAPS_UC_DBUS_ERROR_CONNECTION;
	}
	MAPS_LOGD("handle->conn: %p", handle->conn);
	g_free(bus_addr);

	handle->service_name = g_strdup(UC_RECEIVER_NAME);
	handle->service_path = g_strdup(UC_RECEIVER_PATH);
	handle->signal_path = g_strdup_printf("%s/%s", handle->service_path, "SAMSUNG");
	MAPS_LOGD("Object Path [%s]", handle->signal_path);

	g_dbus_proxy_new(handle->conn, G_DBUS_PROXY_FLAGS_NONE, NULL, handle->service_name, handle->signal_path, UC_INTERFACE_NAME, NULL, heremaps_uc_ready_cb, NULL);

	if (handle->conn) {
		g_object_unref(handle->conn);
		handle->conn = NULL;
	}
	g_free(handle->service_path);
	g_free(handle->service_name);
	g_free(handle->signal_path);
	g_free(handle);

	return HEREMAPS_UC_DBUS_ERROR_NONE;
}

