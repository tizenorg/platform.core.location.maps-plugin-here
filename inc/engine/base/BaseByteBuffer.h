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

#ifndef BASE_BYTE_BUFFER_H
#define BASE_BYTE_BUFFER_H

#include "common/HereMaps_global.h"
#include "base/BaseBufferBase.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class ByteBuffer	: public BufferBase
{
public:
	ByteBuffer(void);
	virtual ~ByteBuffer(void);
	unsigned long Construct(const byte* pBuffer, int index, int length, int capacity);
	byte* GetPointer(void) const;

}; // ByteBuffer

TIZEN_MAPS_END_NAMESPACE

#endif /* BASE_BYTE_BUFFER_H */
