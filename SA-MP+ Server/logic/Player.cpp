#include "StdInc.h"

Player::Player(PlayerManager* playerManager, unsigned int playerid, const RakNet::SystemAddress& socket) : Ped(nullptr, playerid)
{
	this->playerManager = playerManager;
	playerSocket = socket;

	pluginVersion = 0;
	joined = false;

	blurLevel = 0;

	playerManager->addToList(this);
}

Player::~Player()
{
	unlink();
}

void Player::unlink()
{
	playerManager->removeFromList(this);
}

void Player::doPulse()
{

}

const char* Player::getSourceIP()
{
	if (ipString.empty())
	{
		char ip[22];

		strcpy_s(ip, sizeof(ip), playerSocket.ToString(false));
		ipString = ip;
	}
	
	return ipString.c_str();
}

uint Player::send(const Packet& packet)
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

	uint byteSend = 0;
	RakNet::BitStream bitStream;

	if (packet.write(bitStream))
	{
		byteSend = bitStream.GetNumberOfBytesUsed();
		g_pGame->sendPacket(packet.getPacketID(), playerSocket, &bitStream, false, packetPriority, reliability, packet.getPacketOrdering());
	}

	return byteSend;
}
