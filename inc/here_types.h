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

#ifndef _LOCATION_HERE_TYPES_H_
#define _LOCATION_HERE_TYPES_H_

#include <glib.h>

typedef enum {
    HERE_ERROR_NONE = 0,                /**< Successful */
    HERE_ERROR_PERMISSION_DENIED,       /**< Permission Denied */
    HERE_ERROR_OUT_OF_MEMORY,           /**< Out of memory */
    HERE_ERROR_INVALID_PARAMETER,       /**< Invalid parameter */
    HERE_ERROR_NOT_SUPPORTED,           /**< Not supported */
    HERE_ERROR_CONNECTION_TIME_OUT,     /**< Timeout error, no answer */
    HERE_ERROR_NETWORK_UNREACHABLE,     /**< Network unavailable */
    HERE_ERROR_INVALID_OPERATION,       /**< Opeartion is not valid */
    HERE_ERROR_KEY_NOT_AVAILABLE,       /**< Invalid key */
    HERE_ERROR_RESOURCE_BUSY,           /**< Resource busy */
    HERE_ERROR_CANCELED,                /**< Service canceled */
    HERE_ERROR_UNKNOWN,                 /**< Unknown error */
    HERE_ERROR_SERVICE_NOT_AVAILABLE,   /**< Service unavailabe*/
    HERE_ERROR_NOT_FOUND,               /**< Result not found */
} here_error_e;

#endif //_LOCATION_HERE_TYPES_H_
