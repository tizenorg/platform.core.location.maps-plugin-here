//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/**
 * @file		FBaseRtMutex.h
 * @brief		This is the header file for the %Mutex class.
 *
 * This header file contains the declarations of the %Mutex class.
 */

#ifndef _TIZEN_MAPS_MUTEX_H_
#define _TIZEN_MAPS_MUTEX_H_


#include "HereMaps_global.h"
#include "base/BaseObject.h"


TIZEN_MAPS_BEGIN_NAMESPACE


class Mutex
	: public Tizen::Maps::Object
{
public:
	/**
	 *	This is the default constructor for this class.
	 *
	 *	@since 2.0
	 *	@remarks	After creating an instance of this class, you must explicitly call one of
	 *				the Create() methods to initialize the instance.
	 */
	Mutex(void);

	/**
	 *	This is the destructor for this class.
	 *
	 *	@since 2.0
	 */
	virtual ~Mutex(void);

	/**
	 *	Creates an unnamed Mutex.
	 *
	 *	@since 2.0
	 *	@return			An error code
	 *	@exception	E_SUCCESS		The method was successful.
	 *	@exception	E_SYSTEM		An unknown operating system error occurred.
	 */
	result Create(void);

	/**
	 *	Creates a non-recursive mutex.
	 *
	 *	@since 2.0
	 *	@return			An error code
	 *	@exception	E_SUCCESS		The method was successful.
	 *	@exception	E_SYSTEM		An unknown operating system error occurred.
	 */
	result CreateNonRecursiveMutex(void);

	/**
	 *	Creates a named Mutex. @n
	 *	If there is already a Mutex with the specified name, this creates a Mutex which references that particular Mutex.
	 *
	 *	@since 2.0
	 *	@return			An error code
	 *	@param[in]	name			The name of the Mutex
	 *	@exception	E_SUCCESS		The method was successful.
	 *	@exception	E_SYSTEM		An unknown operating system error occurred.
	 */
	result Create(const String& name);

	/**
	 *	Acquires the Mutex if it is not acquired. @n
	 *	If the Mutex is already acquired by another thread,
	 *	the current thread is blocked until the Mutex is released.
	 *
	 *	@since 2.0
	 *	@return			An error code
	 *	@param[in]	timeout			The period during which the thread tries to acquire the mutex
	 *	@exception	E_SUCCESS		The method was successful.
	 *	@exception	E_TIMEOUT		The operation could not be completed within the specified time period. @n
	 *	@exception	E_SYSTEM		An unknown operating system error occurred. @n
	 *								Failed to acquire the Mutex because an OS failure occurred.
	 */
	result Acquire(long timeout);

	/**
	 *	Releases the Mutex.
	 *
	 *	@since 2.0
	 *	@return			An error code
	 *	@exception	E_SUCCESS	The method was successful.
	 *	@exception	E_SYSTEM	An unknown operating system error occurred. @n
	 *							Failed to acquire the Mutex because an OS failure occurred.
	 */
	result Release(void);

	/**
	 *	Acquires the Mutex if it is not acquired. @n
	 *	If the Mutex is already acquired by another thread,
	 *	the current thread is blocked until the Mutex is released.
	 *
	 *	@since 2.0
	 *	@return			An error code
	 *	@exception	E_SUCCESS		The method was successful.
	 *	@exception	E_SYSTEM		An unknown operating system error occurred. @n
	 *								Failed to acquire the Mutex because an OS failure occurred.
	 */
	result Acquire(void);

	/**
	 *	Acquires the mutex if it is not acquired. @n
	 *	If the mutex is already acquired by another thread, E_OBJECT_LOCKED is returned.
	 *
	 *	@since 2.0
	 *
	 *	@return			An error code
	 *	@exception	E_SUCCESS		The method is successful.
	 *	@exception	E_OBJECT_LOCKED		The mutex is already locked.	
	 *	@exception	E_INVALID_STATE		The mutex has not been initialized as yet.
	 *	@exception	E_SYSTEM		A system error has occurred.
	 */
	result TryToAcquire(void);

private:
	pthread_mutex_t* __pMutex;
	String __name;

};



TIZEN_MAPS_END_NAMESPACE
    
#endif // _TIZEN_MAPS_MUTEX_H_

