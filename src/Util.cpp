#include "Util.h"
#include "Platform.h"

#include <stdio.h>

char* Util::ReadFile(const char* szPath)
{
	char* pResult;
	unsigned long ulFileSize;
	size_t bytesRead;
	FILE* pFile = fopen(szPath, "r");
	fseek(pFile, 0, SEEK_END);
	ulFileSize = ftell(pFile);
	rewind(pFile);

	pResult = new char[ulFileSize+1];
	bytesRead = fread(pResult, sizeof(char), ulFileSize, pFile);
	fclose(pFile);
	
	pResult[bytesRead] = 0;

	return pResult;
}
