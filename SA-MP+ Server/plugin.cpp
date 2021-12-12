// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "StdInc.h"

typedef void(*logprintf_t)(const char* format, ...);

extern void *pAMXFunctions;

logprintf_t logprintf;
Server* server = NULL;

AMX_NATIVE_INFO projectNatives[] = {
	{0, 0}
};

MTAEXPORT void initServer()
{
	if (server == NULL)
		server = new Server();
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = static_cast<logprintf_t>(ppData[PLUGIN_DATA_LOGPRINTF]);

	server = new Server();

	logprintf("[SA-MP+] Plugin version v%s loaded.", SAMP_PLUS_VERSIONSTRING);
	Debug::write("플러그인 로드 완료.");

	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	server->doPulse();
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	delete server;

	logprintf("[SA-MP+] Plugin unloaded.");

	return sampgdk::Unload();
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
	//Callback::getAmxList().push_back(amx);

	return amx_Register(amx, projectNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
	//Callback::getAmxList().remove(amx);

	return AMX_ERR_NONE;
}
