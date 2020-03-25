/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  Copyright (C) 2010 Marcel Groothuis
 *  https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "rest.h"
#include <memory>
#include <vector>
#include <stdlib.h>
#include <string.h>

using namespace ADDON;

int cRest::Get(const std::string& command, const std::string& arguments, Json::Value& json_response)
{
	std::string response;
	int retval;
	retval = httpRequest(command, arguments, false, response);

	if (retval != E_FAILED)
	{
		if (response.length() != 0)
		{
			std::string jsonReaderError;
			Json::CharReaderBuilder jsonReaderBuilder;
			std::unique_ptr<Json::CharReader> const reader(jsonReaderBuilder.newCharReader());

			if (!reader->parse(response.c_str(), response.c_str() + response.size(), &json_response, &jsonReaderError))
			{
				XBMC->Log(LOG_DEBUG, "Failed to parse %s: \n%s\n",
					response.c_str(),
					jsonReaderError.c_str());
				return E_FAILED;
			}
		}
		else
		{
			XBMC->Log(LOG_DEBUG, "Empty response");
			return E_EMPTYRESPONSE;
		}
	}

	return retval;
}

int cRest::Post(const std::string& command, const std::string& arguments, Json::Value& json_response)
{
	std::string response;
	int retval;
	retval = httpRequest(command, arguments, true, response);

	if (retval != E_FAILED)
	{
		if (response.length() != 0)
		{
			std::string jsonReaderError;
			Json::CharReaderBuilder jsonReaderBuilder;
			std::unique_ptr<Json::CharReader> const reader(jsonReaderBuilder.newCharReader());

			if (!reader->parse(response.c_str(), response.c_str() + response.size(), &json_response, &jsonReaderError))
			{
				XBMC->Log(LOG_DEBUG, "Failed to parse %s: \n%s\n",
					response.c_str(),
					jsonReaderError.c_str());
				return E_FAILED;
			}
		}
		else
		{
			XBMC->Log(LOG_DEBUG, "Empty response");
			return E_EMPTYRESPONSE;
		}
	}

	return retval;
}

int httpRequest(const std::string& command, const std::string& arguments, const bool write, std::string& json_response)
{
	//P8PLATFORM::CLockObject critsec(communication_mutex);		
	std::string strUrl = command;
	
	if (write) {	// POST http request
		void* hFile = XBMC->OpenFileForWrite(strUrl.c_str(), 0);
		if (hFile != NULL)
		{
			int rc = XBMC->WriteFile(hFile, arguments.c_str(), arguments.length());
			if (rc >= 0)
			{
				std::string result;
				result.clear();
				char buffer[1024];
				while (XBMC->ReadFileString(hFile, buffer, 1024))
					result.append(buffer);
				json_response = result;
				return 0;
			}
			XBMC->CloseFile(hFile);
		}
	}
	else {	// GET http request	
		strUrl += arguments;
		void* fileHandle = XBMC->OpenFile(strUrl.c_str(), 0);
		if (fileHandle)
		{
			std::string result;
			char buffer[1024];
			while (XBMC->ReadFileString(fileHandle, buffer, 1024))
				result.append(buffer);

			XBMC->CloseFile(fileHandle);
			json_response = result;
			return 0;
		}
	}

	return -1;
}

