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

#ifndef HERE_GRAPHIC_FLOATPOINT_H
#define HERE_GRAPHIC_FLOATPOINT_H

#include "common/HereMaps_global.h"
#include "base/BaseObject.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class FloatPoint;

class EXPORT_API FloatPoint : public Object
{
public:
	/**
	 * This is the default constructor for this class. @n
	 * This constructor initializes an instance of %FloatPoint with the values (0.f, 0.f).
	 *
	 * @since 2.0
	 */
	FloatPoint(void);

	/**
	 * This is the copy constructor for the %FloatPoint class.
	 *
	 * @since 2.0
	 *
	 * @param[in]     rhs                     An instance of %FloatPoint
	 */
	FloatPoint(const FloatPoint& rhs);

	/**
	 * Initializes an instance of %FloatPoint with the specified location.
	 *
	 * @since 2.0
	 *
	 * @param[in]	x  The x-coordinate
	 * @param[in]	y  The y-coordinate
	 */
	FloatPoint(float x, float y);

	/**
	 * This is the destructor for this class.
	 *
	 * @since 2.0
	 */
	virtual ~FloatPoint(void);

	/**
	 * This is the default assignment operator for this class.
	 *
	 * @since 2.0
	 *
	 * @param[in]     rhs                     An instance of %FloatPoint
	 */
	FloatPoint& operator=(const FloatPoint& rhs);

	/**
	 * Checks whether the current instance and the specified instance of %FloatPoint are equal.
	 *
	 * @since 2.0
	 *
	 * @return		@c true if the two instances of %FloatPoint are at the same location, @n
	 *				else @c false
	 * @param[in]	rhs		An instance of %FloatPoint
	 */
	bool operator==(const FloatPoint& rhs) const;

	/**
	 * Checks whether the current instance and the specified instance of %FloatPoint are not equal.
	 *
	 * @since 2.0
	 *
	 * @return		@c true if the two instances of %FloatPoint are at different locations, @n
	 *				else @c false
	 * @param[in]	rhs		An instance of %FloatPoint
	 */
	bool operator!=(const FloatPoint& rhs) const;

	/**
	 * Adds the value of the specified instance of %FloatPoint and the current instance.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %FloatPoint containing the resulting value of the operation
	 * @param[in]	rhs		An instance of %FloatPoint
	 */
	FloatPoint operator+(const FloatPoint& rhs) const;

	/**
	 * Subtracts the value of the specified instance of %FloatPoint from the current instance.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %FloatPoint containing the resulting value of the operation
	 * @param[in]	rhs		An instance of %FloatPoint
	 */
	FloatPoint operator-(const FloatPoint& rhs) const;

	/**
	 * Adds the value of the specified instance of %FloatPoint to the current instance.
	 *
	 * @since 2.0
	 *
	 * @param[in]	point		An instance of %FloatPoint
	 */
	FloatPoint& operator+=(const FloatPoint& point);

	/**
	 * Subtracts the value of the specified instance of %FloatPoint from the current instance.
	 *
	 * @since 2.0
	 *
	 * @param[in]	point		An instance of %FloatPoint
	 */
	FloatPoint& operator-=(const FloatPoint& point);

	/**
	 * Checks whether the value of the specified instance of %FloatPoint equals the value of the current instance.
	 *
	 * @since 2.0
	 *
	 * @return		@c true if the value of the specified instance equals the value of the current instance, @n
	 *				else @c false
	 * @param[in]	rhs		An instance of %FloatPoint
	 * @remarks		The %FloatPoint class has a semantic value, which means that the
	 *				Equals() method checks whether the two instances have the same
	 *				location.
	 */
	virtual bool Equals(const Object& rhs) const;

	/**
	 * Gets the hash value of the current instance.
	 *
	 * @since 2.0
	 *
	 * @return		The hash value of the current instance
	 * @remarks		Two equal instances must return the same hash value. @n For better performance,
	 *				the used hash function must generate a random distribution for all inputs.
	 */
	virtual long GetHashCode(void) const;

	/**
	 * Sets the x and y coordinates for the current instance of %FloatPoint.
	 *
	 * @since 2.0
	 *
	 * @param[in]	x	The new x-coordinate
	 * @param[in]	y	The new y-coordinate
	 */
	void SetPosition(float x, float y);

	/**
	 * Sets the current instance of %FloatPoint.
	 *
	 * @since 2.0
	 *
	 * @param[in]	point	An instance of %FloatPoint
	 */
	void SetPosition(const FloatPoint& point);

	/**
	 * Translates this %FloatPoint to the indicated distance.
	 *
	 * @since 2.0
	 *
	 * @param[in]	deltaX	The distance to move this point along the x-axis
	 * @param[in]	deltaY	The distance to move this point along the y-axis
	 */
	void Translate(float deltaX, float deltaY);

public:
	/**
	 *	The x-coordinate of the point.
	 *
	 *  @since 2.0
	 */
	float x;

	/**
	 *	The y-coordinate of the point.
	 *
	 *  @since 2.0
	 */
	float y;

private:
	friend class _FloatPointImpl;

	//
	// This variable is for internal use only.
	// Using this variable can cause behavioral, security-related, and consistency-related issues in the application.
	//
	// @since 2.0
	//
	class _FloatPointImpl* __pImpl;

}; // FloatPoint

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_GRAPHIC_FLOATPOINT_H */
