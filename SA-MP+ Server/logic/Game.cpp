#include "StdInc.h"

Game* g_pGame = NULL;

Game::Game()
{
	g_pGame = this;

	serverFullyUp = false;

	markerManager = NULL;
	remoteCalls = NULL;
	packetTranslator = NULL;
	playerManager = NULL;

	interiorSoundsEnabled = true;
	overrideRainLevel = false;
	overrideSunSize = false;
	overrideSunColor = false;
	overrideWindVelocity = false;
	overrideFarClip = false;
	overrideFogDistance = false;
	overrideMoonSize = false;

	resetMapInfo();

	cloudsEnabled = true;
}

Game::~Game()
{

}

void Game::resetMapInfo()
{
	gameSpeed = 1.0f;
	aircraftMaxHeight = 800.0f;
	
	skyGradientTR = 0, skyGradientTG = 0, skyGradientTB = 0;
	skyGradientBR = 0, skyGradientBG = 0, skyGradientBB = 0;
	skyGradientHas = false;
	heatHazeSettings = SHeatHazeSettings();
	heatHazeHas = false;
	cloudsEnabled = true;

	g_pGame->setHasWaterColor(false);
	g_pGame->setInteriorSoundsEnabled(true);
	g_pGame->setHasFarClipDistance(false);
	g_pGame->setHasFogDistance(false);
	g_pGame->setHasRainLevel(false);
	g_pGame->setHasSunColor(false);
	g_pGame->setHasSunSize(false);
	g_pGame->setHasWindVelocity(false);
	g_pGame->setHasMoonSize(false);
}

void Game::start()
{
	markerManager = new MarkerManager();
	playerManager = new PlayerManager();
	packetTranslator = new PacketTranslator(playerManager);

	g_pNetwork->registerPacketHandler(Game::staticPacketHandler);
}

void Game::doPulse()
{

}

bool Game::staticPacketHandler(unsigned short packetID, RakNet::SystemAddress address, RakNet::BitStream& bitStream, int extra)
{
	if (packetID == ID_NEW_INCOMING_CONNECTION)
	{
		g_pNetwork->sendPacket(ePacketType::PACKET_PLAYER_REQUEST_VERSION, address);

		return true;
	}

	Packet* packet = g_pGame->packetTranslator->translate(address, static_cast<ePacketType>(packetID), bitStream, extra);

	if (packet != NULL)
	{
		bool handled = g_pGame->processPacket(*packet);

		delete packet;
		return handled;
	}

	return false;
}

bool Game::processPacket(Packet& packet)
{
	ePacketType packetID = packet.getPacketID();

	switch ((int)packetID)
	{
		case PACKET_PLAYER_JOIN_DATA:
		{
			packet_PlayerJoinData(static_cast<PlayerJoinDataPacket&>(packet));

			return true;
		}
	}
}

bool Game::sendPacket(unsigned char packetID, const RakNet::SystemAddress& playerSocket, RakNet::BitStream* bitStream, bool broadCast,
	PacketPriority packetPriority, PacketReliability packetReliability, char packetOrdering)
{
	g_pNetwork->sendPacket((ePacketType)packetID, playerSocket, bitStream, packetPriority, packetReliability, packetOrdering, broadCast);
}

void Game::packet_PlayerJoinData(PlayerJoinDataPacket& packet)
{
	Player* player = playerManager->create(INVALID_PLAYER_ID, packet.getSourceSocket());
}
