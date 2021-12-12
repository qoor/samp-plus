#pragma once

#include <SA-MP+/RPC.h>

class WorldRPCs
{
public:
	static void loadFunctions();

	DECLARE_RPC(setGameSpeed);
	DECLARE_RPC(setWaveHeight);
	DECLARE_RPC(setSkyGradient);
	DECLARE_RPC(resetSkyGradient);
	DECLARE_RPC(setHeatHaze);
	DECLARE_RPC(resetHeatHaze);
	DECLARE_RPC(setBlurLevel);
	DECLARE_RPC(setFPSLimit);
	DECLARE_RPC(setCloudsEnabled);
	DECLARE_RPC(setAircraftMaxHeight);

	DECLARE_RPC(setRainLevel);
	DECLARE_RPC(setSunSize);
	DECLARE_RPC(setSunColor);
	DECLARE_RPC(setWindVelocity);
	DECLARE_RPC(setFarClipDistance);
	DECLARE_RPC(setFogDistance);
	DECLARE_RPC(resetRainLevel);
	DECLARE_RPC(resetSunSize);
	DECLARE_RPC(resetSunColor);
	DECLARE_RPC(resetWindVelocity);
	DECLARE_RPC(resetFarClipDistance);
	DECLARE_RPC(resetFogDistance);

	DECLARE_RPC(setMoonSize);
	DECLARE_RPC(resetMoonSize);
};
