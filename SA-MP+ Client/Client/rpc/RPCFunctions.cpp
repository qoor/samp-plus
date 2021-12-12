#include "StdInc.h"

#include "RPCFunctions.h"

#include "WorldRPCs.h"
#include "MarkerRPCs.h"

RPCFunctions::RPCFunctions()
{
	addHandlers();
}

void RPCFunctions::addHandlers()
{
	WorldRPCs::loadFunctions();
	MarkerRPCs::loadFunctions();
}
