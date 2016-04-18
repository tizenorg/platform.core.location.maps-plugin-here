/*
 * Copyright (C) 2013 HERE Global B.V. All rights reserved.
 * This software, including documentation, is protected by copyright controlled by
 * HERE Global B.V. (“Software”). All rights are reserved. Copying, including reproducing,
 * storing, adapting or translating, any or all of this material requires the prior
 * written consent of HERE Global B.V. You may use this
 * Software in accordance with the terms and conditions defined in the
 * HERE Location Platform Services Terms and Conditions, available at
 * http://developer.here.com/terms-conditions-base
 *
 * As an additional permission to the above, you may distribute Software,
 * in object code format as part of an Application, according to, and subject to, terms and
 * conditions defined in the Tizen Software Development kit (“SDK”) License Agreement.
 * You may distribute such object code format Application under terms of your choice,
 * provided that the header and source files of the Software have not been modified.
 */

#ifndef HEREMAPS_GLOBAL_H
#define HEREMAPS_GLOBAL_H

#define TIZEN_MIGRATION

#ifdef TIZEN_MIGRATION
/* enhancement for updated HERE APIs */
#define TIZEN_CUSTOMIZATION

/* sub-features */
#define TIZEN_SUPPORT_LIMIT_RETRYING_FETCHING_TILES	/* limit the number of retrying when failed fetching tiles */
#define TIZEN_SUPPORT_TILE_FILE_CACHE
#define TIZEN_SUPPORT_POST_METHOD
#define TIZEN_SUPPORT_CRYPTO_LOCK			/* mutex locking system for SSL */
#define TIZEN_SUPPORT_OPTIMIZATION_OF_REDRAWING

/* configuration */
#define TIZEN_CFG_CURL_TIMEOUT		20	/* seconds */
#define TIZEN_CFG_CURL_MULTITHREADS	8	/* the limit of multi-threads for CURL */

/* for debugging */
//#define TIZEN_PROFILING_CURL_TIME
//#define TIZEN_PROFILING_MEMLEAK
#endif



#ifdef TIZEN_MIGRATION
#include <string>

typedef unsigned long result;
typedef std::string String;
typedef std::string Uri;
typedef std::wstring WString;

typedef unsigned char byte;
#ifndef null
#define null    0
#endif // null
#endif



/*
 * Note: DEBUG variable should be set from the outside.
 * Currently done in CMAKE file
 */

#define HERE_MAPS_BEGIN_NAMESPACE  namespace Here { namespace Maps {
#define HERE_MAPS_END_NAMESPACE    }}
#define HERE_MAPS_NAMESPACE_PREFIX Here::Maps

#define TIZEN_MAPS_BEGIN_NAMESPACE  namespace Tizen { namespace Maps {
#define TIZEN_MAPS_END_NAMESPACE    }}
#define TIZEN_MAPS_NAMESPACE_PREFIX Tizen::Maps

#include <memory>
#include <dlog.h>

//logging macro prototypes
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "HERE_PLUGIN"

#define HERE_MAPS_LOG_DBG_INFO(fmt,args...)  LOGD(fmt, ##args);
#define HERE_MAPS_LOG_ERROR(fmt,args...)     LOGE(fmt, ##args);
#define HERE_MAPS_LOG_WARNING(fmt,args...)   LOGW(fmt, ##args);

#define HERE_MAPS_RETURN_RESULT(cond,ret,fmt,args...)\
        if (!cond) {\
                LOGE(fmt, ##args);\
                return ret;\
        }

#define HERE_MAPS_TRY_CATCH(cond,catch,fmt,args...)\
        if (!cond) {\
                LOGE(fmt, ##args);\
                catch;\
                goto CATCH;\
        }

// Error severities
#define E_SUCCESS                       0
#define E_FAILURE                       -1
#define E_SYSTEM                        -2
#define E_INVALID_STATE                 -3
#define E_OUT_OF_MEMORY                 -4

#ifndef INFINITE
#define INFINITE    0xFFFFFFFF
#endif // INFINITE

//assertions
#include <assert.h>
#if DEBUG
#define HERE_MAPS_ASSERT(x) assert(x);
#else
#define HERE_MAPS_ASSERT(x)
#endif

typedef unsigned char Byte;
typedef unsigned int UInt;



#define HERE_MAPS_NO_COPY_NO_ASSIGN(ClassName) \
  private:                                     \
  ClassName(const ClassName&);                 \
  ClassName& operator=(const ClassName&)


HERE_MAPS_BEGIN_NAMESPACE
extern void Stopwatch_Start(int aIndex);
extern void Stopwatch_Stop(int aIndex);
extern void Stopwatch_Show(int aIndex);
extern void Stopwatch_Reset(int aIndex);
HERE_MAPS_END_NAMESPACE

#endif // HEREMAPS_GLOBAL_H
