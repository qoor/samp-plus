#include "StdInc.h"

RPCFunctions* g_pRPCFunctions = NULL;
extern Game* g_pGame;

Player* RPCFunctions::sourcePlayer;

static PlayerManager* playerManager;

RPCFunctions::RPCFunctions()
{
	g_pRPCFunctions = this;

	playerManager = g_pGame->getPlayerManager();
	addHandlers();
}

RPCFunctions::~RPCFunctions()
{
	for (std::vector<RPCHandler*>::iterator it = rpcHandlers.begin(); it != rpcHandlers.end(); ++it)
		delete *it;

	rpcHandlers.clear();

	g_pRPCFunctions = NULL;
}