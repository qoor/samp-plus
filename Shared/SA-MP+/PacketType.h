#pragma once

enum ePacketType : unsigned char
{
	PACKET_PLAYER_REGISTERED = 0x87,
	PACKET_PLAYER_REQUEST_VERSION,
	PACKET_PLAYER_JOIN_DATA,
	PACKET_PLAYER_PROPER_DISCONNECT,
	PACKET_PLAYER_PROPER_KICK,
	PACKET_CONNECTION_REJECTED,
	PACKET_RPC
};
