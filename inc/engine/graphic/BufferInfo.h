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

#ifndef HERE_GRAPHIC_BUFFERINFO_H
#define HERE_GRAPHIC_BUFFERINFO_H

#include "common/HereMaps_global.h"
#include "base/BaseObject.h"
#include "graphic/Rectangle.h"

#if 0
typedef enum
{
	PIXEL_FORMAT_RGB565 = 1, /**< The RGB565 pixel format */
	PIXEL_FORMAT_ARGB8888, /**< The ARGB8888 pixel format */
	PIXEL_FORMAT_R8G8B8A8, /**< The R8G8B8A8 pixel format @n
			                    The order of color component is guaranteed by the byte unit. */
	PIXEL_FORMAT_YCbCr420_PLANAR, /**< The 8-bit Y-plane followed by 8-bit 2x2 sub sampled U-plane and V-plane */
	PIXEL_FORMAT_JPEG, /**< The encoded format */
	PIXEL_FORMAT_NV12, /**< The NV12 pixel format */
	PIXEL_FORMAT_UYVY, /**< The UYVY pixel format */
	PIXEL_FORMAT_MAX, // This enum value is for internal use only. Using this enum value can cause behavioral, security-related, and consistency-related issues in the application.
	PIXEL_FORMAT_MIN = 0 // This enum value is for internal use only. Using this enum value can cause behavioral, security-related, and consistency-related issues in the application.
} PixelFormat;
#endif

TIZEN_MAPS_BEGIN_NAMESPACE

class BufferInfo;

class _BufferInfoImpl
{
public:
	enum
	{
		INVALID_BUFFER_HANDLE = 0
	};

	enum Orientation
	{
		ORIENTATION_PORTRAIT,
		ORIENTATION_LANDSCAPE,
		ORIENTATION_PORTRAIT_REVERSE,
		ORIENTATION_LANDSCAPE_REVERSE
	};

	enum HandleType
	{
		HANDLE_TYPE_NONE,
		HANDLE_TYPE_OVERLAY_REGION,
		HANDLE_TYPE_VE_SURFACE,
		HANDLE_TYPE_CANVAS_TEXTURE,
		HANDLE_TYPE_NATIVE_PIXMAP
	};

	enum Rotation
	{
		ROTATION_0,
		ROTATION_90,
		ROTATION_180,
		ROTATION_270
	};

	/**
	 * This is the default constructor for this class.
	 */
	_BufferInfoImpl();

	/**
	 * This is the destructor for this class.
	 */
	virtual ~_BufferInfoImpl();

	/*
	 * Gets the handle of the current instance of _BufferInfoImpl.
	 *
	 * @return	The runtime handle
	 *
	 */
	int GetHandle(HandleType handleType) const;

	void* GetUserData(HandleType handleType) const;

	/*
	 * Sets the handle of the current instance of _BufferInfoImpl.
	 *
	 */
	void SetHandle(HandleType handleType, int handle, void* pUserData = null);

	/*
	 * Gets the orientation of the current instance of _BufferInfoImpl.
	 *
	 */
	Orientation GetOrientation(void) const;

	/*
	 * Sets the orientation of the current instance of _BufferInfoImpl.
	 *
	 */
	void SetOrientation(Orientation orientation);

	/*
	 * Gets the bounds of the current instance of _BufferInfoImpl.
	 *
	 */
	Rectangle GetBounds(void) const;

	/*
	 * Sets the bounds of the current instance of _BufferInfoImpl.
	 *
	 */
	void SetBounds(const Rectangle& rect);

	/*
	 * Gets the rotation of the current instance of _BufferInfoImpl.
	 *
	 */
	Rotation GetRotation(void) const;

	/*
	 * Sets the rotation of the current instance of _BufferInfoImpl.
	 *
	 */
	void SetRotation(Rotation rotation);

	static _BufferInfoImpl* GetInstance(BufferInfo& bufferInfo);
	static const _BufferInfoImpl* GetInstance(const BufferInfo& bufferInfo);

private:
	/**
	 * This is the default copy constructor for this class.
	 */
	_BufferInfoImpl(const _BufferInfoImpl& src);

	/**
	 * This is the default assignment operator for this class.
	 */
	_BufferInfoImpl& operator =(const _BufferInfoImpl& rhs);

	friend class BufferInfo;

	HandleType __handleType;
	int __handle;
	void* __pUserData;
	Orientation __orientation;
	Rectangle __bounds;
	Rotation __rotation;

}; // _BufferInfoImpl

class BufferInfo : public Object
{
public:
	/**
	 * This is the default constructor for this class.
	 *
	 * @since	2.0
	 */
	BufferInfo(void);

	/**
	 * This is the copy constructor for the %BufferInfo class.
	 *
	 * @since 2.0
	 *
	 * @param[in]          rhs         An instance of %BufferInfo
	 */
	BufferInfo(const BufferInfo& rhs);

	/**
	 * This is the destructor for this class.
	 *
	 * @since	2.0
	 */
	virtual ~BufferInfo(void);

	/**
	 * This is the default assignment operator for this class.
	 *
	 * @since 2.0
	 *
	 * @param[in]          rhs         An instance of %BufferInfo
	 */
	BufferInfo& operator =(const BufferInfo& rhs);

	/**
	 *	Checks whether the value of the specified instance equals the value of the current instance.
	 *
	 * @since 2.0
	 *
	 *	@return			@c true if the value of the current instance equals the value of the specified instance, @n
	 *           else @c false
	 *	@param[in]	rhs	The object to compare with the current instance
	 */
	virtual bool Equals(const Object& rhs) const;

	/**
	 *	Gets the hash value of the current instance.
	 *
	 * @since 2.0
	 *
	 *	@return		An integer value indicating the hash value of the current instance
	 */
	virtual long GetHashCode(void) const;

public:
	/**
	 * The width of the buffer's logical dimensions in pixels.
	 *
	 * @since	2.0
	 */
	int width;

	/**
	 * The height of the buffer's logical dimensions in pixels.
	 *
	 * @since	2.0
	 */
	int height;

	/**
	 * The length of the buffer scan-line in bytes.
	 *
	 * @since	2.0
	 */
	int pitch;

	/**
	 * The bits per pixel of the buffer.
	 *
	 * @since	2.0
	 */
	int bitsPerPixel;

	/**
	 * The color format of the buffer.
	 *
	 * @since	2.0
	 */
	enum PixelFormat
	{
		PIXEL_FORMAT_RGB565 = 1, /**< The RGB565 pixel format */
		PIXEL_FORMAT_ARGB8888, /**< The ARGB8888 pixel format */
		PIXEL_FORMAT_R8G8B8A8, /**< The R8G8B8A8 pixel format @n
				                    The order of color component is guaranteed by the byte unit. */
		PIXEL_FORMAT_YCbCr420_PLANAR, /**< The 8-bit Y-plane followed by 8-bit 2x2 sub sampled U-plane and V-plane */
		PIXEL_FORMAT_JPEG, /**< The encoded format */
		PIXEL_FORMAT_NV12, /**< The NV12 pixel format */
		PIXEL_FORMAT_UYVY, /**< The UYVY pixel format */
		PIXEL_FORMAT_MAX, // This enum value is for internal use only. Using this enum value can cause behavioral, security-related, and consistency-related issues in the application.
		PIXEL_FORMAT_MIN = 0 // This enum value is for internal use only. Using this enum value can cause behavioral, security-related, and consistency-related issues in the application.
	};
	
	PixelFormat pixelFormat;

	/**
	 * A pointer to the actual locked pixel bits.
	 *
	 * @since	2.0
	 */
	void* pPixels;

private:
	friend class _BufferInfoImpl;

	//
	// This variable is for internal use only.
	// Using this variable can cause behavioral, security-related, and consistency-related issues in the application.
	//
	// @since 2.0
	//
	class _BufferInfoImpl * __pImpl;

}; // BufferInfo

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_GRAPHIC_BUFFERINFO_H */
