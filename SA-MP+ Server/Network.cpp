#include "StdInc.h"

#define SAMP_PLUS_PASSWORD "adsfnkl;anlkbkna;lknqni"

Network::Network(std::string serverAddress, unsigned int port, unsigned int maxConnections) : initialized(false)
{
	initialize((serverAddress.size() > 0) ? serverAddress.c_str() : NULL, port, maxConnections);
}

void Network::initialize(const char* serverAddress, unsigned int port, unsigned int maxConnections)
{
	raknetPeer = RakNet::RakPeerInterface::GetInstance();

	RakNet::SocketDescriptor socketDescriptor(port, serverAddress);

	if (raknetPeer->Startup(maxConnections, &socketDescriptor, 1) != RakNet::StartupResult::RAKNET_STARTED)
	{
		Debug::write("네트워크를 초기화 할 수 없습니다.");
		exit(EXIT_FAILURE);

		return;
	}

	raknetPeer->SetIncomingPassword(SAMP_PLUS_PASSWORD, strlen(SAMP_PLUS_PASSWORD));
	raknetPeer->SetMaximumIncomingConnections(maxConnections + 1);

	initialized = true;
}

void Network::closeConnection(const RakNet::SystemAddress& destAddress, bool sendDisconnectionNotification)
{
	return raknetPeer->CloseConnection(destAddress, sendDisconnectionNotification);
}

void Network::doPulse()
{
	if (!isInitialized())
		return;

	RakNet::Packet* packet;

	for (packet = raknetPeer->Receive(); packet != NULL; raknetPeer->DeallocatePacket(packet), packet = raknetPeer->Receive())
	{
		if (packet->length <= 0)
			continue;

		RakNet::BitStream bitStream(&packet->data[1], packet->length - 1, false);

		if (packetHandler != NULL)
			packetHandler(packet->data[0], packet->systemAddress, bitStream, 0);
	}
}

uint32_t Network::sendPacket(ePacketType packetType, const RakNet::SystemAddress destAddress, RakNet::BitStream* sourceBitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadCast)
{
	RakNet::BitStream bitStream;

	bitStream.Write(static_cast<unsigned char>(packetType));

	if (sourceBitStream != NULL)
		bitStream.Write(reinterpret_cast<char*>(sourceBitStream->GetData()), sourceBitStream->GetNumberOfBytesUsed());

	return raknetPeer->Send(&bitStream, priority, reliability, orderingChannel, destAddress, broadCast);
}

uint32_t Network::sendRPC(eRPC rpcid, const RakNet::SystemAddress destAddress, RakNet::BitStream* sourceBitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadCast)
{
	RakNet::BitStream bitStream;

	bitStream.Write(static_cast<unsigned short>(rpcid));

	if (sourceBitStream != NULL)
		bitStream.Write(reinterpret_cast<char*>(sourceBitStream->GetData()), sourceBitStream->GetNumberOfBytesUsed());

	return send(ePacketType::PACKET_RPC, destAddress, &bitStream, priority, reliability, orderingChannel, broadCast);
}

void Network::registerPacketHandler(registerPacketHandler_t* handler)
{
	packetHandler = handler;
}
