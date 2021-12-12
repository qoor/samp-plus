#include "StdInc.h"

#include "StaticFunctionDefinations.h"

static Core* core;
static CGame* game;
static ClientGame* clientGame;
static ClientManager* manager;

StaticFunctionDefinations::StaticFunctionDefinations(Core* targetCore, CGame* targetGame, ClientGame* targetClientGame, ClientManager* targetManager)
{
	core = targetCore;
	game = targetGame;
	clientGame = targetClientGame;
	manager = targetManager;
}

bool StaticFunctionDefinations::getElementRadius(ClientEntity& entity, float& radius)
{
	return false;
}

bool StaticFunctionDefinations::getElementBoundingBox(ClientEntity& entity, CVector& min, CVector& max)
{
	return false;
}

ClientMarker* StaticFunctionDefinations::createMarker(int id, bool local, const CVector& position, const char* typeName, float size, const SColor color)
{
	assert(typeName);

	unsigned char type = ClientMarker::stringToType(typeName);

	if (type != ClientMarker::MARKER_INVALID)
	{
		Debug::write("마커 생성 시작.");
		ClientMarker* marker = new ClientMarker(manager, local, id, type);

		marker->setPosition(position);
		marker->setColor(color);
		marker->setSize(size);

		return marker;
	}

	return NULL;
}

bool StaticFunctionDefinations::destroyMarker(int markerid)
{
	ClientMarker* marker = manager->getMarkerManager()->get(markerid);

	if (marker != NULL)
	{
		delete marker;

		return true;
	}

	return false;
}
