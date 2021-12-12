#include "Entity.h"
#include "Core.h"

IdAllocator* Entity::markerIdAllocator = NULL;
std::list<int> Entity::markers;

Entity::Entity()
{
	markerIdAllocator = new IdAllocator();
}

void Entity::createMarker(bool isLocal, float x, float y, float z, const char* type, float size, int r, int g, int b, int a)
{
	int markerid = markerIdAllocator->AllocateId();
	RakNet::BitStream bitStream;

	bitStream.Write(isLocal);
	bitStream.Write(markerid);
	bitStream.Write(x);
	bitStream.Write(y);
	bitStream.Write(z);
	bitStream.Write(type);
	bitStream.Write(size);
	bitStream.Write(r);
	bitStream.Write(g);
	bitStream.Write(b);
	bitStream.Write(a);

	core->getNetwork()->sendBroadcastRPC(CREATE_MARKER, &bitStream);

	markers.push_back(markerid);
}

bool Entity::destroyMarker(int markerid)
{
	bool orderDestroy = false;

	for (std::list<int>::iterator it = markers.begin(); it != markers.end(); ++it)
	{
		if (*it == markerid)
		{
			RakNet::BitStream bitStream;

			bitStream.Write(markerid);
			core->getNetwork()->sendBroadcastRPC(DESTROY_MARKER, &bitStream);

			markers.remove(markerid);

			return true;
		}
	}

	return false;
}
