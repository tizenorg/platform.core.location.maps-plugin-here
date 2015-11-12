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

#ifndef BASE_BUFFER_BASE_H
#define BASE_BUFFER_BASE_H

#include "common/HereMaps_global.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class BufferBase
{
public:
	BufferBase(void);
	virtual ~BufferBase(void);

	int GetCapacity(void) const;
	int GetLimit(void) const;

	class _BufferData
	{
	public:
		_BufferData(void);
		virtual ~_BufferData(void);
		byte* GetArray(void);


		// Attribute
		unsigned long long capacityInByte;
		long refCount;
	}; // _BufferData

	int _capacity;
	int _position;
	int _limit;
	int _mark;
	_BufferData* _pData;
	byte* __pArrayStart;
}; // BufferBase

TIZEN_MAPS_END_NAMESPACE

#endif /* BASE_BUFFER_BASE_H */
