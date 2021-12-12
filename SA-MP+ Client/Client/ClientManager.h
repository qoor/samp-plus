#pragma once

#include "ClientMarkerManager.h"

class ClientManager
{
private:
	ClientStreamer* markerStreamer;

	ClientMarkerManager* markerManager;

public:
	ClientManager();
	~ClientManager();

	bool isGameLoaded() { return game->GetSystemState() == 9 && network->isInitialized(); }

	void doPulse();
	void updateStreamers();
	void unreferenceEntity(ClientEntity* entity);

	ClientStreamer* getMarkerStreamer() { return markerStreamer; }

	ClientMarkerManager* getMarkerManager() { return markerManager; }
};
