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

#include "heremaps-uc-launcher.h"
#include <gio/gio.h>

#define UC_RECEIVER_NAME	"org.tizen.lbs.Providers.HereMapsUCLauncher"

GMainLoop *loop = NULL;

static void on_bus_acquired(GDBusConnection *conn, const gchar *name, gpointer user_data)
{
	LS_LOGD("HereMapsUCLauncher: Acquired the bus <%s>", name);

	g_main_loop_quit(loop);
	LS_LOGD("HereMapsUCLauncher: g_main_loop_quit");
}

static void on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
	LS_LOGD("HereMapsUCLauncher: Acquired the name <%s> on the system bus", name);
}

static void on_name_lost(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
	LS_LOGD("HereMapsUCLauncher: Lost the name <%s> on the system bus", name);
}

static void launch_heremaps_uc()
{
	LS_FUNC_ENTER

	app_control_h app_control = NULL;
	app_control_create(&app_control);
	app_control_set_app_id(app_control, "org.tizen.heremaps-uc");
	app_control_send_launch_request(app_control, NULL, NULL);
	app_control_destroy(app_control);

	gchar *service_name = g_strdup(UC_RECEIVER_NAME);
	guint owner_id = g_bus_own_name(G_BUS_TYPE_SESSION, service_name, G_BUS_NAME_OWNER_FLAGS_NONE, on_bus_acquired, on_name_acquired, on_name_lost, NULL, NULL);
	LS_LOGD("g_bus_own_name id=[%d]", owner_id);

	loop =  g_main_loop_new(NULL, TRUE);

	LS_LOGD("HereMapsUCLauncher: g_main_loop_quit");
	g_main_loop_run(loop);

	g_main_loop_unref(loop);
	LS_LOGD("HereMapsUCLauncher: g_main_loop_unref");

	g_bus_unown_name(owner_id);
	LS_LOGD("g_bus_unown_name");

	g_free(service_name);
	LS_LOGD("g_free service_name");

	loop = NULL;

	LS_FUNC_EXIT
}

int main(int argc, char *argv[])
{
	LS_FUNC_ENTER

	launch_heremaps_uc();

	LS_FUNC_EXIT
	return 0;
}
