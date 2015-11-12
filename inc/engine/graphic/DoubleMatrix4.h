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

#ifndef HERE_DOUBLEMATRIX4_H
#define HERE_DOUBLEMATRIX4_H

#include "common/HereMaps_global.h"
#include "base/BaseObject.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class DoubleMatrix4;

class DoubleMatrix4 : public Object
{
public:
	/**
	 * This is the default constructor for this class. @n
	 * Constructs a 4 X 4 null matrix in which all the elements are zero.
	 *
	 * @since 2.0
	 */
	DoubleMatrix4(void);

	/**
	 * Copying of objects using this copy constructor is allowed.
	 *
	 * @since 2.0
	 *
	 * @param[in]	rhs	An instance of %DoubleMatrix4 to copy
	 */
	DoubleMatrix4(const DoubleMatrix4& rhs);

	/**
	 * Constructs a 4 by 4 matrix initialized to the value in the specified array.
	 *
	 * @since 2.0
	 *
	 * @param[in]	matrix	The matrix with 16 @c double values
	 */
	DoubleMatrix4(const double matrix[4][4]);

	/**
	 * This destructor overrides Object::~Object().
	 *
	 * @since 2.0
	 */
	virtual ~DoubleMatrix4(void);

	/**
	 * Checks whether the current instance and the specified instance of %DoubleMatrix4 are equal.
	 *
	 * @since 2.0
	 *
	 * @return		@c true if all the matrix members of the current instance are equal to the corresponding matrix members in the specified instance, @n
	 *				else @c false
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	bool operator ==(const DoubleMatrix4& rhs) const;

	/**
	 * Checks whether the current instance and the specified instance of %DoubleMatrix4 are not equal.
	 *
	 * @since 2.0
	 *
	 * @return		@c true if all the matrix members of the current instance are not equal to the corresponding matrix members in the specified instance, @n
	 *				else @c false
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	bool operator !=(const DoubleMatrix4& rhs) const;

	/**
	 * Copying of objects using this copy assignment operator is allowed.
	 *
	 * @since 2.0
	 *
	 * @return		A reference to this instance
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	DoubleMatrix4& operator =(const DoubleMatrix4& rhs);

	/**
	 * Assigns the value of the specified instance to the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A reference to this instance
	 * @param[in]	value	The @c double value to assign
	 */
	DoubleMatrix4& operator =(double value);

	/**
	 * Multiplies the value of the specified instance with the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	DoubleMatrix4 operator *(const DoubleMatrix4& rhs) const;

	/**
	 * Multiplies the value to each matrix member of current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	value	The @c double value to multiply
	 */
	DoubleMatrix4 operator *(double value) const;

	/**
	 * Adds the value of the specified instance to the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	DoubleMatrix4 operator +(const DoubleMatrix4& rhs) const;

	/**
	 * Adds the value to each matrix member of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	value	The @c double value to add
	 */
	DoubleMatrix4 operator +(double value) const;

	/**
	 * Subtracts the value of the specified instance from the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	DoubleMatrix4 operator -(const DoubleMatrix4& rhs) const;

	/**
	 * Subtracts the value from each matrix member of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	value	The @c double value to subtract
	 */
	DoubleMatrix4 operator -(double value) const;

	/**
	 * Multiplies the value of the specified instance and the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		The reference to %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	DoubleMatrix4& operator *=(const DoubleMatrix4& rhs);

	/**
	 * Multiplies the value to each matrix member of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A reference to %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	value	The @c double value to multiply
	 */
	DoubleMatrix4& operator *=(double value);

	/**
	 * Adds the value of the specified instance to the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A reference to %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	DoubleMatrix4& operator +=(const DoubleMatrix4& rhs);

	/**
	 * Adds the value to each matrix member of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A reference to %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	value	The @c double value to add
	 */
	DoubleMatrix4& operator +=(double value);

	/**
	 * Subtracts the value of the specified instance from the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A reference to %DoubleMatrix4 cthat contains the resulting value of the operation
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	DoubleMatrix4& operator -=(const DoubleMatrix4& rhs);

	/**
	 * Subtracts the value from each matrix member of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A reference to %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	value	The @c double value to subtract
	 */
	DoubleMatrix4& operator -=(double value);

	/**
	 * Gets an instance of %DoubleMatrix4 resulting from the sum of the value and the specified instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	value	The @c double value to add
	 * @param[in]	rhs	An instance of %DoubleMatrix4
	 */
	friend DoubleMatrix4 operator +(const double& value, const DoubleMatrix4& rhs);

	/**
	 * Gets an instance of %DoubleMatrix4 resulting from the product of the value and the specified instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	value	The @c double value to multiply
	 * @param[in]	rhs		An instance of %DoubleMatrix4
	 */
	friend DoubleMatrix4 operator *(const double& value, const DoubleMatrix4& rhs);

	/**
	 * Gets an instance of %DoubleMatrix4 resulting from the difference between the value and the specified instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @param[in]	value	The @c double value to subtract
	 * @param[in]	rhs		An instance of %DoubleMatrix4
	 */
	friend DoubleMatrix4 operator -(const double& value, const DoubleMatrix4& rhs);

	/**
	 * Checks whether the current instance of %DoubleMatrix4 equals the specified instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		@c true if the values of the current instance is equal to the value of the specified instance, @n
	 *				else @c false
	 * @param[in]	obj	An instance of %DoubleMatrix4
	 * @remarks
	 *				- This method overrides Object::Equals(). 
	 *				- This method uses the values of the Matrix components to compare the two instances.
	 */
	virtual bool Equals(const Object& obj) const;

	/**
	 * Gets the determinant of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		The determinant value of the current instance
	 */
	double GetDeterminant(void) const;

	/**
	 * Gets the inverse matrix of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 * @remarks		This method must be called after checking whether the matrix is invertible or not.
	 */
	DoubleMatrix4 GetInverse(void) const;

	/**
	 * Gets the trace of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		The trace of the current instance
	 */
	double GetTrace(void) const;

	/**
	 * Gets the transpose matrix of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		A new instance of %DoubleMatrix4 that contains the resulting value of the operation
	 */
	DoubleMatrix4 GetTranspose(void) const;

	/**
	 * Checks whether the current instance is an identity matrix.
	 *
	 * @since 2.0
	 *
	 * @return		@c true if the matrix is an identity matrix, @n
	 *				else @c false
	 */
	bool IsIdentity(void) const;

	/**
	 * Checks whether the current matrix is invertible.
	 *
	 * @since 2.0
	 *
	 * @return		@c true if the matrix is invertible, @n
	 *				else @c false
	 */
	bool IsInvertible(void) const;

	/**
	 * Negates the matrix members of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 */
	void Negate(void);

	/**
	 * Sets the identity matrix to the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 */
	void SetAsIdentity(void);

	/**
	 * Sets the inverse matrix to the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @return		An error code
	 * @exception	E_SUCCESS			The method is successful.
	 * @exception	E_INVALID_OPERATION	The current instance is not invertible.
	 */
	result Invert(void);

	/**
	 * Sets the transposed matrix to the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 */
	void Transpose(void);

	/**
	 * Sets the matrix members of the current instance of %DoubleMatrix4 to zero.
	 *
	 * @since 2.0
	 */
	void SetAsNull(void);

	int Compare(const double d1, const double d2) const;

	/**
	 * The matrix of the current instance of %DoubleMatrix4.
	 *
	 * @since 2.0
	 *
	 * @remarks		The column-major order matrix.
	 */
	double matrix[4][4];

private:
	friend class _DoubleMatrix4Impl;
	class _DoubleMatrix4Impl* __pImpl;

}; // DoubleMatrix4


TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_DOUBLEMATRIX4_H */
