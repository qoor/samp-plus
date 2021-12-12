#include "StdInc.h"

PacketTranslator::PacketTranslator(PlayerManager* playerManager)
{
	this->playerManager = playerManager;
}

PacketTranslator::~PacketTranslator()
{

}

Packet* PacketTranslator::translate(const RakNet::SystemAddress& socket, ePacketType packetID, RakNet::BitStream& bitStream, int extra)
{
	Packet* temp = NULL;

	switch ((int)packetID)
	{
	case ePacketType::PACKET_PLAYER_JOIN_DATA:
		temp = new PlayerJoinDataPacket();
		break;

	default:
		break;
	}

	if (temp != NULL)
	{
		temp->setSourceSocket(socket);

		Player* sourcePlayer = playerManager->get(socket);

		temp->setSourceElement(sourcePlayer);

		if (sourcePlayer == NULL && temp->requiresSourcePlayer())
		{
			delete temp;
			temp = NULL;
		}
		else
		{
			if (!temp->read(bitStream))
			{
				delete temp;
				temp = NULL;
			}
		}
	}

	return temp;
}
