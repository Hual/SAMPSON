#include "AMXUtil.h"

#include <cstdarg>
#include <cstring>
#include <vector>

extern void* pAMXFunctions;

logprintf_t AMXUtil::Printf;
std::list<AMX*> AMXUtil::m_lAMX;

cell AMXUtil::Invoke(const char* szFunction, const char* szFormat, ...)
{
	cell iReturnValue = 1;
	std::vector<cell> returnValues(m_lAMX.size(), 1);
	size_t idx = 0;
	va_list argPtr;

	for (std::list<AMX*>::iterator it = m_lAMX.begin(); it != m_lAMX.end(); ++it, ++idx) {
		AMX* pAmx = *it;
		int iFuncIdx;

		if (amx_FindPublic(pAmx, szFunction, &iFuncIdx) != 0) {
			continue;
		}

		cell addresses[16];
		unsigned int addrIdx = 0;

		if (szFormat) {
			va_start(argPtr, szFormat);

			for (unsigned int i = 0; i < strlen(szFormat); ++i) {
				if (szFormat[i] == 'i') {
					amx_Push(pAmx, va_arg(argPtr, int));
				}
				else if (szFormat[i] == 's') {
					amx_PushString(pAmx, &addresses[addrIdx++], NULL, va_arg(argPtr, char*), false, false);
				}
				else if (szFormat[i] == 'a') {
					cell iAmxAddr, *pPhysAddr;

					PAWNArray array = va_arg(argPtr, PAWNArray);
					amx_Allot(pAmx, array.length, &iAmxAddr, &pPhysAddr);
					memcpy(pPhysAddr, array.address, array.length * sizeof(cell));
					amx_Push(pAmx, iAmxAddr);

				}
			}

			va_end(argPtr);
		}

		amx_Exec(pAmx, &returnValues[idx], iFuncIdx);

		if (!returnValues[idx]) {
			iReturnValue = 0;
		}

		for (unsigned int i = 0; i < addrIdx; ++i) {
			amx_Release(pAmx, addresses[i]);
		}

	}

	return iReturnValue;
}

void AMXUtil::SetAMXFunctions(void* pFunctionData)
{
	pAMXFunctions = pFunctionData;
}

char* AMXUtil::GetStringFromCell(AMX* pAmx, cell cellString)
{
	cell* pAddr = 0;
	int iLen = 0;
	char* pStr;

	amx_GetAddr(pAmx, cellString, &pAddr);
	amx_StrLen(pAddr, &iLen);
	++iLen;
	pStr = new char[iLen];
	amx_GetString(pStr, pAddr, 0, iLen);
	return pStr;
}
