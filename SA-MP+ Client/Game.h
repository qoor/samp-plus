#pragma once

#include "game_sa/CGameSA.h"

class Game
{
private:
	static bool worldCreated;
public:
	static void initialize();
	static void onLoad();
	static void onWorldCreate();
	static inline bool isWorldCreated() { return worldCreated; }
};

extern CGameSA* gGame;
