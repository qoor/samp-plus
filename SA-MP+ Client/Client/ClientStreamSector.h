#pragma once

#include <list>

class ClientStreamer;
class ClientStreamElement;
class ClientStreamSectorRow;

class ClientStreamSector
{
	friend class ClientStreamer;
	friend class ClientStreamSectorRow;

private:
	CVector2D bottomLeft;
	CVector2D topRight;
	std::list<ClientStreamElement*> elements;
	ClientStreamSector *left, *right, *top, *bottom;
	ClientStreamSectorRow* row;
	bool activated;
	bool extra;

	bool isActivated() { return activated; }
	void setActivated(bool activated) { this->activated = activated; }

	bool isExtra() { return extra; }
	void setExtra(bool extra) { this->extra = extra; }

public:
	ClientStreamSector(ClientStreamSectorRow* row, const CVector2D& bottomLeft, const CVector2D& topRight);
	~ClientStreamSector();

	bool doesContain(CVector& position);
	bool doesContain(float x);
	void getSurroundingSectors(ClientStreamSector** sectorArray);
	bool isMySurroundSector(ClientStreamSector* sector);
	void compareSurroundings(ClientStreamSector* sector, std::list<ClientStreamSector*>* common, std::list<ClientStreamSector*>* uncommon, bool includeCenter);

	void add(ClientStreamElement* element) { elements.push_back(element); }
	void remove(ClientStreamElement* element) { elements.remove(element); }
	std::list<ClientStreamElement*>::iterator begin() { return elements.begin(); }
	std::list<ClientStreamElement*>::iterator end() { return elements.end(); }

	void addElements(std::list<ClientStreamElement*>* list);
	void removeElements(std::list<ClientStreamElement*>* list);
	unsigned int countElements() { return elements.size(); }

	ClientStreamSectorRow* getRow() { return row; }
	void getCorners(CVector2D& bottomLeft, CVector2D& topRight)
	{
		bottomLeft = this->bottomLeft;
		topRight = this->topRight;
	}
};
