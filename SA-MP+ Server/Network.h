#pragma once

#define DEFAULT_ORDERING_CHANNEL 2

typedef bool(registerPacketHandler_t)(unsigned short, RakNet::SystemAddress, RakNet::BitStream&, int);

class Network
{
private:
	RakNet::RakPeerInterface* raknetPeer;
	RakNet::SystemAddress* serverAddress;

	bool initialized;

	registerPacketHandler_t* packetHandler;

public:
	Network(std::string serverAddress, unsigned int port, unsigned int maxConnections);
	void initialize(const char* serverAddress, unsigned int port, unsigned int maxConnections);

	bool isInitialized() { return initialized; }

	void closeConnection(const RakNet::SystemAddress& destAddress, bool sendDisconnectionNotification = false);

	void doPulse();

	uint32_t sendPacket(ePacketType packetType, const RakNet::SystemAddress destAddress, RakNet::BitStream* sourceBitStream = NULL, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char orderingChannel = DEFAULT_ORDERING_CHANNEL, bool broadCast = false);
	uint32_t sendRPC(eRPC rpcid, const RakNet::SystemAddress destAddress, RakNet::BitStream* sourceBitStream = NULL, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char orderingChannel = DEFAULT_ORDERING_CHANNEL, bool broadCast = false);

	void registerPacketHandler(registerPacketHandler_t* handler);
};
