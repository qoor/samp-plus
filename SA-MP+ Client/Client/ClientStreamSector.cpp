#include "StdInc.h"

#include "ClientStreamSector.h"

ClientStreamSector::ClientStreamSector(ClientStreamSectorRow* row, const CVector2D& bottomLeft, const CVector2D& topRight)
{
	this->row = row;
	this->bottomLeft = bottomLeft;
	this->topRight = topRight;
	left = NULL;
	right = NULL;
	top = NULL;
	bottom = NULL;
	activated = false;
	extra = false;
}

ClientStreamSector::~ClientStreamSector()
{
	if (left != NULL)
		left->right = NULL;
	if (right != NULL)
		right->left = NULL;
	if (top != NULL)
		top->bottom = NULL;
	if (bottom != NULL)
		bottom->top = NULL;
}

bool ClientStreamSector::doesContain(CVector& position)
{
	if (position.fX >= bottomLeft.fX && position.fX < topRight.fX)
	{
		if (position.fY >= bottomLeft.fY && position.fY < topRight.fY)
			return true;
	}

	return false;
}

bool ClientStreamSector::doesContain(float x)
{
	if (x >= bottomLeft.fX && x < topRight.fX)
		return true;

	return false;
}

void ClientStreamSector::getSurroundingSectors(ClientStreamSector** sectorArray)
{
	memset(sectorArray, 0, sizeof(sectorArray) * 8);

	sectorArray[1] = top;
	sectorArray[3] = left;
	sectorArray[4] = right;
	sectorArray[6] = bottom;

	if (top != NULL)
	{
		sectorArray[0] = top->left;
		sectorArray[2] = top->right;
	}
	else
	{
		if (left != NULL)
			sectorArray[0] = left->top;
		if (right != NULL)
			sectorArray[2] = right->top;
	}

	if (bottom != NULL)
	{
		sectorArray[5] = bottom->left;
		sectorArray[7] = bottom->right;
	}
	else
	{
		if (left != NULL)
			sectorArray[5] = left->bottom;
		if (right != NULL)
			sectorArray[7] = right->bottom;
	}
}

bool ClientStreamSector::isMySurroundSector(ClientStreamSector* sector)
{
	ClientStreamSector* surrounding[8];

	getSurroundingSectors(surrounding);

	for (int i = 0; i < 8; ++i)
	{
		if (surrounding[i] && surrounding[i] == sector)
			return true;
	}

	return false;
}

void ClientStreamSector::compareSurroundings(ClientStreamSector* sector, std::list<ClientStreamSector*>* common, std::list<ClientStreamSector*>* uncommon, bool includeCenter)
{
	Debug::write("compareSurroundings()");

	common->clear();
	uncommon->clear();

	ClientStreamSector* surrounding[8];

	sector->getSurroundingSectors(surrounding);

	for (int i = 0; i < 8; ++i)
	{
		if (surrounding[i] != NULL)
		{
			if (isMySurroundSector(surrounding[i]))
				common->push_back(surrounding[i]);
			else
				uncommon->push_back(surrounding[i]);
		}
	}

	if (includeCenter)
	{
		if (isMySurroundSector(sector))
			common->push_back(sector);
		else
			uncommon->push_back(sector);
	}
}

void ClientStreamSector::addElements(std::list<ClientStreamElement*>* list)
{
	for (std::list<ClientStreamElement*>::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		if (ListContains(*list, *it))
			continue;

		list->push_back(*it);
	}
}

void ClientStreamSector::removeElements(std::list<ClientStreamElement*>* list)
{
	for (std::list<ClientStreamElement*>::iterator it = elements.begin(); it != elements.end(); ++it)
		list->remove(*it);
}
