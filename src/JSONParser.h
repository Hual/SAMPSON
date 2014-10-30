#pragma once

#include <plugincommon.h>
#include <amx/amx.h>
#include <libjson.h>
#include <string.h>

#include "AMXUtil.h"

class JSONParser
{
public:
	static CALLBACK_RETURN ParseFile(CALLBACK_PARAMS);
	static CALLBACK_RETURN ParseString(CALLBACK_PARAMS);
	static CALLBACK_RETURN Close(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetType(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetNode(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetString(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetBool(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetInt(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetFloat(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetArray(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetArraySize(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetArrayElement(CALLBACK_PARAMS);
	static CALLBACK_RETURN GetName(CALLBACK_PARAMS);

private:
	static JSONNODE* json_get_recursive(JSONNODE* pRootNode, char* szPath, const char cDelim);

};
