#include "Platform.h"

size_t Platform::GetExecutablePath(char* pBuf, size_t sSize)
{
#if (defined WIN32 || defined _WIN32)
	return GetModuleFileName(NULL, pBuf, sSize);
#else
	ssize_t result = readlink("/proc/self/exe", pBuf, sSize);

	if (result != -1)
		return result;
	else
		return NULL;

#endif
}
