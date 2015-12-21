/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "here_base.h"
#include "here_manager.h"
#include <common/CommunicationError.h>
#include <common/ParserError.h>
#include <finder/FinderError.h>
#include <routes/RouterError.h>
#include <tilefetcher/TileFetcherError.h>


HERE_PLUGIN_BEGIN_NAMESPACE

HereBase::HereBase()
{
	m_nRestReqId = 0;
	m_bCanceled = 0;
	m_nReqId = 0;

	m_pCbFunc = NULL;
	m_pUserData = NULL;
}

HereBase::~HereBase()
{
	if (HereManager::GetHandler())
		HereManager::GetHandler()->CloseInstance(m_nReqId);
}

void HereBase::TerminateService(void)
{
	if(m_nRestReqId)
	{
		m_bCanceled = 1;
		return;
	}
	delete this;
}

gint HereBase::GetReqId(void)
{
	return m_nReqId;
}

gint HereBase::GetRestReqId(void)
{
	return m_nRestReqId;
}

gint HereBase::GetErrorCode(const BaseReply& Reply)
{
	ErrorBase *pError = (ErrorBase*)Reply.GetError();
	maps_error_e error = MAPS_ERROR_UNKNOWN;
	CommunicationError *commErr;
	FinderError *finderErr;
	String errMsg = "";


	if (pError)
	{
		ErrorBase::ErrorCategory category = pError->GetErrorCategory();

		switch(category)
		{
		case ErrorBase::ErrorCategory::EC_CommunicationsError:
			commErr = (CommunicationError*)pError;
			errMsg = commErr->ToString();

			if (commErr->GetErrorCode() == CommunicationError::ErrorCode::CE_NetworkError)
				error = MAPS_ERROR_NETWORK_UNREACHABLE;
			else if (commErr->GetErrorCode() == CommunicationError::ErrorCode::CE_RestEngineError)
				error = MAPS_ERROR_INVALID_OPERATION;
			else
				error = HereUtils::ConvertHttpCodeToMapsError(commErr->GetHttpStatusCode());
			break;

		case ErrorBase::ErrorCategory::EC_ParserError:
			errMsg = ((ParserError*)pError)->ToString();
			error = MAPS_ERROR_INVALID_OPERATION;
			break;

		case ErrorBase::ErrorCategory::EC_RouterError:
			errMsg = ((RouterError*)pError)->ToString();
			error = MAPS_ERROR_INVALID_OPERATION;
			break;

		case ErrorBase::ErrorCategory::EC_TileMapError:
			errMsg = ((TileFetcherError*)pError)->ToString();
			error = MAPS_ERROR_INVALID_OPERATION;
			break;

		case ErrorBase::ErrorCategory::EC_FinderError:
			finderErr = (FinderError*)pError;
			//errMsg = finderErr->ToString();

			if (finderErr->GetErrorType() == FinderError::ErrorType::ET_InvalidQueryArguments)
				error = MAPS_ERROR_INVALID_PARAMETER;
			else if (finderErr->GetErrorType() == FinderError::ErrorType::ET_InvalidCredentials)
				error = MAPS_ERROR_KEY_NOT_AVAILABLE;
			else
				error = MAPS_ERROR_INVALID_OPERATION;
			break;
		default:
			error = MAPS_ERROR_INVALID_OPERATION;
			break;
		}
	}

	if (error != MAPS_ERROR_NONE) {
		if (errMsg.size() > 0) errMsg += ". ";
		MAPS_LOGE("ERROR: %s%s (%s, %ld)", errMsg.data(),
			ConverHereErrorToString(ConvertToHereError(error)),
			ConvertMapsErrorToChar(error), error);
	}

	return error;
}

HERE_PLUGIN_END_NAMESPACE
