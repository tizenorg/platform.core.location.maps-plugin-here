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

static void launch_heremaps_uc()
{
	LS_FUNC_ENTER

	app_control_h app_control = NULL;
	app_control_create(&app_control);
	app_control_set_app_id(app_control, "org.tizen.heremaps-uc");
	app_control_send_launch_request(app_control, NULL, NULL);
	app_control_destroy(app_control);

	LS_FUNC_EXIT
}

int main(int argc, char *argv[])
{
	LS_FUNC_ENTER

	launch_heremaps_uc();

	LS_FUNC_EXIT
	return 0;
}
