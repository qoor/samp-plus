#pragma once

#define SAMP_PLUS_PASSWORD "adsfnkl;anlkbkna;lknqni"

#include <CSingleton.h>

typedef unsigned int uint;

class Settings;
class Network;
class CGame;
class CMultiplayer;
class CDirect3DHookManager;
class CDirectInputHookManager;
class CPlayerPed;
class ClientGame;
class CSAMP;

class Core : public CSingleton<Core>
{
private:
	bool modulesLoaded;
	bool firstPulse;
	bool firstFrame;

	bool isRenderingGrass;
	bool doneFrameRateLimit;
	uint frameRateLimit;
	uint serverFrameRateLimit;
	uint queuedFrameRate;
	bool queuedFrameRateValid;
	CElapsedTimeHD frameRateTimer;

	Settings* settings;
	Network* network;
	CGame* game;
	CMultiplayer* multiplayer;
	ClientGame* clientGame;
	CSAMP* samp;

	CDirect3DHookManager* direct3DHookManager;
	CDirectInputHookManager* directInputHookManager;

public:
	//bool gameStarted;

	Core();
	~Core();

	inline Settings* getSettings() { return settings; }
	inline Network* getNetwork() { return network; }
	inline CGame* getGame() { return game; }
	inline CMultiplayer* getMultiplayer() { return multiplayer; }
	inline CSAMP* getSAMP() { return samp; }
	CPlayerPed* getLocalPed();

	void applyHooks();
	void applyHooks2();

	bool areModulesLoaded();
	void setModulesLoaded(bool loaded);

	void createNetwork();
	void createGame();
	void createMultiplayer();

	void onPostFramePulse();
	void onCrashAverted(uint uiId);
	void onEnterCrashZone(uint uiId);
	void onGameTimerUpdate();

	bool getDebugIdEnabled(uint uiDebugId);
	void logEvent(uint uiDebugId, const char* szType, const char* szContext, const char* szBody, uint uiAddReportLogId);

	bool GetDeviceSelectionEnabled();
	void NotifyRenderingGrass(bool bIsRenderingGrass);
	void applyGameSettings();
	void recalculateFrameRateLimit(uint serverFrameRateLimit = -1);
	void ensureFrameLimitApplied();
	void applyFrameRateLimit(uint overrideRate = -1);
	void applyQueuedFrameRateLimit();
};

extern Core* core;
