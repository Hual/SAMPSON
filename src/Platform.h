#pragma once

#if (defined WIN32 || defined _WIN32)
	#define PATH_SEPARATOR '\\'
#else
	#define PATH_SEPARATOR '/'
#endif

#if (defined WIN32 || defined _WIN32)
	#include <Windows.h>
#else
	#include <unistd.h>
	#include <limits.h>
	#define MAX_PATH PATH_MAX
#endif

class Platform
{
public:
	static size_t GetExecutablePath(char* pBuf, size_t sSize = MAX_PATH);

};
