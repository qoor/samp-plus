#include "StdInc.h"

#include "WorldRPCs.h"

void WorldRPCs::loadFunctions()
{
	RPC::addRPCHandler(SET_GAME_SPEED, setGameSpeed);
	RPC::addRPCHandler(SET_WAVE_HEIGHT, setWaveHeight);
	RPC::addRPCHandler(SET_SKY_GRADIENT, setSkyGradient);
	RPC::addRPCHandler(RESET_SKY_GRADIENT, resetSkyGradient);
	RPC::addRPCHandler(SET_HEAT_HAZE, setHeatHaze);
	RPC::addRPCHandler(RESET_HEAT_HAZE, resetHeatHaze);
	RPC::addRPCHandler(SET_BLUR_LEVEL, setBlurLevel);
	RPC::addRPCHandler(SET_FPS_LIMIT, setFPSLimit);
	RPC::addRPCHandler(SET_CLOUDS_ENABLED, setCloudsEnabled);
	RPC::addRPCHandler(SET_AIRCRAFT_MAX_HEIGHT, setAircraftMaxHeight);

	RPC::addRPCHandler(SET_RAIN_LEVEL, setRainLevel);
	RPC::addRPCHandler(SET_SUN_SIZE, setSunSize);
	RPC::addRPCHandler(SET_SUN_COLOR, setSunColor);
	RPC::addRPCHandler(SET_WIND_VELOCITY, setWindVelocity);
	RPC::addRPCHandler(SET_FAR_CLIP_DISTANCE, setFarClipDistance);
	RPC::addRPCHandler(SET_FOG_DISTANCE, setFogDistance);
	RPC::addRPCHandler(RESET_RAIN_LEVEL, resetRainLevel);
	RPC::addRPCHandler(RESET_SUN_SIZE, resetSunSize);
	RPC::addRPCHandler(RESET_SUN_COLOR, resetSunColor);
	RPC::addRPCHandler(RESET_WIND_VELOCITY, resetWindVelocity);
	RPC::addRPCHandler(RESET_FAR_CLIP_DISTANCE, resetFarClipDistance);
	RPC::addRPCHandler(RESET_FOG_DISTANCE, resetFogDistance);

	RPC::addRPCHandler(SET_MOON_SIZE, setMoonSize);
	RPC::addRPCHandler(RESET_MOON_SIZE, resetMoonSize);
}

void WorldRPCs::setGameSpeed(RPC_ARGS)
{
	float speed;

	if (bitStream.Read(speed))
		game->SetGameSpeed(speed);
}

void WorldRPCs::setWaveHeight(RPC_ARGS)
{
	float waveHeight;

	if (bitStream.Read(waveHeight))
		game->GetWaterManager()->SetWaveLevel(waveHeight);
}

void WorldRPCs::setSkyGradient(RPC_ARGS)
{
	unsigned char topRed = 0, topGreen = 0, topBlue = 0;
	unsigned char bottomRed = 0, bottomGreen = 0, bottomBlue = 0;

	if (bitStream.Read(topRed) && bitStream.Read(topGreen) && bitStream.Read(topBlue) &&
		bitStream.Read(bottomRed) && bitStream.Read(bottomGreen) && bitStream.Read(bottomBlue))
	{
		multiplayer->SetSkyColor(topRed, topGreen, topBlue, bottomRed, bottomGreen, bottomBlue);
	}
}

void WorldRPCs::resetSkyGradient(RPC_ARGS)
{
	multiplayer->ResetSky();
}

void WorldRPCs::setHeatHaze(RPC_ARGS)
{
	SHeatHazeSettings heatHaze;

	if (bitStream.Read((char*)&heatHaze, sizeof(SHeatHazeSettings)))
		multiplayer->SetHeatHaze(heatHaze);
}

void WorldRPCs::resetHeatHaze(RPC_ARGS)
{
	multiplayer->ResetHeatHaze();
}

void WorldRPCs::setBlurLevel(RPC_ARGS)
{
	unsigned char blurLevel;

	if (bitStream.Read(blurLevel))
		game->SetBlurLevel(blurLevel);
}

void WorldRPCs::setFPSLimit(RPC_ARGS)
{
	short fpsLimit;

	bitStream.Read(fpsLimit);

	core->recalculateFrameRateLimit(fpsLimit);
}

void WorldRPCs::setCloudsEnabled(RPC_ARGS)
{
	unsigned char isEnabled;

	bitStream.Read(isEnabled);

	bool enabled = (isEnabled == 1);

	multiplayer->SetCloudsEnabled(enabled);
}

void WorldRPCs::setAircraftMaxHeight(RPC_ARGS)
{
	float maxHeight;

	if (bitStream.Read(maxHeight))
		multiplayer->SetAircraftMaxHeight(maxHeight);
}

void WorldRPCs::setRainLevel(RPC_ARGS)
{
	float rainLevel;

	if (bitStream.Read(rainLevel))
		game->GetWeather()->SetAmountOfRain(rainLevel);
}

void WorldRPCs::setSunSize(RPC_ARGS)
{
	float sunSize;

	if (bitStream.Read(sunSize))
		multiplayer->SetSunSize(sunSize);
}

void WorldRPCs::setSunColor(RPC_ARGS)
{
	unsigned char coreR, coreG, coreB;
	unsigned char coronaR, coronaG, coronaB;

	if (bitStream.Read(coreR) && bitStream.Read(coreG) && bitStream.Read(coreB) &&
		bitStream.Read(coronaR) && bitStream.Read(coronaG) && bitStream.Read(coronaB))
	{
		multiplayer->SetSunColor(coreR, coreG, coreB, coronaR, coronaG, coronaB);
	}
}

void WorldRPCs::setWindVelocity(RPC_ARGS)
{
	float velX, velY, velZ;

	if (bitStream.Read(velX) && bitStream.Read(velY) && bitStream.Read(velZ))
		multiplayer->SetWindVelocity(velX, velY, velZ);
}

void WorldRPCs::setFarClipDistance(RPC_ARGS)
{
	float farClip;

	if (bitStream.Read(farClip))
		multiplayer->SetFarClipDistance(farClip);
}

void WorldRPCs::setFogDistance(RPC_ARGS)
{
	float fogDist;

	if (bitStream.Read(fogDist))
		multiplayer->SetFogDistance(fogDist);
}

void WorldRPCs::resetRainLevel(RPC_ARGS)
{
	game->GetWeather()->ResetAmountOfRain();
}

void WorldRPCs::resetSunSize(RPC_ARGS)
{
	multiplayer->ResetSunSize();
}

void WorldRPCs::resetSunColor(RPC_ARGS)
{
	multiplayer->ResetSunColor();
}

void WorldRPCs::resetWindVelocity(RPC_ARGS)
{
	multiplayer->RestoreWindVelocity();
}

void WorldRPCs::resetFarClipDistance(RPC_ARGS)
{
	multiplayer->RestoreFarClipDistance();
}

void WorldRPCs::resetFogDistance(RPC_ARGS)
{
	multiplayer->RestoreFogDistance();
}

void WorldRPCs::setMoonSize(RPC_ARGS)
{
	int moonSize;

	if (bitStream.Read(moonSize))
		multiplayer->SetMoonSize(moonSize);
}

void WorldRPCs::resetMoonSize(RPC_ARGS)
{
	multiplayer->ResetMoonSize();
}
