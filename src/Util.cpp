#include "Util.h"

#include <cstdio>

#include "Platform.h"
#include "AMXUtil.h"

char* Util::ReadFile(const char szPath[])
{
	FILE* pFile = nullptr;
	char* pResult = nullptr;
	long lFileSize = 0L;
	size_t bytesRead = 0U;

	if ((pFile = std::fopen(szPath, "rb")) == nullptr) {
		Platform::SecondaryError = errno;
		return nullptr;
	}

	if (std::fseek(pFile, 0, SEEK_END) != 0) {
		Platform::SecondaryError = errno;
		std::fclose(pFile);
		return nullptr; 
	}
	
	if ((lFileSize = std::ftell(pFile)) == -1L) {
		Platform::SecondaryError = errno;
		std::fclose(pFile);
		return nullptr;
	}

	std::rewind(pFile);

	pResult = new char[lFileSize + 1];
	if ((bytesRead = std::fread(pResult, sizeof(char), lFileSize, pFile)) != lFileSize) {
		std::fclose(pFile);
		return nullptr;
	}

	std::fclose(pFile);

	pResult[bytesRead] = 0;
	return pResult;
}
