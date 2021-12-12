#pragma once

#include "packets/Packet.h"

class PlayerManager
{
	friend class Player;

private:
	void addToList(Player* player);
	void removeFromList(Player* player);

	CMappedList<Player*> players;
	std::map<RakNet::SystemAddress, Player*> socketPlayerMap;

public:
	PlayerManager();
	~PlayerManager();

	void doPulse();

	Player* create(unsigned int playerid, const RakNet::SystemAddress& socket);
	void deleteAll();

	unsigned int count() { return static_cast<unsigned int>(players.size()); }
	unsigned int countJoined();
	bool exists(Player* player);

	Player* get(const RakNet::SystemAddress& playerSocket);
	Player* get(int playerid);

	std::list<Player*>::const_iterator iterBegin() { return players.begin(); }
	std::list<Player*>::const_iterator iterEnd() { return players.end(); }

	void broadcastOnlyJoined(const Packet& packet, Player* skip = NULL);

	static void broadcast(const Packet& packet, const std::list<Player*>& sendList);
};
