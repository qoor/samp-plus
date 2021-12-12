#include "StdInc.h"

#include "Core.h"

#include "game_sa/CPoolsSA.h"

#include "Game.h"
#include "Memory.h"
#include "PoolManager.h"

#include "Settings.h"
#include "Network.h"
#include "Proxy/CDirect3DHookManager.h"
#include "Proxy/CDirectInputHookManager.h"
#include "game/CGame.h"
#include "multiplayer/CMultiplayer.h"
#include "Client/ClientGame.h"

#include <SA-MP+/Debug.h>

template<>
Core* CSingleton<Core>::m_pSingleton = NULL;

Core::Core() : settings(NULL), direct3DHookManager(NULL), network(NULL), multiplayer(NULL), clientGame(NULL)
{
	Debug::initialize("SA-MP_Plus.log");
	Debug::write("SA-MP+ 시작 초기화 중..");

	modulesLoaded = false;
	firstPulse = true;
	firstFrame = true;
	//gameStarted = false;

	doneFrameRateLimit = false;
	frameRateLimit = 0;
	serverFrameRateLimit = 0;

	settings = new Settings();
	samp = new CSAMP();
	
	direct3DHookManager = new CDirect3DHookManager();
	directInputHookManager = new CDirectInputHookManager();

	Debug::write("DirectX, DirectInput 후킹 매니저 준비 됨.");

	applyHooks();
}

Core::~Core()
{
	delete settings;

	if (network != NULL)
		delete network;

	Debug::finalize();
}

CPlayerPed* Core::getLocalPed()
{
	if (getGame() == NULL || getGame()->GetPools() == NULL)
		return NULL;

	return dynamic_cast<CPlayerPed*>(getGame()->GetPools()->GetPedFromRef(static_cast<DWORD>(1)));
}

void Core::applyHooks()
{
	directInputHookManager->applyHook();
}

void Core::applyHooks2()
{
	Debug::write("DirectInput 최종 후킹 완료 및 DirectX 후킹 준비.");

	direct3DHookManager->applyHook();
}

bool Core::areModulesLoaded()
{
	return modulesLoaded;
}

void Core::setModulesLoaded(bool loaded)
{
	modulesLoaded = loaded;
}

void Core::createNetwork()
{
	network = new Network(settings->getParamData("h"), settings->getParamData("p"));

	Debug::write("네트워크 서비스 준비 됨.");
}

void Core::createGame()
{
	game = GetGameInterface(core);

	Debug::write("게임 인터페이스 준비 됨.");

	if (game->GetGameVersion() >= VERSION_11)
	{
		Debug::write("GTA:SA 버전이 1.0이 아닙니다. 다운그레이드가 필요합니다.");
		exit(0);
	}

	game->DisableVSync();
	samp->detectSAMPVersion();
}

void Core::createMultiplayer()
{
	multiplayer = InitMultiplayerInterface(core);

	Debug::write("멀티플레이어 서비스 준비 됨.");
}

void Core::onPostFramePulse()
{
	static bool bFirstPulse = true;
	if (bFirstPulse)
	{
		bFirstPulse = false;

		applyGameSettings();
		samp->detectSAMPVersion();
	}

	if (game->GetSystemState() == 5)            // GS_INIT_ONCE
	{
		WatchDogCompletedSection("L2");            // gta_sa.set seems ok
		WatchDogCompletedSection("L3");            // No hang on startup
	}

	if (game->GetSystemState() == 9)
	{
		if (firstFrame)
		{
			firstFrame = false;

			//game->DisableVSync();

			Memory::memCopy((void*)0x0401190, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10); // NOP SetGameSpeed to 1.0 every frame
			Memory::memCopy((void*)0x060CD41, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10); // NOP SetGameSpeed to 1.0 on player death

			clientGame = new ClientGame(false);
			PoolManager::initialize();

			Debug::write("ClientGame, PoolManager 로드 됨.");
		}
	}

	if (clientGame != NULL)
	{
		clientGame->doPulsePostFrame();
		samp->doPostFramePulse();
		ensureFrameLimitApplied();
	}
}

void Core::onCrashAverted(uint uiId)
{

}

void Core::onEnterCrashZone(uint uiId)
{

}

void Core::onGameTimerUpdate()
{
	applyQueuedFrameRateLimit();
}

bool Core::getDebugIdEnabled(uint uiId)
{
	return (uiId == 0);
}

void Core::logEvent(uint uiDebugId, const char* szType, const char* szContext, const char* szBody, uint uiAddReportLogId)
{

}

bool Core::GetDeviceSelectionEnabled()
{
	return GetApplicationSettingInt("device-selection-disabled") ? false : true;
}

void Core::NotifyRenderingGrass(bool bIsRenderingGrass)
{
	isRenderingGrass = bIsRenderingGrass;
}

void Core::applyGameSettings()
{
	bool boolValue = false;
	int intValue = 0;

	if (game->GetSettings()->IsWideScreenEnabled())
	{
		getSettings()->getSettingData("HudMatchAspectRatio", boolValue);
		game->GetSettings()->SetAspectRatio(eAspectRatio::ASPECT_RATIO_AUTO, boolValue);
	}
	getSettings()->getSettingData("TyreSmoke", boolValue);
	getMultiplayer()->SetTyreSmokeEnabled(boolValue);
	game->GetSettings()->UpdateFieldOfViewFromSettings();
	game->GetSettings()->ResetVehiclesLODDistance();
	recalculateFrameRateLimit();
}

void Core::recalculateFrameRateLimit(uint serverFrameRateLimit)
{
	if (serverFrameRateLimit != -1)
		this->serverFrameRateLimit = serverFrameRateLimit;

	frameRateLimit = serverFrameRateLimit;

	uint clientConfigRate;

	getSettings()->getSettingData("FrameLimit", clientConfigRate);

	if ((frameRateLimit == 0 || clientConfigRate < frameRateLimit) && clientConfigRate > 0)
		frameRateLimit = clientConfigRate;
}

void Core::ensureFrameLimitApplied()
{
	if (!doneFrameRateLimit)
		applyFrameRateLimit();
	
	doneFrameRateLimit = false;
}

void Core::applyFrameRateLimit(uint overrideRate)
{
	doneFrameRateLimit = true;

	uint useRate = (overrideRate != -1) ? overrideRate : frameRateLimit;

	applyQueuedFrameRateLimit();

	queuedFrameRate = useRate;
	queuedFrameRateValid = true;
}

void Core::applyQueuedFrameRateLimit()
{
	if (queuedFrameRateValid)
	{
		queuedFrameRateValid = false;
		// Calc required time in ms between frames
		const double dTargetTimeToUse = 1000.0 / queuedFrameRate;

		while (true)
		{
			// See if we need to wait
			double dSpare = dTargetTimeToUse - frameRateTimer.Get();

			if (dSpare <= 0.0)
				break;

			if (dSpare >= 2.0)
				Sleep(1);
		}

		frameRateTimer.Reset();
	}
}
