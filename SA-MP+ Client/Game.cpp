#include "StdInc.h"

#include "Game.h"
#include "Memory.h"

CGameSA* gGame = NULL;
bool Game::worldCreated = false;

void Game::initialize()
{
	Debug::write("게임 초기화 성공.");
}

void Game::onLoad()
{
	if (core->getSettings()->isValidParamData("b") || !core->getSettings()->isValidParamData("h"))
		return;

	SetInitialVirtualProtect();

	Memory::unprotectMemory(0x72C659, 0x12);
	Memory::unprotectMemory(0xC812E8, sizeof(float));

	core->startMainProcess();

	gGame = new CGameSA();
}

void Game::onWorldCreate()
{
	if (isWorldCreated())
		return;

	onLoad();

	worldCreated = true;

	Debug::write("onWorldCreate 로드 됨.");
}
