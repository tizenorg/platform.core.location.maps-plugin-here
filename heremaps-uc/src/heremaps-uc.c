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

#include "heremaps-uc-common.h"

#define UC_FILE "/opt/usr/apps/org.tizen.heremaps-uc/shared/data/heremaps_uc.xml"

static Evas_Object *create_conformant(Evas_Object * parent)
{
	LS_FUNC_ENTER
	Evas_Object *conformant = NULL;

	conformant = elm_conformant_add(parent);
	elm_win_conformant_set(parent, EINA_TRUE);
	elm_win_resize_object_add(parent, conformant);
	evas_object_size_hint_weight_set(conformant, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(conformant, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(conformant);

	LS_FUNC_EXIT
	return conformant;
}

static Evas_Object *create_layout(Evas_Object * parent)
{
	LS_FUNC_ENTER
	Evas_Object *layout = NULL;

	if (parent != NULL) {
		layout = elm_layout_add(parent);
		elm_object_content_set(parent, layout);
		evas_object_show(layout);
	}

	LS_FUNC_EXIT
	return layout;
}

static void win_del(void *data, Evas_Object * obj, void *event)
{
	LS_FUNC_ENTER
	elm_exit();
}

static void read_file(heremaps_uc_app_data *ad)
{
	LS_FUNC_ENTER
	FILE *fp = fopen(UC_FILE, "r");
	char buf[15] = {};
	char *data = NULL, *save_token = NULL;
	app_control_h reply;
	int ret = 0;

	if (fp == NULL)
		LS_LOGE("UC_FILE open fail");
	else {
		ret = fread(buf, 1, 15, fp);
		fclose(fp);

		if (ret > 0) {
			data = strtok_r(buf, "=", &save_token);
			data = strtok_r(NULL, "=", &save_token);
		} else
			LS_LOGE("UC_FILE read fail");
	}

	app_control_create(&reply);
	if (data == NULL)
		app_control_add_extra_data(reply, "result", "No");
	else if ((strcmp(data, "Yes") == 0) || (strcmp(data, "No") == 0))
		app_control_add_extra_data(reply, "result", data);
	else
		app_control_add_extra_data(reply, "result", "No");
	ret = app_control_reply_to_launch_request(reply, ad->app_control, APP_CONTROL_RESULT_SUCCEEDED);
	if (ret != APP_CONTROL_ERROR_NONE)
		LS_LOGE("app_control_reply_to_launch_request fail. err=%d", ret);
	app_control_destroy(reply);
}

static void save_file(char *data, heremaps_uc_app_data *ad)
{
	FILE *fp = fopen(UC_FILE, "w+");
	char buf[15] = {};
	app_control_h reply;
	int ret = 0;

	app_control_create(&reply);

	if (fp == NULL) {
		LS_LOGE("UC_FILE open fail");
		app_control_add_extra_data(reply, "result", "No");
	} else {
		snprintf(buf, sizeof(buf)-1, "Agree=%s", data);
		fwrite(buf, strlen(buf), 1, fp);
		fclose(fp);
		LS_LOGE("result of save_file() is %s", data);

		app_control_add_extra_data(reply, "result", strdup(data));
	}

	ret = app_control_reply_to_launch_request(reply, ad->app_control, APP_CONTROL_RESULT_SUCCEEDED);
	if (ret != APP_CONTROL_ERROR_NONE)
		LS_LOGE("app_control_reply_to_launch_request fail. err=%d", ret);
	app_control_destroy(reply);
}

static void disagree_btn_cb(void *data, Evas_Object * obj, void *event)
{
	LS_FUNC_ENTER
	heremaps_uc_app_data *ad = (heremaps_uc_app_data *) data;

	save_file("No", ad);

	elm_exit();
}

static void agree_btn_cb(void *data, Evas_Object * obj, void *event)
{
	LS_FUNC_ENTER
	heremaps_uc_app_data *ad = (heremaps_uc_app_data *) data;

	save_file("Yes", ad);
	elm_exit();
}

static void back_btn_cb(void *data, Evas_Object * obj, void *event)
{
	LS_FUNC_ENTER
	heremaps_uc_app_data *ad = (heremaps_uc_app_data *) data;

	read_file(ad);
	elm_exit();
}

static Evas_Object *create_win(const char *name)
{
	LS_FUNC_ENTER
	Evas_Object *eo;

	eo = elm_win_add(NULL, name, ELM_WIN_BASIC);
	if (eo) {
		elm_win_title_set(eo, name);
		elm_win_borderless_set(eo, EINA_TRUE);
		evas_object_smart_callback_add(eo, "delete,request", win_del, NULL);
		elm_win_alpha_set(eo, EINA_TRUE);
		if (elm_win_wm_rotation_supported_get(eo)) {
			int rots[4] = { 0, 90, 180, 270 };
			elm_win_wm_rotation_available_rotations_set(eo, (const int *)(&rots), 4);
		}
	}
	return eo;
}

static Evas_Object *create_popup(Evas_Object *layout, heremaps_uc_app_data *ad)
{
	Evas_Object *popup;
	Evas_Object *disagree_btn, *agree_btn;

	/* popup */
	popup = elm_popup_add(layout);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, back_btn_cb, ad);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	elm_object_part_text_set(popup, "title,text", P_("IDS_POSITIONING_CONSENT_TITLE"));
	elm_object_text_set(popup, P_("IDS_POSITIONING_CONSENT_BODY"));

	/* Disagree button */
	disagree_btn = elm_button_add(popup);
	elm_object_style_set(disagree_btn, "popup");
	elm_object_text_set(disagree_btn, P_("IDS_ST_BUTTON_DISAGREE"));
	elm_object_part_content_set(popup, "button1", disagree_btn);
	evas_object_smart_callback_add(disagree_btn, "clicked", disagree_btn_cb, ad);

	/* Agree button */
	agree_btn = elm_button_add(popup);
	elm_object_style_set(agree_btn, "popup");
	elm_object_text_set(agree_btn, P_("IDS_ST_BUTTON_AGREE"));
	elm_object_part_content_set(popup, "button2", agree_btn);
	evas_object_smart_callback_add(agree_btn, "clicked", agree_btn_cb, ad);

	evas_object_show(popup);

	return popup;
}

static bool _app_create_cb(void *user_data)
{
	LS_FUNC_ENTER

	return true;
}

static void _app_terminate_cb(void *user_data)
{
	LS_FUNC_ENTER
}

/*
static void _app_pause_cb(void *user_data)
{
	LS_FUNC_ENTER
}

static void _app_resume_cb(void *user_data)
{
	LS_FUNC_ENTER
}
*/

static void _app_control_cb(app_control_h app_control, void *user_data)
{
	LS_FUNC_ENTER

	gboolean ret = FALSE;
	heremaps_uc_app_data *ad = (heremaps_uc_app_data *) user_data;
	char *action = NULL;
	char *data = NULL;
	LS_RETURN_IF_FAILED(ad);

	ret = app_control_clone(&(ad->app_control), app_control);
	if (ret == FALSE)
		LS_LOGE("app_control_clone. err=%d", ret);

	app_control_get_extra_data(app_control, "action", &action);
	if (action != NULL) {
		if (strcmp(action, "Get") == 0) {
			read_file(ad);
			elm_exit();
		} else if (strcmp(action, "Set") == 0) {
			app_control_get_extra_data(app_control, "value", &data);
			LS_LOGE("DATA = %s", data);

			 if (data != NULL) {
				if ((strcmp(data, "Yes") == 0) || (strcmp(data, "No") == 0)) {
					save_file(data, ad);
					elm_exit();
				}
			}
		}
	}

	if (ad->win_main) {
		evas_object_del(ad->win_main);
		ad->win_main = NULL;
	}

	elm_app_base_scale_set(2.6);
	elm_config_accel_preference_set("3d");

	bindtextdomain(HEREMAPS_UC_PKG, LOCALE_DIR);

	ad->win_main = create_win(HEREMAPS_UC_PKG);
	ad->conformant = create_conformant(ad->win_main);
	ad->layout_main = create_layout(ad->conformant);

	ad->popup = create_popup(ad->layout_main, ad);

	evas_object_show(ad->win_main);
	LS_FUNC_EXIT
}

/*
static void _app_low_memory_cb(void *user_data)
{
	LS_FUNC_ENTER
}

static void _app_low_battery_cb(void *user_data)
{
	LS_FUNC_ENTER
}

static void _app_device_orientation_cb(app_event_info_h event_info, void *user_data)
{
	LS_FUNC_ENTER
	LS_RETURN_IF_FAILED(event_info);
	LS_RETURN_IF_FAILED(user_data);

	heremaps_uc_app_data *ad = (heremaps_uc_app_data *)user_data;
	app_device_orientation_e orientation;
	app_event_get_device_orientation(event_info, &orientation);
	elm_win_rotation_with_resize_set(ad->win_main, orientation);
}
*/

static void _app_language_changed_cb(app_event_info_h event_info, void *user_data)
{
	LS_FUNC_ENTER

	char *locale = vconf_get_str(VCONFKEY_LANGSET);
	if (locale) elm_language_set(locale);
}

int main(int argc, char *argv[])
{
	LS_FUNC_ENTER

	int ret = 0;
	heremaps_uc_app_data ad = {0,};

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = _app_create_cb;
	event_callback.terminate = _app_terminate_cb;
	event_callback.app_control = _app_control_cb;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, NULL, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, NULL, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, NULL, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED,	_app_language_changed_cb, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, NULL, NULL);

	ret = APP_ERROR_NONE;
	ret = ui_app_main(argc, argv, &event_callback, &ad);

	if (ret != APP_ERROR_NONE)
		LS_LOGE("ui_app_main() is failed. err=%d", ret);

	return ret;

	LS_FUNC_EXIT
}
