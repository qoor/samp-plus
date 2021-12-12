#include "StdInc.h"

PlayerManager::PlayerManager()
{

}

PlayerManager::~PlayerManager()
{
	deleteAll();
}

void PlayerManager::doPulse()
{
	for (std::list<Player*>::const_iterator it = players.begin(); it != players.end(); ++it)
		(*it)->doPulse();
}

Player* PlayerManager::create(unsigned int playerid, const RakNet::SystemAddress& playerSocket)
{
	if (playerid == INVALID_PLAYER_ID)
		return NULL;

	Player* otherPlayer = MapFindRef(socketPlayerMap, playerSocket);

	if (otherPlayer != NULL)
		return NULL;

	Player* player = new Player(this, playerid, playerSocket);

	if (player->getID() == INVALID_PLAYER_ID)
	{
		delete player;
		return NULL;
	}

	return player;
}

unsigned int PlayerManager::countJoined()
{
	unsigned int count = 0;

	for (std::list<Player*>::const_iterator it = players.begin(); it != players.end(); ++it)
	{
		if ((*it)->isJoined())
			++count;
	}

	return count;
}

bool PlayerManager::exists(Player* player)
{
	return players.Contains(player);
}

Player* PlayerManager::get(const RakNet::SystemAddress& playerSocket)
{
	return MapFindRef(socketPlayerMap, playerSocket);
}

Player* PlayerManager::get(int playerid)
{
	if (playerid == INVALID_PLAYER_ID)
		return NULL;

	for (std::list<Player*>::const_iterator it = players.begin(); it != players.end(); ++it)
	{
		if ((*it)->getID() == playerid)
			return *it;
	}

	return NULL;
}

void PlayerManager::deleteAll()
{
	while (!players.empty())
		delete *players.begin();
}

void PlayerManager::broadcastOnlyJoined(const Packet& packet, Player* skip)
{
	SendList sendList;

	for (std::list<Player*>::const_iterator it = players.begin(); it != players.end(); ++it)
	{
		Player* player = *it;

		if (player != skip && player->isJoined())
			sendList.push_back(player);
	}

	PlayerManager::broadcast(packet, sendList);
}

static void doBroadCast(const Packet& packet, const std::list<Player*>& groupSet)
{
	PacketReliability reliability;
	unsigned long flags = packet.getFlags();

	if (flags & PACKET_RELIABLE)
	{
		if (flags & PACKET_SEQUENCED)
			reliability = PacketReliability::RELIABLE_ORDERED;
		else
			reliability = PacketReliability::RELIABLE;
	}
	else
	{
		if (flags & PACKET_SEQUENCED)
			reliability = PacketReliability::UNRELIABLE_SEQUENCED;
		else
			reliability = PacketReliability::UNRELIABLE;
	}

	PacketPriority packetPriority = PacketPriority::MEDIUM_PRIORITY;

	if (flags & PACKET_HIGH_PRIORITY)
		packetPriority = PacketPriority::HIGH_PRIORITY;
	else if (flags & PACKET_LOW_PRIORITY)
		packetPriority = PacketPriority::LOW_PRIORITY;

	for (std::list<Player*>::const_iterator it = groupSet.begin(); it != groupSet.end(); ++it)
	{
		RakNet::BitStream bitStream;
		Player* player = *it;

		if (packet.write(bitStream))
			g_pGame->sendPacket(packet.getPacketID(), player->getSocket(), &bitStream, false, packetPriority, reliability, packet.getPacketOrdering());
	}
}

void PlayerManager::broadcast(const Packet& packet, const std::list<Player*>& sendList)
{
	doBroadCast(packet, sendList);
}
