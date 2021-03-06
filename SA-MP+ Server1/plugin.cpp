#include "plugin.h"
#include "Core.h"
#include "Native.h"
#include "Callback.h"

typedef void(*logprintf_t)(const char* format, ...);

logprintf_t logprintf;

extern void *pAMXFunctions;

AMX_NATIVE_INFO projectNatives[] = {
	{"SAMPPlus_ExecuteCallback", Native::ExecuteCallback},
	{"GetServerSAMPPlusVersion", Native::GetServerSAMPPlusVersion},
	{"IsPlayerLowSAMPPlusVersion", Native::IsPlayerLowSAMPPlusVersion},
	{"IsPlayerSAMPPlusConnected", Native::IsPlayerSAMPPlusConnected},
	{"SetWaveHeight", Native::SetWaveHeight},
	{"SetWaveHeightForPlayer", Native::SetWaveHeightForPlayer},
	{"SetSkyGradient", Native::SetSkyGradient},
	{"SetSkyGradientForPlayer", Native::SetSkyGradientForPlayer},
	{"ResetSkyGradient", Native::ResetSkyGradient},
	{"ResetSkyGradientForPlayer", Native::ResetSkyGradientForPlayer},
	{"SetGameSpeed", Native::SetGameSpeed},
	{"SetGameSpeedForPlayer", Native::SetGameSpeedForPlayer},
	{"CreateMarker", Native::CreateMarker},
	{"DestroyMarker", Native::DestroyMarker},
	{0, 0}
};

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = static_cast<logprintf_t>(ppData[PLUGIN_DATA_LOGPRINTF]);

	Debug::initialize("SA-MP_Plus_Debug.txt");

	core = new Core();

	logprintf("[SA-MP+] Plugin version %s loaded.", PLUGIN_VERSION);
	Debug::write("SA-MP+ 플러그인 로드 완료.");

	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	core->update();
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("[SA-MP+] plugin unloaded.");

	return sampgdk::Unload();
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	Callback::getAMXList().push_back(amx);

	return amx_Register(amx, projectNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	Callback::getAMXList().remove(amx);

	return AMX_ERR_NONE;
}
