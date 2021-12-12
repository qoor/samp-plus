#pragma once

#include "IdAllocator.h"
#include <list>

class Entity
{
private:
	static IdAllocator* markerIdAllocator;
	static std::list<int> markers;

public:
	Entity();
	void createMarker(bool isLocal, float x, float y, float z, const char* type, float size, int r, int g, int b, int a);
	bool destroyMarker(int markerid);
};
