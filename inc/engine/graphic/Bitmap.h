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

#ifndef HERE_GRAPHIC_BITMAP_H
#define HERE_GRAPHIC_BITMAP_H

#include "common/HereMaps_global.h"
#include "base/BaseObject.h"
#include "graphic/Dimension.h"
#include "graphic/Rectangle.h"
#include "graphic/BufferInfo.h"


TIZEN_MAPS_BEGIN_NAMESPACE

enum BitmapPixelFormat
{
	BITMAP_PIXEL_FORMAT_RGB565 = 1, /**< The RGB565 pixel format */
	BITMAP_PIXEL_FORMAT_ARGB8888, /**< The ARGB8888 pixel format */
	BITMAP_PIXEL_FORMAT_R8G8B8A8, /**< The R8G8B8A8 pixel format, the order of the color component is guaranteed by the byte unit */
	BITMAP_PIXEL_FORMAT_MAX, // This enum value is for internal use only. Using this enum value can cause behavioral, security-related, and consistency-related issues in the application.
	BITMAP_PIXEL_FORMAT_MIN = 0 // This enum value is for internal use only. Using this enum value can cause behavioral, security-related, and consistency-related issues in the application.
};

class EXPORT_API Bitmap : public Object
{
public:
    Bitmap(void);

    virtual ~Bitmap(void);

    result Construct(const Dimension& dim, BitmapPixelFormat bitmapPixelFormat=BITMAP_PIXEL_FORMAT_R8G8B8A8);
    result Construct(const Bitmap& bitmap, const Rectangle& rect);
    result Construct(const byte* pBuffer, int bufferSize, const Dimension& dim, BitmapPixelFormat bitmapPixelFormat=BITMAP_PIXEL_FORMAT_R8G8B8A8);
    result Lock(BufferInfo& info, long timeout = INFINITE);
    result Unlock(void);

    int GetWidth(void) const;
    int GetHeight(void) const;
    void SetAlphaConstant(int opacity);
    unsigned char* GetBuffer() const;
    BitmapPixelFormat GetPixelColorFormat() const;
private:
    int width;
    int height;
    int bytes_per_pixel;
    BitmapPixelFormat pixel_format;
    unsigned char* buffer;
    pthread_mutex_t mutex;

    void BitBlt(int xDest, int yDest, unsigned char *pSrcBuffer, int xSour, int ySour, int wSour, int hSour, int nPitch, unsigned long opacity = 255);
};

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_GRAPHIC_BITMAP_H */
