#pragma once

#include "packets/Packet.h"

class PacketTranslator
{
private:
	PlayerManager* playerManager;

public:
	PacketTranslator(PlayerManager* playerManager);
	~PacketTranslator();

	Packet* translate(const RakNet::SystemAddress& socket, ePacketType packetID, RakNet::BitStream& bitStream, int extra);
};
