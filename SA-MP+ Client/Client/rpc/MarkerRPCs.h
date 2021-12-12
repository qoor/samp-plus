#pragma once

#include <SA-MP+/RPC.h>

class MarkerRPCs
{
public:
	static void loadFunctions();

	DECLARE_RPC(createMarker);
	DECLARE_RPC(destroyMarker);
};
