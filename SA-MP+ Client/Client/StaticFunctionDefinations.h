#pragma once

class StaticFunctionDefinations
{
public:
	StaticFunctionDefinations(Core* targetCore, CGame* targetGame, ClientGame* targetClientGame, ClientManager* targetManager);

	static bool getElementRadius(ClientEntity& entity, float& fRadius);
	static bool getElementBoundingBox(ClientEntity& entity, CVector& min, CVector& max);

	static ClientMarker* createMarker(int id, bool local, const CVector& position, const char* typeName, float size, const SColor color);
	static bool destroyMarker(int markerid);
};
