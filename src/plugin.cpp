#define PLUGIN_VERSION "0.2.0"

#include <plugincommon.h>
#include <amx/amx.h>

#include "AMXUtil.h"
#include "JSONParser.h"
#include "Platform.h"

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
	AMXUtil::SetAMXFunctions(ppData[PLUGIN_DATA_AMX_EXPORTS]);
	AMXUtil::SetPrintFunction((logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF]);
	AMXUtil::Printf("============== SAMPSON v" PLUGIN_VERSION " by King_Hual loaded ==============");
	return 1;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	AMXUtil::Printf("============= SAMPSON v" PLUGIN_VERSION " by King_Hual unloaded =============");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "json_parse_file", JSONParser::ParseFile },
	{ "json_parse_string", JSONParser::ParseString },
	{ "json_close", JSONParser::Close }, 
	{ "json_get_string", JSONParser::GetString },
	{ "json_get_type", JSONParser::GetType },
	{ "json_get_node", JSONParser::GetNode },
	{ "json_get_bool", JSONParser::GetBool },
	{ "json_get_int", JSONParser::GetInt },
	{ "json_get_float", JSONParser::GetFloat },
	{ "json_get_array", JSONParser::GetArray },
	{ "json_array_count", JSONParser::GetArraySize },
	{ "json_array_at", JSONParser::GetArrayElement },
	{ "json_get_name", JSONParser::GetName },
	{ "json_get_last_error", Platform::GetLastError },
	{ "json_get_last_error_extra", Platform::GetLastErrorSecondary },
	{ "json_get_error_extra_string", Platform::GetErrorSecondaryString },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* pAmx)
{
	AMXUtil::AddAMX(pAmx);
	return amx_Register(pAmx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* pAmx)
{
	AMXUtil::RemoveAMX(pAmx);
	return AMX_ERR_NONE;
}
