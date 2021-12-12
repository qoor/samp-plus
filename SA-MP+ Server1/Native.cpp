#include "Native.h"
#include "Callback.h"
#include "Core.h"
#include "Entity.h"

#include <SA-MP+/PacketType.h>
#include <RakNet/BitStream.h>

cell AMX_NATIVE_CALL Native::ExecuteCallback(AMX* amx, cell* params)
{
	return (Callback::process(amx, static_cast<Callback::eCallbackType>(params[1]), &params[2]));
}

cell AMX_NATIVE_CALL Native::GetServerSAMPPlusVersion(AMX* amx, cell* params)
{
	cell* destAddress;
	int length = strlen(SAMP_PLUS_VERSIONSTRING) + 1;
	char* serverVersion = new char[length];

	sprintf_s(serverVersion, length, "%d.%d.%d", SAMPPLUS_VERSION_MAJOR, SAMPPLUS_VERSION_MINOR, SAMPPLUS_VERSION_MAINTENANCE);

	amx_GetAddr(amx, params[1], &destAddress);
	amx_SetString(destAddress, serverVersion, 0, 0, params[2]);

	delete serverVersion;

	return 1;
}

cell AMX_NATIVE_CALL Native::IsPlayerLowSAMPPlusVersion(AMX* amx, cell* params)
{
	Player* player = core->getNetwork()->getPlayerFromPlayerId(params[1]);

	if (player != NULL)
		return player->getSocket()->getClientVersionInt() < SAMP_PLUS_VERSION;
	
	return 0;
}

cell AMX_NATIVE_CALL Native::IsPlayerSAMPPlusConnected(AMX* amx, cell* params)
{
	return (core->getNetwork()->getPlayerFromPlayerId(params[1]) != NULL);
}

cell AMX_NATIVE_CALL Native::SetWaveHeight(AMX* amx, cell* params)
{
	RakNet::BitStream bitStream;

	bitStream.Write(amx_ctof(params[1]));

	core->getNetwork()->sendBroadcastRPC(eRPC::SET_WAVE_HEIGHT, &bitStream);

	return 1;
}

cell AMX_NATIVE_CALL Native::SetWaveHeightForPlayer(AMX* amx, cell* params)
{
	RakNet::BitStream bitStream;

	bitStream.Write(amx_ctof(params[2]));

	return core->getNetwork()->sendPlayerRPC(eRPC::SET_WAVE_HEIGHT, params[1], &bitStream);
}

cell AMX_NATIVE_CALL Native::SetSkyGradient(AMX* amx, cell* params)
{
	RakNet::BitStream bitStream;

	bitStream.Write(params[1]);
	bitStream.Write(params[2]);
	bitStream.Write(params[3]);
	bitStream.Write(params[4]);
	bitStream.Write(params[5]);
	bitStream.Write(params[6]);

	core->getNetwork()->sendBroadcastRPC(eRPC::SET_SKY_GRADIENT, &bitStream);

	return 1;
}

cell AMX_NATIVE_CALL Native::SetSkyGradientForPlayer(AMX* amx, cell* params)
{
	RakNet::BitStream bitStream;

	bitStream.WriteCasted<unsigned char, cell>(params[2]);
	bitStream.WriteCasted<unsigned char, cell>(params[3]);
	bitStream.WriteCasted<unsigned char, cell>(params[4]);
	bitStream.WriteCasted<unsigned char, cell>(params[5]);
	bitStream.WriteCasted<unsigned char, cell>(params[6]);
	bitStream.WriteCasted<unsigned char, cell>(params[7]);

	return core->getNetwork()->sendPlayerRPC(eRPC::SET_SKY_GRADIENT, params[1], &bitStream);
}

cell AMX_NATIVE_CALL Native::ResetSkyGradient(AMX* amx, cell* params)
{
	core->getNetwork()->sendBroadcastRPC(eRPC::RESET_SKY_GRADIENT);

	return 1;
}

cell AMX_NATIVE_CALL Native::ResetSkyGradientForPlayer(AMX* amx, cell* params)
{
	return core->getNetwork()->sendPlayerRPC(eRPC::RESET_SKY_GRADIENT, params[1]);
}

cell AMX_NATIVE_CALL Native::SetGameSpeed(AMX* amx, cell* params)
{
	RakNet::BitStream bitStream;

	bitStream.Write(amx_ctof(params[1]));

	core->getNetwork()->sendBroadcastRPC(eRPC::SET_GAME_SPEED, &bitStream);

	return 1;
}

cell AMX_NATIVE_CALL Native::SetGameSpeedForPlayer(AMX* amx, cell* params)
{
	RakNet::BitStream bitStream;

	bitStream.Write(amx_ctof(params[2]));

	return core->getNetwork()->sendPlayerRPC(eRPC::SET_GAME_SPEED, params[1], &bitStream);
}

cell AMX_NATIVE_CALL Native::SetAircraftMaxHeight(AMX* amx, cell* params)
{
	RakNet::BitStream bitStream;

	bitStream.Write(amx_ctof(params[1]));

	core->getNetwork()->sendBroadcastRPC(eRPC::SET_AIRCRAFT_MAX_HEIGHT, &bitStream);

	return 1;
}

cell AMX_NATIVE_CALL Native::SetAircraftMaxHeightForPlayer(AMX* amx, cell* params)
{
	RakNet::BitStream bitStream;

	bitStream.Write(amx_ctof(params[2]));

	return core->getNetwork()->sendPlayerRPC(eRPC::SET_AIRCRAFT_MAX_HEIGHT, params[1], &bitStream);
}

cell AMX_NATIVE_CALL Native::CreateMarker(AMX* amx, cell* params)
{
	char* type = NULL;

	amx_StrParam(amx, params[4], type);

	if (type != NULL)
	{
		core->getEntity()->createMarker(false, amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]),
			type, amx_ctof(params[5]), params[6], params[7], params[8], params[9]);

		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL Native::DestroyMarker(AMX* amx, cell* params)
{
	return static_cast<int>(core->getEntity()->destroyMarker(params[1]));
}
