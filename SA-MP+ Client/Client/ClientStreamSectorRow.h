#pragma once

#define WORLD_SIZE 6000.0f

#include <list>

class ClientStreamSector;
class ClientStreamer;

class ClientStreamSectorRow
{
	friend class ClientStreamer;

private:
	const float sectorSize;
	const float rowSize;
	float bottomValue, topValue;
	std::list<ClientStreamSector*> sectors;
	bool extra;
	ClientStreamSectorRow *top, *bottom;

	bool isExtra() { return extra; }
	void setExtra(bool extra) { this->extra = extra; }

public:
	ClientStreamSectorRow(float bottom, float top, float sectorSize, float rowSize);
	~ClientStreamSectorRow();

	std::list<ClientStreamSector*>::iterator begin() { return sectors.begin(); }
	std::list<ClientStreamSector*>::iterator end() { return sectors.end(); }
	ClientStreamSector* front() { return sectors.front(); }
	void add(ClientStreamSector* sector);
	void remove(ClientStreamSector* sector);
	unsigned int countSectors() { return sectors.size(); }

	bool doesContain(CVector& position);
	bool doesContain(float y);

	ClientStreamSector* findOrCreateSector(CVector& position, ClientStreamSector* surrounding = NULL);
	ClientStreamSector* findSector(float y);

	void connectSector(ClientStreamSector* sector);

	void getPosition(float& tpo, float& bottom)
	{
		top = this->top;
		bottom = this->bottomValue;
	}
};