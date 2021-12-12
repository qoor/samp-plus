#pragma once

#include "Packet.h"

class PlayerJoinDataPacket : public Packet
{
private:
	unsigned short pluginVersion;
	RakNet::RakString playerVersionString;

public:
	virtual bool requiresSourcePlayer() const { return false; }
	ePacketType getPacketID() const { return static_cast<ePacketType>(PACKET_PLAYER_JOIN_DATA); }
	unsigned long getFlags() const { return PACKET_HIGH_PRIORITY | PACKET_RELIABLE | PACKET_SEQUENCED; }

	bool read(RakNet::BitStream& bitStream);

	unsigned short getPluginVersion() { return pluginVersion; }
	const std::string& getPlayerVersion() { return playerVersionString.C_String(); }
};
