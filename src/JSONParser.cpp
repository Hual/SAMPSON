#include "JSONParser.h"

#include "Platform.h"
#include "Server.h"
#include "Util.h"

CALLBACK_RETURN JSONParser::ParseFile(CALLBACK_PARAMS)
{
	const JSONNODE* pRoot = nullptr;
	char szPath[FILENAME_MAX] = { 0 };

	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	{
		const std::unique_ptr<const char> inputString(AMXUtil::GetStringFromCell(pAmx, pParams[1]));
		
		if (!Server::GetScriptfilesPath(szPath, inputString.get())) {
			Platform::Error = Platform::JSONError::JSON_ERROR_SCRIPTFILES_PATH_NOT_FOUND;
			return 0;
		}
	}

	const std::unique_ptr<const char> fileString(Util::ReadFile(szPath));
	
	if (fileString) {
		pRoot = ::json_parse(fileString.get());
	}
	else {
		Platform::Error = Platform::JSONError::JSON_ERROR_FAILED_READING_FILE;
		return 0;
	}

	return reinterpret_cast<cell>(pRoot);
}

CALLBACK_RETURN JSONParser::ParseString(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	const std::unique_ptr<const char> pString(AMXUtil::GetStringFromCell(pAmx, pParams[1]));
	const JSONNODE* pRoot = json_parse(pString.get());

	return reinterpret_cast<cell>(pRoot);
}

CALLBACK_RETURN JSONParser::Close(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	json_free(reinterpret_cast<JSONNODE*>(pParams[1]));
	return 1;
}

CALLBACK_RETURN JSONParser::GetType(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	const std::unique_ptr<char> pPath(AMXUtil::GetStringFromCell(pAmx, pParams[2]));
	char cType = json_type(json_get_recursive(reinterpret_cast<JSONNODE*>(pParams[1]), pPath.get(), static_cast<char>(pParams[3])));

	return cType;
}

CALLBACK_RETURN JSONParser::GetNode(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	const std::unique_ptr<char> pPath(AMXUtil::GetStringFromCell(pAmx, pParams[2]));
	const JSONNODE* pNode = json_get_recursive(reinterpret_cast<JSONNODE*>(pParams[1]), pPath.get(), static_cast<char>(pParams[3]));

	return reinterpret_cast<cell>(pNode);
}

CALLBACK_RETURN JSONParser::GetString(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	const std::unique_ptr<char> pPath(AMXUtil::GetStringFromCell(pAmx, pParams[4]));
	cell* out_addr = 0;
	amx_GetAddr(pAmx, pParams[2], &out_addr);
	char* pStr = json_as_string(json_get_recursive(reinterpret_cast<JSONNODE*>(pParams[1]), pPath.get(), static_cast<char>(pParams[6])));

	if (pStr == nullptr) {
		return 0;
	}

	amx_SetString(out_addr, pStr, pParams[5], 0, pParams[3]);
	json_free(pStr);

	return 1;
}

CALLBACK_RETURN JSONParser::GetBool(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	const std::unique_ptr<char> pPath(AMXUtil::GetStringFromCell(pAmx, pParams[2]));
	json_bool_t bResult = json_as_bool(json_get_recursive(reinterpret_cast<JSONNODE*>(pParams[1]), pPath.get(), static_cast<char>(pParams[3])));

	return bResult;
}

CALLBACK_RETURN JSONParser::GetInt(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	const std::unique_ptr<char> pPath(AMXUtil::GetStringFromCell(pAmx, pParams[2]));
	json_int_t iResult = json_as_int(json_get_recursive(reinterpret_cast<JSONNODE*>(pParams[1]), pPath.get(), static_cast<char>(pParams[3])));
	
	return iResult;
}

CALLBACK_RETURN JSONParser::GetFloat(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	const std::unique_ptr<char> pPath(AMXUtil::GetStringFromCell(pAmx, pParams[2]));
	float fNumber = json_as_float(json_get_recursive(reinterpret_cast<JSONNODE*>(pParams[1]), pPath.get(), static_cast<char>(pParams[3])));

	return amx_ftoc(fNumber);
}

CALLBACK_RETURN JSONParser::GetArray(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	const std::unique_ptr<char> pPath(AMXUtil::GetStringFromCell(pAmx, pParams[2]));
	JSONNODE* pResult = json_as_array(json_get_recursive(reinterpret_cast<JSONNODE*>(pParams[1]), pPath.get(), static_cast<char>(pParams[3])));

	return reinterpret_cast<cell>(pResult);
}

CALLBACK_RETURN JSONParser::GetArraySize(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	return json_size(reinterpret_cast<JSONNODE*>(pParams[1]));
}

CALLBACK_RETURN JSONParser::GetArrayElement(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	return reinterpret_cast<cell>(json_begin(reinterpret_cast<JSONNODE*>(pParams[1]))[pParams[2]]);
}

CALLBACK_RETURN JSONParser::GetName(CALLBACK_PARAMS)
{
	Platform::Error = Platform::JSONError::JSON_ERROR_NONE;
	Platform::SecondaryError = 0;

	cell *out_addr = 0;
	amx_GetAddr(pAmx, pParams[2], &out_addr);
	char* pName = json_name(reinterpret_cast<JSONNODE*>(pParams[1]));

	if (pName == nullptr || !pName[0])
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

		if (pRootNode == nullptr) {
			Platform::Error = Platform::JSONError::JSON_ERROR_INVALID_JSON_PATH;
			return nullptr;
		}

		szPath = pDelim + 1;
	}

	pRootNode = json_get_nocase(pRootNode, szPath);

	if (pRootNode == nullptr) {
		Platform::Error = Platform::JSONError::JSON_ERROR_INVALID_JSON_PATH;
		return nullptr;
	}

	return pRootNode;
}
