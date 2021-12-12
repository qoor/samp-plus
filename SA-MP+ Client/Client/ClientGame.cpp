#include "StdInc.h"

#include "ClientGame.h"

#include "rpc/RPCFunctions.h"

ClientGame* clientGame = NULL;
CGame* game = NULL;
CMultiplayer* multiplayer = NULL;
Network* network = NULL;

ClientGame::ClientGame(bool localPlay)
{
	clientGame = this;
	game = core->getGame();
	multiplayer = core->getMultiplayer();
	network = core->getNetwork();
	gameLoaded = false;
	sampGraphicRestored = false;
	beingDeleted = false;
	
	game->InitLocalPlayer();
	playerPed = dynamic_cast<CPlayerPed*>(game->GetPools()->GetPedFromRef(static_cast<DWORD>(1)));

	if (localPlay == false)
		core->getNetwork()->tryConnect();

	manager = new ClientManager();
	rpcFunctions = new RPCFunctions();

	multiplayer->SetPostWorldProcessHandler(ClientGame::staticPostWorldProcessHandler);

	StaticFunctionDefinations(core, game, this, manager);

	Debug::write("클라이언트 게임 준비 됨.");
}

ClientGame::~ClientGame()
{
	beingDeleted = true;

	beingDeleted = false;
}

void ClientGame::doPulsePostFrame()
{
	if (isGameLoaded())
	{
		if (!gameLoaded)
		{
			gameLoaded = true;

			event_OnIngame();
		}
	}

	if (!sampGraphicRestored)
	{
		if (reinterpret_cast<int*>(0x00B6F5F0) != 0)
		{
			restoreSAMPGraphic();

			sampGraphicRestored = true;
		}
	}

	manager->updateStreamers();

	network->update();
}

void ClientGame::event_OnIngame()
{
	resetMapInfo();
}

void ClientGame::resetMapInfo()
{
	game->SetGameSpeed(1.0f);
	game->GetSettings()->ResetVehiclesLODDistance();
	game->GetSettings()->ResetPedsLODDistance();
	game->GetAudioEngine()->ResetAmbientSounds();
	game->GetAudioEngine()->ResetWorldSounds();
	game->GetWorld()->SetJetpackMaxHeight(100.0f);
	game->GetWorld()->SetAircraftMaxHeight(800.0f);
	game->GetWorld()->SetAircraftMaxVelocity(1.5f);

	game->SetBlurLevel(0);
	multiplayer->ResetSunSize();
	multiplayer->ResetMoonSize();

	Debug::write("resetMapInfo 끝");
}

void ClientGame::restoreSAMPGraphic()
{
	// Enable sun for SA-MP
	MemCpy((void*)0x0053C136, "\xE8\x65\x04\x1C\00", 5);

	// Enable grass and plants for SA-MP
	MemCpy((void*)0x0053C159, "\xE8\x42\x0E\x0A\x00", 5);
	
	// Enable motion blur for SA-MP
	MemCpy((void*)0x704E8A, "\xE8\x11\xE2\xFF\xFF", 5);

	// Enable vehicle name show for SA-MP
	MemCpy((void*)0x58FBE9, "\xE8\xB2\xB2\xFF\xFF", 5);

	// Enable zone name show for SA-MP
	MemCpy((void*)0x5720A5, "\xE8\x76\xFE\xFF\xFF", 5);
	MemCpy((void*)0x590099, "\xE8\xC2\x7A\x19\x00", 5);
	MemCpy((void*)0x5952A6, "\xE8\x85\xCF\xFF\xFF", 5);

	resetSAMPGraphicWithSettings();
}

void ClientGame::resetSAMPGraphicWithSettings()
{
	Settings* settings = core->getSettings();
	bool boolValue = false;
	int intValue = 0;

	settings->getSettingData("GrassAndPlants", boolValue);
	core->getGame()->GetSettings()->SetGrassEnabled(boolValue);
	settings->getSettingData("MotionBlur", boolValue);
	core->getGame()->SetBlurLevel((boolValue) ? 36 : 0);
	settings->getSettingData("CarNames", boolValue);
	core->getGame()->GetHud()->SetComponentVisible(eHudComponent::HUD_VEHICLE_NAME, boolValue);
	core->getGame()->GetHud()->SetComponentVisible(eHudComponent::HUD_AREA_NAME, true);
}

void ClientGame::staticPostWorldProcessHandler()
{
	clientGame->postWorldProcessHandler();
}

void ClientGame::postWorldProcessHandler()
{
	manager->getMarkerManager()->doPulse();
}

void ClientGame::sendJoinData()
{
	RakNet::BitStream bitStream;
	RakNet::RakString version("%d.%d.%d", SAMPPLUS_VERSION_MAJOR, SAMPPLUS_VERSION_MINOR, SAMPPLUS_VERSION_MAINTENANCE);

	bitStream.Write(SAMP_PLUS_VERSION);
	bitStream.Write(version);

	network->sendPacket(ePacketType::PACKET_PLAYER_JOIN_DATA, &bitStream);
}
