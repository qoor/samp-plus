#pragma once

#include <list>

class ClientStreamSector;
class ClientStreamSectorRow;
class ClientStreamElement;
typedef bool(StreamerLimitReachedFunction)(void);

class ClientStreamer
{
	friend class ClientStreamElement;

private:
	void createSectors(std::list<ClientStreamSectorRow*>* list, const CVector2D& size, const CVector2D& bottomLeft, const CVector2D& topRight);
	void connectSector(ClientStreamSector* sector);
	void connectRow(ClientStreamSectorRow* row);

	ClientStreamSectorRow* findOrCreateRow(CVector& position, ClientStreamSectorRow* surrounding = NULL);
	ClientStreamSectorRow* findRow(float y);
	void onUpdateStreamPosition(ClientStreamElement* element);

	void addElement(ClientStreamElement* element);
	void removeElement(ClientStreamElement* element);

	void setExpDistances(std::list<ClientStreamElement*>* list);
	void addToSortedList(std::list<ClientStreamElement*>* list, ClientStreamElement* element);


	void restream(bool movedFar);
	bool reachedLimit() { return limitReachedFunction(); }

	void onEnterSector(ClientStreamSector* sector);
	void onElementEnterSector(ClientStreamElement* element, ClientStreamSector* sector);
	void onElementForceStreamIn(ClientStreamElement* element);
	void onElementForceStreamOut(ClientStreamElement* element);
	
	const float sectorSize;
	const float rowSize;
	float maxDistanceExp;
	float maxDistanceThreshold;
	StreamerLimitReachedFunction* limitReachedFunction;
	std::list<ClientStreamSectorRow*> worldRows;
	std::list<ClientStreamSectorRow*> extraRows;
	ClientStreamSectorRow* row;
	ClientStreamSector* sector;
	CVector position;
	std::list<ClientStreamElement*> activeElements;
	std::list<ClientStreamElement*> toStreamOut;

	static void* addingElement;

public:
	ClientStreamer(StreamerLimitReachedFunction* limitReachedFunction, float maxDistance, float sectorSize, float rowSize);
	~ClientStreamer();

	void doPulse(CVector& position);

	static bool compareExpDistance(ClientStreamElement* p1, ClientStreamElement* p2);

	unsigned int countActiveElements();
	bool isActiveElement(ClientStreamElement* element);

	std::list<ClientStreamElement*>::iterator activeElementsBegin() { return activeElements.begin(); }
	std::list<ClientStreamElement*>::iterator activeElementsEnd() { return activeElements.end(); }
};
