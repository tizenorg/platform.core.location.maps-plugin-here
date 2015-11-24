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

#ifndef HERE_EVENTDRIVENTHREAD_H
#define HERE_EVENTDRIVENTHREAD_H

#include <glib.h>
#include <sys/eventfd.h>
#include <vector>

#include "common/HereMaps_global.h"
#include "base/BaseObject.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class EventDrivenThread;

typedef std::vector<void*> FireArg_List;

class EventDrivenThread : public Object
{
public:
	/**
	 * This is the default constructor for this class.
	 *
	 * @since 2.0
	 *
	 * @remarks     After creating an instance of this class, one of the
	 *              Construct() methods must be called explicitly to initialize this instance.
	 */
	EventDrivenThread(void);

	/**
	 * This is the destructor for this class.
	 *
	 * @since 2.0
	 *
	 */
	virtual ~EventDrivenThread(void);

	result Construct(bool Delegate);

	void Quit(void);

	int Join(void);

	/**
	 * Sends a user event to the event-driven thread.
	 *
	 * @since 2.0
	 *
	 * @final        Although this method is virtual, it must not be overridden.
	 *               If overridden, it may not work as expected.
	 *
	 * @return       An error code
	 * @param[in]    requestId       	The user-defined event ID
	 * @param[in]    pArgs           	A pointer to the list of arguments
	 * @exception    E_SUCCESS          The method is successful.
	 * @exception    E_INVALID_STATE    The thread is in an invalid state.
	 * @exception    E_OUT_OF_MEMORY    The memory is insufficient.
	 * @exception    E_SYSTEM           A system error has occurred.
	 *
	 * @see          OnUserEventReceivedN()
	 */
	int SendUserEvent(int requestType, void* pArgs);

	void Fire(void* pArgs);

	virtual void FireImpl( void* pArgs) = 0;

	/**
	 * Called when the user event is received.
	 *
	 * @since 2.0
	 *
	 * @param[in]    requestId       The user-defined event ID
	 * @param[in]    pArgs           A pointer to the list of arguments
	 *
	 * @see          SendUserEvent()
	 */
	virtual void OnUserEventReceivedN(int requestId, void* pArgs) = 0;

private:
	bool __constructed;
	bool __is_quit;
	GSource* __pSource;
	GIOChannel* __pChannel;
	GMainContext* __pGmainContext;

	FireArg_List FireArgs;
	pthread_mutex_t FireArgsLock;
	static gboolean OnEventReceived(GIOChannel* pChannel, GIOCondition condition, gpointer data);
	static void __flush(EventDrivenThread *pArg);
}; // EventDrivenThread

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_EVENTDRIVENTHREAD_H */
