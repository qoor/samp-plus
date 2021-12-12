#pragma once

#define DEFAULT_ORDERING_CHANNEL 2

#include "RPCCallback.h"
#include <SA-MP+/PacketType.h>

#include <string>

class Network
{
private:
	bool initialized;
	char* serverAddress;
	unsigned short serverPort;
	bool connected;
	bool serverHasPlugin;
	uint reconnectTime;

	RakNet::RakPeerInterface* raknetPeer;
	RakNet::SocketDescriptor* raknetSocketDescriptor;
	RakNet::SystemAddress* raknetSystemAddress;

public:
	Network(std::string address, std::string port);
	~Network();
	inline bool isInitialized() { return initialized; }
	inline bool isConnected() { return connected; }
	inline bool isServerHasPlugin() { return serverHasPlugin; }
	void tryConnect();
	void disconnect();
	void update();
	uint32_t sendPacket(ePacketType packetType, RakNet::BitStream* sourceBitStream = NULL, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char orderingChannel = DEFAULT_ORDERING_CHANNEL, bool broadCast = false);
};
