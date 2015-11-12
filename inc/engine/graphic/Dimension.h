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

#ifndef HERE_GRAPHIC_DIMENSION_H
#define HERE_GRAPHIC_DIMENSION_H

#include "common/HereMaps_global.h"
#include "base/BaseObject.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class Dimension;

class EXPORT_API Dimension : public Object
{
public:
	/**
	 * This is the default constructor for this class. @n
	 * This constructor initializes an instance of %Dimension with the width and the height set as @c 0.
	 *
	 * @since	2.0
	 */
	Dimension(void);

	/**
	* This is the copy constructor for the %Dimension class.
	*
	* @since 2.0
	*
	* @param[in]	rhs		An instance of %Dimension
	*/
	Dimension(const Dimension& rhs);

	/**
	 * Initializes an instance of %Dimension with the specified values of width and height.
	 *
	 * @since			2.0
	 *
	 * @param[in]	width	The width to set
	 * @param[in]	height	The height to set
	 */
	Dimension(int width, int height);

	/**
	 * This is the destructor for this class.
	 *
	 * @since	2.0
	 */
	virtual ~Dimension(void);

	/**
	* Assigns the value of the specified instance to the current instance of %Dimension.
	*
	* @since 2.0
	*
	* @param[in]	rhs		An instance of %Dimension
	*/
	Dimension& operator =(const Dimension& rhs);

	/**
	 * Checks whether the two instances of %Dimension have equal width and height values.
	 *
	 * @since			2.0
	 *
	 * @return		@c true if the values of the width and height of the two instances of %Dimension are equal, @n
	 *				else @c false
	 * @param[in]	rhs		An instance of %Dimension
	 */
	bool operator ==(const Dimension& rhs) const;

	/**
	 * Checks whether the two instances of %Dimension have different width and height values.
	 *
	 * @since			2.0
	 *
	 * @return		@c true if the values of the width and the height of the two instances of %Dimension are not equal, @n
	 *				else @c false
	 * @param[in]	rhs		An instance of %Dimension
	 */
	bool operator !=(const Dimension& rhs) const;

	/**
	 * Checks whether the value of the current instance of %Dimension equals the value of the specified instance.
	 *
	 * @since			2.0
	 *
	 * @return		@c true if the value of the current instance equals the value of the specified instance, @n
	 *               else @c false
	 * @param[in]	rhs		An instance of %Dimension
	 * @remarks		The %Dimension class has a semantic value, which means that the
	 *				Equals() method checks whether the two instances have the same width and height.
	 */
	virtual bool Equals(const Object& rhs) const;

	/**
	 * Gets the hash value of the current instance.
	 *
	 * @since		2.0
	 *
	 * @return		The hash value of the current instance
	 * @remarks		Two equal instances must return the same hash value. For better performance,
	 *				the used hash function must generate a random distribution for all inputs.
	 */
	virtual long GetHashCode(void) const;

	/**
	 * Sets the size of the current instance of %Dimension.
	 *
	 * @since			2.0
	 *
	 * @param[in]	width		The new width
	 * @param[in]	height		The new height
	 */
	void SetSize(int width, int height);

public:
	/**
	 * The width of the current instance of %Dimension.
	 *
	 * @since	2.0
	 */
	int width;

	/**
	 * The height of the current instance of %Dimension.
	 *
	 * @since	2.0
	 */
	int height;

private:
	friend class _DimensionImpl;

	//
	// This variable is for internal use only.
	// Using this variable can cause behavioral, security-related, and consistency-related issues in the application.
	//
	// @since 2.0
	//
	class _DimensionImpl * __pImpl;

}; // Dimension

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_GRAPHIC_DIMENSION_H */
