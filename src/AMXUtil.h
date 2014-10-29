#pragma once

#define CALLBACK_RETURN cell AMX_NATIVE_CALL
#define CALLBACK_PARAMS AMX* pAmx, cell* pParams

typedef void(*logprintf_t)(char* format, ...);

#include <list>
#include <amx/amx.h>

struct PAWNArray
{
	cell* address;
	size_t length;
};

class AMXUtil
{
public:
	static cell Invoke(const char* szFunction, const char* szFormat, ...);
	static void SetAMXFunctions(void* pFunctionData);
	static char* GetStringFromCell(AMX* pAmx, cell cellString);
	static inline const std::list<AMX*>& GetAMXList() { return m_lAMX; };
	static inline void AddAMX(AMX* pAmx) { m_lAMX.push_back(pAmx); };
	static inline void RemoveAMX(AMX* pAmx) { m_lAMX.remove(pAmx); };
	static inline void SetPrintFunction(logprintf_t func) { Printf = func; };

	static logprintf_t Printf;

private:
	static std::list<AMX*> m_lAMX;

};
