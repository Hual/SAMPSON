#include "Server.h"
#include "Platform.h"
#include "AMXUtil.h"
#include <string.h>

void Server::GetScriptfilesPath(char* pBuf, const char* szAppend)
{
	Platform::GetExecutablePath(pBuf);
	const size_t sLen = strlen(szAppend);
	char* pBase = strrchr(pBuf, PATH_SEPARATOR) + 1;

	memcpy(pBase, "scriptfiles", 11);
	*(pBase + 11) = PATH_SEPARATOR;

	if (szAppend)
	{
		memcpy(pBase + 12, szAppend, sLen);
		pBase += sLen;
	}

	*(pBase + 12) = 0;
}