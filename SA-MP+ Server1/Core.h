#pragma once

#include "Settings.h"
#include "Network.h"
#include "version.h"

class Entity;

class Core
{
private:
	Settings* settings;
	Network* network;
	Entity* entity;

public:
	Core();
	inline Settings* getSettings() { return settings; }
	inline Network* getNetwork() { return network; }
	inline Entity* getEntity() { return entity; }

	std::string getListeningAddress();
	unsigned short getListeningPort();
	unsigned short getMaxPlayers();
	void update();
};

extern Core* core;
