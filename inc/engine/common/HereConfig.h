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

#ifndef HERE_CONFIG_H
#define HERE_CONFIG_H

#include "common/HereMaps_global.h"
#include "base/BaseObject.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class EXPORT_API HereConfig
{
public:
	HereConfig();
	~HereConfig();
	static void SetProxyAddress(char* address);
	static char* GetProxyAddress(void);
	static void Shutdown(void);

//private:
	static char* __proxy_address;
};

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_CONFIG_H */

