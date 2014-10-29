#include "AMXUtil.h"
#include <stdarg.h>
#include <string.h>

extern void* pAMXFunctions;

logprintf_t AMXUtil::Printf;
std::list<AMX*> AMXUtil::m_lAMX = std::list<AMX*>();

cell AMXUtil::Invoke(const char* szFunction, const char* szFormat, ...)
{
	cell iReturnValue = 1;
	cell* pReturnValues = new cell[m_lAMX.size()];
	std::fill_n(pReturnValues, m_lAMX.size(), 1);
	size_t idx = 0;
	va_list argPtr;

	for (std::list<AMX*>::iterator it = m_lAMX.begin(); it != m_lAMX.end(); ++it, ++idx)
	{
		AMX* pAmx = *it;
		int iFuncIdx;

		if (amx_FindPublic(pAmx, szFunction, &iFuncIdx) != 0)
			continue;

		cell addresses[16];
		unsigned int addrIdx = 0;

		if (szFormat)
		{
			va_start(argPtr, szFormat);

			for (unsigned int i = 0; i < strlen(szFormat); ++i)
			{
				switch (szFormat[i])
				{
				case 'i':
					amx_Push(pAmx, va_arg(argPtr, int));
					break;

				case 's':
					amx_PushString(pAmx, &addresses[addrIdx++], NULL, va_arg(argPtr, char*), false, false);
					break;

				case 'a':
				{
					cell iAmxAddr, *pPhysAddr;

					PAWNArray array = va_arg(argPtr, PAWNArray);
					amx_Allot(pAmx, array.length, &iAmxAddr, &pPhysAddr);
					memcpy(pPhysAddr, array.address, array.length*sizeof(cell));
					amx_Push(pAmx, iAmxAddr);
					break;
				}
				}
			}

			va_end(argPtr);
		}

		amx_Exec(pAmx, &pReturnValues[idx], iFuncIdx);

		for (unsigned int i = 0; i < addrIdx; ++i)
			amx_Release(pAmx, addresses[i]);

	}

	for (size_t i = 0; i < idx; ++i)
		if (!pReturnValues[i])
			iReturnValue = 0;

	delete[] pReturnValues;

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
