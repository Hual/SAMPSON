#include <cstring>

#include "Server.h"
#include "Platform.h"
#include "AMXUtil.h"

#define S_SCRIPTFILES_PATH (PATH_SEPARATOR "scriptfiles" PATH_SEPARATOR)

bool Server::GetScriptfilesPath(char pBuf[], const char szAppend[])
{
	if (Platform::GetExecutablePath(pBuf) == nullptr) {
		return false;
	}

	std::strcat(pBuf, S_SCRIPTFILES_PATH);
	
	if (szAppend != nullptr) {
		std::strcat(pBuf, szAppend);
	}

	return true;
}
