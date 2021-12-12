#pragma once

#include <SA-MP+/RPC.h>

class RPCCallback
{
private:
	static bool initialized;

	static CGame* game;

public:
	static void initialize();
	static inline bool isInitialized() { return initialized; }

	static RPC_CALLBACK setWaveLevel(RPC_ARGS);
	static RPC_CALLBACK setSkyGradient(RPC_ARGS);
	static RPC_CALLBACK resetSkyGradient(RPC_ARGS);
	static RPC_CALLBACK setGameSpeed(RPC_ARGS);
	static RPC_CALLBACK setAircraftMaxHeight(RPC_ARGS);
};
