#pragma once

#include <cstdio>
#include <memory>

#if (defined WIN32 || defined _WIN32)
	#define PATH_SEPARATOR "\\"

	#include <Windows.h>
	#include <direct.h>
#else
	#define PATH_SEPARATOR "/"
	#define _getcwd getcwd

	#include <unistd.h>
	#include <limits.h>
#endif

#include "AMXUtil.h"

class Platform
{
public:
	enum JSONError : int {
		JSON_ERROR_NONE = 0,
		JSON_ERROR_SCRIPTFILES_PATH_NOT_FOUND = 1,
		JSON_ERROR_FAILED_READING_FILE = 2,
		JSON_ERROR_INVALID_JSON_PATH = 3
	};
	
	static char* GetExecutablePath(char pBuf[], size_t sSize = FILENAME_MAX);

	static CALLBACK_RETURN GetLastError(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetLastErrorSecondary(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetErrorSecondaryString(CALLBACK_PARAMS);

	static JSONError Error;
	static int SecondaryError;

};
