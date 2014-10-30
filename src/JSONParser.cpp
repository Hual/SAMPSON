#include "JSONParser.h"

#include "Platform.h"
#include "Server.h"
#include "Util.h"

CALLBACK_RETURN JSONParser::ParseFile(CALLBACK_PARAMS)
{
	if (pParams[0] < sizeof(cell))
		return 0;

	JSONNODE* pRoot = NULL;
	char szPath[MAX_PATH];
	char* pReusableChar = AMXUtil::GetStringFromCell(pAmx, pParams[1]);
	Server::GetScriptfilesPath(szPath, pReusableChar);
	delete[] pReusableChar;

	pReusableChar = Util::ReadFile(szPath);

	if (pReusableChar)
	{
		pRoot = json_parse(pReusableChar);
		delete[] pReusableChar;
	}

	return (cell)pRoot;
}

CALLBACK_RETURN JSONParser::ParseString(CALLBACK_PARAMS)
{
	char* pString = AMXUtil::GetStringFromCell(pAmx, pParams[1]);
	JSONNODE* pRoot = json_parse(pString);
	delete[] pString;

	return (cell)pRoot;
}

CALLBACK_RETURN JSONParser::Close(CALLBACK_PARAMS)
{
	if (pParams[0] < sizeof(cell))
		return 0;

	json_free((JSONNODE*)pParams[1]);
	return 1;
}

CALLBACK_RETURN JSONParser::GetType(CALLBACK_PARAMS)
{
	char* pPath = AMXUtil::GetStringFromCell(pAmx, pParams[2]);
	char cType = json_type(json_get_recursive((JSONNODE*)pParams[1], pPath, (char)pParams[3]));
	delete[] pPath;

	return cType;
}

CALLBACK_RETURN JSONParser::GetNode(CALLBACK_PARAMS)
{
	char* pPath = AMXUtil::GetStringFromCell(pAmx, pParams[2]);
	JSONNODE* pNode = json_get_recursive((JSONNODE*)pParams[1], pPath, (char)pParams[3]);
	delete[] pPath;

	return (cell)pNode;
}

CALLBACK_RETURN JSONParser::GetString(CALLBACK_PARAMS)
{
	cell* out_addr = 0;
	char* pPath = AMXUtil::GetStringFromCell(pAmx, pParams[4]);
	amx_GetAddr(pAmx, pParams[2], &out_addr);
	char* pStr = json_as_string(json_get_recursive((JSONNODE*)pParams[1], pPath, (char)pParams[6]));
	amx_SetString(out_addr, pStr, pParams[5], 0, pParams[3]);
	json_free(pStr);
	delete[] pPath;

	return 1;
}

CALLBACK_RETURN JSONParser::GetBool(CALLBACK_PARAMS)
{
	char* pPath = AMXUtil::GetStringFromCell(pAmx, pParams[2]);
	json_bool_t bResult = json_as_bool(json_get_recursive((JSONNODE*)pParams[1], pPath, (char)pParams[3]));
	delete[] pPath;

	return bResult;
}

CALLBACK_RETURN JSONParser::GetInt(CALLBACK_PARAMS)
{
	char* pPath = AMXUtil::GetStringFromCell(pAmx, pParams[2]);
	json_int_t iResult = json_as_int(json_get_recursive((JSONNODE*)pParams[1], pPath, (char)pParams[3]));
	delete[] pPath;
	
	return iResult;
}

CALLBACK_RETURN JSONParser::GetFloat(CALLBACK_PARAMS)
{
	char* pPath = AMXUtil::GetStringFromCell(pAmx, pParams[2]);
	float fNumber = json_as_float(json_get_recursive((JSONNODE*)pParams[1], pPath, (char)pParams[3]));
	delete[] pPath;

	return amx_ftoc(fNumber);
}

CALLBACK_RETURN JSONParser::GetArray(CALLBACK_PARAMS)
{
	char* pPath = AMXUtil::GetStringFromCell(pAmx, pParams[2]);
	JSONNODE* pResult = json_as_array(json_get_recursive((JSONNODE*)pParams[1], pPath, (char)pParams[3]));
	delete[] pPath;

	return (cell)pResult;
}

CALLBACK_RETURN JSONParser::GetArraySize(CALLBACK_PARAMS)
{
	return (cell)json_size((JSONNODE*)pParams[1]);
}

CALLBACK_RETURN JSONParser::GetArrayElement(CALLBACK_PARAMS)
{
	return (cell)json_begin((JSONNODE*)pParams[1])[pParams[2]];
}

CALLBACK_RETURN JSONParser::GetName(CALLBACK_PARAMS)
{
	cell *out_addr = 0;
	amx_GetAddr(pAmx, pParams[2], &out_addr);
	char* pName = json_name((JSONNODE*)pParams[1]);

	if (!pName[0])
		return 0;
	
	amx_SetString(out_addr, pName, pParams[4], 0, pParams[3]);
	return 1;
}

JSONNODE* JSONParser::json_get_recursive(JSONNODE* pRootNode, char* szPath, const char cDelim)
{
	char *pDelim;

	if (!szPath[0])
		return pRootNode;

	while ((pDelim = strchr(szPath, cDelim)) != NULL)
	{
		*pDelim = 0;
		pRootNode = json_get_nocase(pRootNode, szPath);
		szPath = pDelim + 1;
	}

	return json_get_nocase(pRootNode, szPath);
}
