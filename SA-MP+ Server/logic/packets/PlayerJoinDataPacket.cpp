#include "StdInc.h"

bool PlayerJoinDataPacket::read(RakNet::BitStream& bitStream)
{
	if (!bitStream.Read(pluginVersion) || !bitStream.Read(playerVersionString))
		return false;

	return true;
}