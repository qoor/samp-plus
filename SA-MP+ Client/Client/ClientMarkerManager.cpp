#include "StdInc.h"

#include "ClientMarker.h"
#include "ClientMarkerManager.h"

ClientMarkerManager::ClientMarkerManager()
{

}

ClientMarkerManager::~ClientMarkerManager()
{
	deleteAll();
}

ClientMarker* ClientMarkerManager::get(int markerid)
{
	for (std::list<ClientMarker*>::iterator it = markers.begin(); it != markers.end(); ++it)
	{
		if ((*it)->getID() == markerid)
			return (*it);
	}

	return NULL;
}

void ClientMarkerManager::deleteAll()
{
	for (std::list<ClientMarker*>::iterator it = markers.begin(); it != markers.end(); ++it)
		delete *it;

	markers.clear();
}

void ClientMarkerManager::doPulse()
{
	for (std::list<ClientMarker*>::iterator it = markers.begin(); it != markers.end(); ++it)
		(*it)->doPulse();
}
