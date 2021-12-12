#pragma once

#include "game/CPlayerPed.h"

extern ClientGame* clientGame;
extern CGame* game;
extern CMultiplayer* multiplayer;
extern Network* network;

class ClientManager;
class RPCFunctions;

class ClientGame
{
private:
	bool gameLoaded;
	bool sampGraphicRestored;
	bool beingDeleted;

	CPlayerPed* playerPed;
	ClientManager* manager;

	RPCFunctions* rpcFunctions;

public:
	ClientGame(bool localPlay);
	~ClientGame();

	void doPulsePostFrame();

	bool isGameLoaded() { return game->GetSystemState() == 9; }
	bool isBeingDeleted() { return beingDeleted; }

	void event_OnIngame();

	void resetMapInfo();
	void restoreSAMPGraphic();
	void resetSAMPGraphicWithSettings();

	static void staticPostWorldProcessHandler();

	void postWorldProcessHandler();

	void sendJoinData();
};
