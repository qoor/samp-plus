#include "StdInc.h"

#include "ClientStreamSector.h"
#include "ClientStreamSectorRow.h"

ClientStreamSectorRow::ClientStreamSectorRow(float bottom, float top, float sectorSize, float rowSize) : sectorSize(sectorSize), rowSize(rowSize)
{
	this->bottomValue = bottom;
	this->topValue = top;
	extra = false;
	this->top = NULL;
	this->bottom = NULL;
}

ClientStreamSectorRow::~ClientStreamSectorRow()
{
	for (std::list<ClientStreamSector*>::iterator it = sectors.begin(); it != sectors.end(); ++it)
		delete *it;

	sectors.clear();
}

void ClientStreamSectorRow::add(ClientStreamSector* sector)
{
	sectors.push_back(sector);
	sector->row = this;
}

void ClientStreamSectorRow::remove(ClientStreamSector* sector)
{
	sectors.remove(sector);
}

bool ClientStreamSectorRow::doesContain(CVector& position)
{
	return (position.fY >= bottomValue && position.fY < topValue);
}

bool ClientStreamSectorRow::doesContain(float y)
{
	return (y >= bottomValue && y < topValue);
}

ClientStreamSector* ClientStreamSectorRow::findOrCreateSector(CVector& position, ClientStreamSector* surrounding)
{
	if (surrounding != NULL)
	{
		if (surrounding->left != NULL && surrounding->left->doesContain(position))
			return surrounding->left;
		if (surrounding->right != NULL && surrounding->right->doesContain(position))
			return surrounding->right;
	}

	ClientStreamSector* sector = NULL;
	std::list<ClientStreamSector*>::iterator it = sectors.begin();

	for (; it != sectors.end(); ++it)
	{
		sector = *it;

		if (sector->doesContain(position.fX))
			return sector;
	}

	float left = float((int)(position.fX / sectorSize)) * sectorSize;

	if (position.fX < 0.0f)
		left -= sectorSize;

	CVector2D bottomLeft(left, bottomValue);
	CVector2D topRight(bottomLeft.fX + sectorSize, bottomLeft.fY + rowSize);

	sector = new ClientStreamSector(this, bottomLeft, topRight);
	connectSector(sector);
	sector->setExtra(true);
	
	sectors.push_back(sector);

	return sector;
}

ClientStreamSector* ClientStreamSectorRow::findSector(float x)
{
	ClientStreamSector* sector = NULL;
	
	for (std::list<ClientStreamSector*>::iterator it = sectors.begin(); it != sectors.end(); ++it)
	{
		sector = *it;

		if (sector->doesContain(x))
			return sector;
	}

	return NULL;
}

void ClientStreamSectorRow::connectSector(ClientStreamSector* sector)
{
	CVector2D bottomLeft, topRight;

	sector->getCorners(bottomLeft, topRight);

	sector->left = findSector(bottomLeft.fX - (sectorSize / 2.0f));
	sector->right = findSector(topRight.fX + (sectorSize / 2.0f));

	if (top != NULL)
		sector->top = top->findSector(bottomLeft.fX);
	if (bottom != NULL)
		sector->bottom = bottom->findSector(bottomLeft.fX);

	if (sector->left != NULL)
		sector->left->right = sector;
	if (sector->right != NULL)
		sector->right->left = sector;
	if (sector->top != NULL)
		sector->top->bottom = sector;
	if (sector->bottom != NULL)
		sector->bottom->top = sector;
}
