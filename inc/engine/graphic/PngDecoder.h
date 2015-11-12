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

#ifndef _PNG_DECODER_H_
#define _PNG_DECODER_H_

#include <png.h>
#include "common/HereMaps_global.h"


enum MediaPixelFormat
{
	MEDIA_PIXEL_FORMAT_NONE = 0x0000,     /**< The undefined pixel format */
	MEDIA_PIXEL_FORMAT_RGB565LE = 0x0001, /**< The RGB565 little-endian format */
	MEDIA_PIXEL_FORMAT_RGB565BE,          /**< The RGB565 big-endian format */
	MEDIA_PIXEL_FORMAT_RGB888 = 0x0100,   /**< The RGB888 format */
	MEDIA_PIXEL_FORMAT_BGR888,            /**< The BGR888 format */
	MEDIA_PIXEL_FORMAT_RGBA8888,          /**< The RGBA8888 format */
	MEDIA_PIXEL_FORMAT_BGRA8888,          /**< The BGRA8888 format */
	MEDIA_PIXEL_FORMAT_YUV420P = 0x0200,  /**< The YUV420 Planar format */
	MEDIA_PIXEL_FORMAT_NV12,              /**< The NV12 format */
	MEDIA_PIXEL_FORMAT_NV12_TILE,         /**< The NV12 tiled format */
	MEDIA_PIXEL_FORMAT_NV21,              /**< The NV21 format */
	MEDIA_PIXEL_FORMAT_YUV444P,           /**< The YUV444 Planar format */
	MEDIA_PIXEL_FORMAT_YUYV422,           /**< The YUYV422 format */
	MEDIA_PIXEL_FORMAT_UYVY422,           /**< The UYVY422 format */
	MEDIA_PIXEL_FORMAT_GRAY,              /**< The gray pixel format */
};

TIZEN_MAPS_BEGIN_NAMESPACE

class PngDecoder
{
public:

	static const int MAX_WIDTH = 5000;
	static const int MAX_HEIGHT = 5000;
	static const int MAX_SIZE = 4096000;   // 4Mbyte

	PngDecoder(void);
	virtual ~PngDecoder(void);

	/**
	 * Constructs this instancce with given buffer and length.
	 *
	 * @return	 An error code
	 * @param[in]  buffer		 The buffer that contains compressed data.
	 * @param[in]  length		 The length of buffer.
	 * @exception  E_SUCCESS	  The method is successful.
	 * @exception  E_INVALID_ARG  The input parameter is invalid.
	 */
	virtual result Construct(const byte* buffer, int length, MediaPixelFormat pixelFormat);

	/**
	 * Decodes current frame and returns decoded data.
	 *
	 * @return	 A buffer pointer of decoded data
	 * @param[out] outLength			 The length of outBuf.
	 * @exception  E_SUCCESS		  The method is successful.
	 * @exception  E_OUT_OF_MEMORY	Memory is insufficient.
	 * @exception  E_INVALID_DATA	 The data is invalid.
	 */
	virtual byte* DecodeN(int& outLength);

	/**
	 * Sets the decoding region. @n
	 *
	 * @return	 An error code
	 * @param[in]  rect					 The decoding region.
	 * @exception  E_SUCCESS				The method is successful.
	 * @exception  E_INVALID_ARG			The input parameter is invalid.
	 * @exception  E_UNSUPPORTED_OPERATION  This method is unsupported.
	 */
	virtual result SetDecodingRegion(int x, int y, int width, int height);

	/**
	 * Gets current dimension of image.
	 *
	 * @return	  An error code
	 * @param[out]  width   The width of image.
	 * @param[out]  height  The height of image.
	 */
	virtual result GetDimension(int& width, int& height);

	/**
	 * Gets the output pixel format.
	 *
	 * @return		   The output pixel format.
	 */
	virtual MediaPixelFormat GetPixelFormat(void);

	void PngReadData(void *pngPtr, byte* data, int size);

	static void PngReadDataStatic(png_structp pngPtr, png_bytep data, png_size_t length);
protected:


private:
	byte* __pBuf;
	unsigned int __curPos;
	unsigned int __bufSize;

	png_structp __pPng;
	png_infop __pInfo;

	int __srcWidth;
	int __srcHeight;
	int __scale;
	int __decodingRectX;
	int __decodingRectY;
	int __decodingRectWidth;
	int __decodingRectHeight;
	bool __isDecodeRegionEnabled;
	MediaPixelFormat __format;

}; // class PngDecoder

TIZEN_MAPS_END_NAMESPACE

#endif
