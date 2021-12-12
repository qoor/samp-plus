#pragma once

#include "plugin.h"

namespace Native
{
	cell AMX_NATIVE_CALL ExecuteCallback(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL GetServerSAMPPlusVersion(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL IsPlayerLowSAMPPlusVersion(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL IsPlayerSAMPPlusConnected(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetWaveHeight(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetWaveHeightForPlayer(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetSkyGradient(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetSkyGradientForPlayer(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ResetSkyGradient(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL ResetSkyGradientForPlayer(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetGameSpeed(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetGameSpeedForPlayer(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetAircraftMaxHeight(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL SetAircraftMaxHeightForPlayer(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL CreateMarker(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DestroyMarker(AMX* amx, cell* params);
}
