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

#ifndef HERE_GRAPHIC_UTIL_H
#define HERE_GRAPHIC_UTIL_H

#include "common/HereMaps_global.h"
#include "graphic/Grp_UtilType.h"
#include "graphic/Bitmap.h"
#include "graphic/PngDecoder.h"

TIZEN_MAPS_BEGIN_NAMESPACE

namespace _Util
	{
	bool IntersectRect(Rectangle<int>& outRect,
                           const Rectangle<int>& srcRect1,
                           const Rectangle<int>& srcRect2);

	bool IntersectRect(Rectangle<float>& outRect,
                           const Rectangle<float>& srcRect1,
                           const Rectangle<float>& srcRect2);

	long GetHashCode(const char *string);

	EXPORT_API Bitmap* DecodePngToBmp(const byte* buffer, size_t size,
                                          MediaPixelFormat pixelFormat=MEDIA_PIXEL_FORMAT_RGBA8888);

	EXPORT_API void ConvertRGBA2BGRA(void *data, unsigned int w, unsigned int h,
                                         MediaPixelFormat format=MEDIA_PIXEL_FORMAT_RGBA8888);

	template<typename T>
	inline T
	Abs(const T& t)
	{
		return (t >= 0) ? t : -t;
	}

	template<typename T>
	inline T
	Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template<typename T>
	inline T
	Max(T a, T b)
	{
		return (a > b) ? a : b;
	}
} // _Util

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_GRAPHIC_UTIL_H */
