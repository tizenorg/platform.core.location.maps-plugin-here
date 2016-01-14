//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef MEM_CHECK_H
#define MEM_CHECK_H

#include <map>
#include <glib.h>

#include "common/HereMaps_global.h"
#include "base/BaseObject.h"

TIZEN_MAPS_BEGIN_NAMESPACE

#ifdef TIZEN_PROFILING_MEMLEAK
typedef std::map<void*,String> MemBlocks;

class EXPORT_API MemCheck
{
public:
	MemCheck();
	~MemCheck();

	static MemCheck& getInstance();
	void add(void *ptr, const char *file, const char *func, int line);
	void remove(void *ptr, const char *file, const char *func, int line);
	void report();

private:
	class MemCheckImpl;
	MemCheckImpl *__impl;
};

#define MEMCHECK_ADD(p)		TIZEN_MAPS_NAMESPACE_PREFIX::MemCheck::getInstance().add(p, __FILE__, __FUNCTION__, __LINE__)
#define MEMCHECK_REMOVE(p)	TIZEN_MAPS_NAMESPACE_PREFIX::MemCheck::getInstance().remove(p, __FILE__, __FUNCTION__, __LINE__)
#define MEMCHECK_REPORT(p)	TIZEN_MAPS_NAMESPACE_PREFIX::MemCheck::getInstance().report()
#else
#define MEMCHECK_ADD(p)
#define MEMCHECK_REMOVE(p)
#define MEMCHECK_REPORT(p)
#endif

TIZEN_MAPS_END_NAMESPACE

#endif // MEM_CHECK_H