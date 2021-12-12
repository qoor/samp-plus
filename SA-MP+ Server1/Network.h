#pragma once

#define MAX_CONNECTION_TIME 5

#define DEFAULT_ORDERING_CHANNEL 2

#include "plugin.h"
#include "ClientSocketInfo.h"
#include "Player.h"

#include <string>
#include <list>
#include <map>
#include <SA-MP+/PacketType.h>
#include <SA-MP+/RPC.h>
#include <RakNet/RakPeerInterface.h>

class Network
{
private:
	bool initialized;

	RakNet::RakPeerInterface* raknetPeer;
	RakNet::SocketDescriptor* raknetSocketDescriptor;

	std::map<unsigned int, Player*> players;
	std::list<ClientSocketInfo*> unhandledConnections;

public:
	Network(std::string address, unsigned short port, unsigned short maxConnections);
	void initialize(const char* address, unsigned short port, unsigned short maxConnections);
	inline bool isInitialized() const { return initialized; }
	bool destroyUnhandledConnection(RakNet::SystemAddress& address);
	Player* handleConnection(unsigned int playerid);
	bool destroyPlayerConnection(unsigned int playerid, bool kick = false);
	void update();
	Player* getPlayerFromPlayerId(unsigned int playerid);
	int getPlayerIdFromSystemAddress(RakNet::SystemAddress& address);
	inline bool isPlayerConnected(unsigned int playerid) { return (players.find(playerid) != players.end()); }
	uint32_t sendPacketEasy(PacketType::ePacketType packetType, const RakNet::SystemAddress destAddress, RakNet::BitStream* sourceBitStream = NULL, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char orderingChannel = DEFAULT_ORDERING_CHANNEL, bool broadCast = false);
	uint32_t sendPlayerPacketEasy(PacketType::ePacketType packetType, unsigned int playerid, RakNet::BitStream* sourceBitStream = NULL, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char orderingChannel = DEFAULT_ORDERING_CHANNEL, bool broadCast = false);
	uint32_t sendRPC(unsigned short rpcid, const RakNet::SystemAddress destAddress, RakNet::BitStream* sourceBitStream = NULL, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char orderingChannel = DEFAULT_ORDERING_CHANNEL, bool broadCast = false);
	uint32_t sendPlayerRPC(unsigned short rpcid, unsigned int playerid, RakNet::BitStream* sourceBitStream = NULL, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char orderingChannel = DEFAULT_ORDERING_CHANNEL, bool broadCast = false);
	void sendBroadcastRPC(unsigned short rpcid, RakNet::BitStream* sourceBitStream = NULL, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char orderingChannel = DEFAULT_ORDERING_CHANNEL, bool broadCast = false);
	void closeConnectionEasy(const RakNet::SystemAddress& destAddress);
};
