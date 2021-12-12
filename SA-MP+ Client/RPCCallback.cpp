#include "StdInc.h"

#include "RPCCallback.h"

bool RPCCallback::initialized = false;
CGame* RPCCallback::game = NULL;

void RPCCallback::initialize()
{
	if (isInitialized())
		return;

	game = core->getGame();

	assert(game);

	initialized = true;

	RPC::addRPCHandler(eRPC::SET_WAVE_LEVEL, setWaveLevel);
	RPC::addRPCHandler(eRPC::SET_SKY_GRADIENT, setSkyGradient);
	RPC::addRPCHandler(eRPC::RESET_SKY_GRADIENT, resetSkyGradient);
	RPC::addRPCHandler(eRPC::SET_GAME_SPEED, setGameSpeed);
	RPC::addRPCHandler(eRPC::SET_AIRCRAFT_MAX_HEIGHT, setAircraftMaxHeight);
}

RPC_CALLBACK RPCCallback::setWaveLevel(RPC_ARGS)
{
	float waveLevel;

	if (bitStreamData.Read(waveLevel))
		game->GetWaterManager()->SetWaveLevel(waveLevel);
}

RPC_CALLBACK RPCCallback::setSkyGradient(RPC_ARGS)
{
	unsigned char topRed = 0, topGreen = 0, topBlue = 0;
	unsigned char bottomRed = 0, bottomGreen = 0, bottomBlue = 0;

	if (bitStreamData.Read(topRed) && bitStreamData.Read(topGreen) && bitStreamData.Read(topBlue) &&
		bitStreamData.Read(bottomRed) && bitStreamData.Read(bottomGreen) && bitStreamData.Read(bottomBlue))
	{
		core->getMultiplayer()->SetSkyColor(topRed, topGreen, topBlue, bottomRed, bottomGreen, bottomBlue);
	}
}

RPC_CALLBACK RPCCallback::resetSkyGradient(RPC_ARGS)
{
	core->getMultiplayer()->ResetSky();
}

RPC_CALLBACK RPCCallback::setGameSpeed(RPC_ARGS)
{
	float gameSpeed;

	if (bitStreamData.Read(gameSpeed))
		game->SetGameSpeed(gameSpeed);
}

RPC_CALLBACK RPCCallback::setAircraftMaxHeight(RPC_ARGS)
{
	float maxHeight;

	if (bitStreamData.Read(maxHeight))
		game->GetWorld()->SetAircraftMaxHeight(maxHeight);
}
