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

#ifndef HERE_TIMER_H
#define HERE_TIMER_H

#include <glib.h>

#include "common/HereMaps_global.h"
#include "base/BaseObject.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class Timer;

enum TimerStatus
{
	TIMER_STATUS_NOT_ACTIVATED, // This enum value is for internal use only. Using this enum can cause behavioral, security-related, and consistency-related issues in the application.
	TIMER_STATUS_ACTIVATED,     // This enum value is for internal use only. Using this enum can cause behavioral, security-related, and consistency-related issues in the application.
	TIMER_STATUS_CANCELED,      // This enum value is for internal use only. Using this enum can cause behavioral, security-related, and consistency-related issues in the application.
	TIMER_STATUS_EXPIRED,       // This enum value is for internal use only. Using this enum can cause behavioral, security-related, and consistency-related issues in the application.
	TIMER_STATUS_ACTIVATED_REPEATABLE,       // This enum value is for internal use only. Using this enum can cause behavioral, security-related, and consistency-related issues in the application.
};

class ITimerEventListener
{
public:
	/**
	 * This is the destructor for this class.
	 *
	 * @since 2.0
	 */
	virtual ~ITimerEventListener(void) {}

	/**
	 *	Called when the timer has expired.
	 *
	 *  @since 2.0
	 *
	 *	@param[in]	timer	The expired timer
	 */
	virtual void OnTimerExpired(Timer& timer) = 0;

}; // ITimerEventListener

class Timer : public Object
{
public:
	/**
	 * This is the default constructor for this class.
	 *
	 * @since 2.0
	 */
	Timer(void);


	/**
	 * This is the destructor for this class.
	 *
	 * @since 2.0
	 */
	virtual ~Timer(void);

	/**
	 * Initializes this instance of %Timer with the specified listener.
	 *
	 * @since 2.0
	 *
	 * @return		An error code
	 * @param[in]	listener		The event listener
	 * @exception	E_SUCCESS		The method is successful.
	 * @exception	E_OUT_OF_MEMORY	The memory is insufficient.
	 * @exception	E_SYSTEM		A system error has occurred.
	 */
	int Construct(ITimerEventListener& listener);

	/**
	 * Starts the timer.
	 *
	 * @if OSPCOMPAT
	 * @brief <i> [Compatibility] </i>
	 * @endif
	 *
	 * @since 2.0
	 *
	 * @if OSPCOMPAT
     * @compatibility     This method has compatibility issues with Tizen API versions @b prior @b to @b 2.1. @n
     *                    For more information, see @ref CompTimerStartPage "here".
	 * @endif
	 *
	 * @return	An error code
	 * @param[in]	timeout	        	The timeout interval in milliseconds
	 * @exception	E_SUCCESS			The method is successful.
	 * @exception	E_INVALID_ARG		The specified input parameter is invalid.
	 * @exception	E_INVALID_STATE		The timer cannot start as it is in an invalid state.
	 * @exception	E_SYSTEM			A system error has occurred.
	 * @remarks	Once the timer has been started, it cannot be started again until it has expired.
	 * @see		Cancel()
	 */
	int Start(int timeout);

	/**
	 * @page                    CompTimerStartPage Compatibility for Start(int timeout)
	 * @section                 CompTimerStartPageIssueSection Issues
	 * Implementation of this method in Tizen API versions prior to 2.1 has the following issue: @n
	 * -# The method returns @c E_INVALID_ARG if timeout is equal to zero.
	 *
	 * @section                 CompTimerStartPageSolutionSection Resolutions
	 * The issue mentioned above is resolved in Tizen API version 2.1, and it is recommended to use Tizen API version 2.1 or above.
	 * -# In case of zero, %Timer sets the timeout to the best possible minimum interval without returning @c E_INVALID_ARG.
	 */

	/**
	 * Starts the timer. @n
	 * The timer expires repeatedly until it is cancelled.
	 *
	 * @since 2.0
	 *
	 * @return	An error code
	 * @param[in]	interval			The timeout interval in milliseconds
	 * @exception	E_SUCCESS			The method is successful.
	 * @exception	E_INVALID_ARG		The specified input parameter is invalid.
         * @exception   E_INVALID_STATE The timer cannot start as it is in an invalid state.
	 * @exception	E_SYSTEM			A system error has occurred.
	 * @remarks     To stop the timer expiration or restart the timer, the timer must be cancelled.
	 * @see         Cancel()
	 */
	int StartAsRepeatable(int interval);

	/**
	 * Cancels the timer.
	 *
	 * @since 2.0
	 *
	 * @return		An error code
	 * @exception	E_SUCCESS	The method is successful.
	 * @exception	E_SYSTEM	A system error has occurred.
	 * @remarks	The started timer can be cancelled when it does not get expired. @n
	 *			If the timer has already expired, this method also returns @c E_SUCCESS which causes the same effect as when cancelled normally.
	 */
	int Cancel(void);

private:
	Timer(const Timer& rhs);

	Timer& operator =(const Timer& rhs);

private:
	friend class _TimerImpl;
	class _TimerImpl * __pTimerImpl;

}; // Timer

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_TIMER_H */
