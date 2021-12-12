#pragma once

#include "ClientMarker.h"
#include <list>

class ClientMarkerManager
{
	friend class ClientGame;
	friend class ClientMarker;
	friend class ClientManager;

private:
	std::list<ClientMarker*> markers;

	ClientMarkerManager();
	~ClientMarkerManager();

	void doPulse();
	void addToList(ClientMarker* marker) { markers.push_back(marker); };
	void removeFromList(ClientMarker* marker) { markers.remove(marker); };

public:
	unsigned int count() { return static_cast<unsigned int>(markers.size()); };
	ClientMarker* get(int markerid);
	void deleteAll();
};
