#include "Platform.h"

#include <cstring>

Platform::JSONError Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
int Platform::SecondaryError = 0;

char* Platform::GetExecutablePath(char pBuf[], const size_t sSize)
{
	return ::_getcwd(pBuf, sSize);
}

CALLBACK_RETURN Platform::GetLastError(CALLBACK_PARAMS)
{
	return Error;
}

CALLBACK_RETURN Platform::GetLastErrorSecondary(CALLBACK_PARAMS)
{
	return SecondaryError;
}

CALLBACK_RETURN Platform::GetErrorSecondaryString(CALLBACK_PARAMS)
{
	cell *out_addr = 0;
	amx_GetAddr(pAmx, pParams[2], &out_addr);
	char* pString = std::strerror(pParams[1]);

	if (pString == nullptr)
		return 0;

	amx_SetString(out_addr, pString, pParams[4], 0, pParams[3]);

	return 1;
}
