#include "StdInc.h"

#include "ClientStreamer.h"
#include "ClientStreamSector.h"
#include "ClientStreamSectorRow.h"
#include "ClientStreamElement.h"

void* ClientStreamer::addingElement = NULL;

ClientStreamer::ClientStreamer(StreamerLimitReachedFunction* limitReachedFunction, float maxDistance, float sectorSize, float rowSize)
	: sectorSize(sectorSize), rowSize(rowSize)
{
	maxDistanceExp = maxDistance * maxDistance;
	maxDistanceThreshold = (maxDistance + 50.0f) * (maxDistance + 50.0f);

	assert(limitReachedFunction);
	this->limitReachedFunction = limitReachedFunction;

	createSectors(&worldRows, CVector2D(this->sectorSize, this->rowSize), CVector2D(-WORLD_SIZE, -WORLD_SIZE), CVector2D(WORLD_SIZE, WORLD_SIZE));

	Debug::write("ºΩ≈Õ ¡ÿ∫Ò µ .");

	row = findOrCreateRow(position);
	sector = NULL;

	Debug::write("∑ŒøÏ ¡ÿ∫Ò µ .");

	onEnterSector(row->findOrCreateSector(position));

	Debug::write("onEnterSector »£√‚ µ .");
}

ClientStreamer::~ClientStreamer()
{
	std::list<ClientStreamSectorRow*>::iterator it = worldRows.begin();

	for (; it != worldRows.end(); ++it)
		delete *it;

	worldRows.clear();

	it = extraRows.begin();

	for (; it != extraRows.end(); ++it)
		delete *it;

	extraRows.clear();
}

void ClientStreamer::createSectors(std::list<ClientStreamSectorRow*>* list, const CVector2D& size, const CVector2D& bottomLeft, const CVector2D& topRight)
{
	ClientStreamSector *current = NULL, *previous = NULL, *previousRowSector = NULL;
	ClientStreamSectorRow *currentRow = NULL, *previousRow = NULL;
	float x = bottomLeft.fX, y = bottomLeft.fY;

	while (y < topRight.fY)
	{
		currentRow = new ClientStreamSectorRow(y, y + size.fY, sectorSize, rowSize);
		list->push_back(currentRow);
		currentRow->bottom = previousRow;

		if (previousRow != NULL)
			previousRow->top = currentRow;

		while (x < topRight.fX)
		{
			previous = current;
			current = new ClientStreamSector(currentRow, CVector2D(x, y), CVector2D(x + size.fX, y + size.fY));
			currentRow->add(current);
			current->left = previous;

			if (previous != NULL)
				previous->right = current;

			if (previousRowSector != NULL)
			{
				current->bottom = previousRowSector;
				previousRowSector->top = current;
				previousRowSector = previousRowSector->right;
			}

			x += size.fX;
		}

		previous = NULL;
		current = NULL;
		previousRow = currentRow;
		previousRowSector = previousRow->front();

		x = bottomLeft.fX;
		y += size.fY;
	}
}

void ClientStreamer::connectRow(ClientStreamSectorRow* row)
{
	float top, bottom;

	row->getPosition(top, bottom);

	row->top = findRow(top + (rowSize / 2.0f));
	row->bottom = findRow(bottom - (rowSize / 2.0f));

	if (row->top != NULL)
		row->top->bottom = row;
	if (row->bottom != NULL)
		row->bottom->top = row;
}

extern ClientGame* clientGame;
void ClientStreamer::doPulse(CVector& position)
{
	bool movedFar = false;

	if (position != this->position)
	{
		movedFar = ((this->position - position).LengthSquared() > (50 * 50));
		this->position = position;

		if (!row->doesContain(position))
		{
			row = findOrCreateRow(position, row);
			onEnterSector(row->findOrCreateSector(position));
		}
		else if (!sector->doesContain(position))
			onEnterSector(row->findOrCreateSector(position, sector));
	}

	setExpDistances(&activeElements);
	activeElements.sort(compareExpDistance);

	restream(movedFar);
}

ClientStreamSectorRow* ClientStreamer::findOrCreateRow(CVector& position, ClientStreamSectorRow* surrounding)
{
	if (surrounding != NULL)
	{
		if (surrounding->top != NULL && surrounding->top->doesContain(position))
			return surrounding->top;
		if (surrounding->bottom != NULL && surrounding->bottom->doesContain(position))
			return surrounding->bottom;
	}

	ClientStreamSectorRow* row = NULL;
	std::list<ClientStreamSectorRow*>::iterator it = worldRows.begin();

	for (; it != worldRows.end(); ++it)
	{
		row = *it;

		if (row->doesContain(position))
			return row;
	}

	it = extraRows.begin();

	for (; it != extraRows.end(); ++it)
	{
		row = *it;

		if (row->doesContain(position))
			return row;
	}

	float bottom = float((int)(position.fY / rowSize)) * rowSize;

	if (position.fY < 0.0f)
		bottom -= rowSize;

	row = new ClientStreamSectorRow(bottom, bottom + rowSize, sectorSize, rowSize);
	connectRow(row);
	row->setExtra(true);

	extraRows.push_back(row);

	return row;
}

ClientStreamSectorRow* ClientStreamer::findRow(float y)
{
	ClientStreamSectorRow* row = NULL;
	std::list<ClientStreamSectorRow*>::iterator it = worldRows.begin();

	for (; it != worldRows.end(); ++it)
	{
		row = *it;

		if (row->doesContain(y))
			return row;
	}

	it = extraRows.begin();

	for (; it != extraRows.end(); ++it)
	{
		row = *it;

		if (row->doesContain(y))
			return row;
	}

	return NULL;
}

void ClientStreamer::onUpdateStreamPosition(ClientStreamElement* element)
{
	CVector position = element->getStreamPosition();
	ClientStreamSectorRow* row = element->getStreamRow();
	ClientStreamSector* sector = element->getStreamSector();

	if (!row->doesContain(position))
	{
		row = findOrCreateRow(position);
		element->setStreamRow(row);
		onElementEnterSector(element, row->findOrCreateSector(position));
	}
	else if (!sector->doesContain(position))
		onElementEnterSector(element, row->findOrCreateSector(position, sector));
	else
		element->setExpDistance(element->getDistanceToBoundingBoxSquared(this->position));
}

void ClientStreamer::addElement(ClientStreamElement* element)
{
	assert(addingElement == NULL);
	addingElement = element;

	CVector position = element->getStreamPosition();
	Debug::write("1");
	ClientStreamSectorRow* row = findOrCreateRow(position);
	Debug::write("2");

	element->setStreamRow(row);
	Debug::write("3");
	onElementEnterSector(element, row->findOrCreateSector(position));
	Debug::write("4");

	addingElement = NULL;
}

void ClientStreamer::removeElement(ClientStreamElement* element)
{
	onElementEnterSector(element, NULL);
	activeElements.remove(element);
	toStreamOut.remove(element);
}

void ClientStreamer::setExpDistances(std::list<ClientStreamElement*>* list)
{
	ClientStreamElement* element = NULL;
	
	for (std::list<ClientStreamElement*>::iterator it = list->begin(); it != list->end(); ++it)
	{
		element = *it;
		element->setExpDistance(element->getDistanceToBoundingBoxSquared(position));
	}
}

void ClientStreamer::addToSortedList(std::list<ClientStreamElement*>* list, ClientStreamElement* element)
{
	float distance = element->getDistanceToBoundingBoxSquared(position);

	element->setExpDistance(distance);

	if (ListContains(*list, element))
		return;

	ClientStreamElement* temp = NULL;
	
	for (std::list<ClientStreamElement*>::iterator it = list->begin(); it != list->end(); ++it)
	{
		temp = *it;

		if (temp->getDistanceToBoundingBoxSquared(position))
		{
			list->insert(it, element);

			return;
		}
	}

	list->push_back(element);
}

bool ClientStreamer::compareExpDistance(ClientStreamElement* p1, ClientStreamElement* p2)
{
	return p1->getExpDistance() < p2->getExpDistance();
}

bool ClientStreamer::isActiveElement(ClientStreamElement* element)
{
	for (std::list<ClientStreamElement*>::iterator it = activeElements.begin(); it != activeElements.end(); ++it)
	{
		if (*it == element)
			return true;
	}

	return false;
}

void ClientStreamer::restream(bool movedFar)
{
	int maxOut = 6;
	int maxIn = 6;

	if (movedFar)
	{
		maxOut = 1000;
		maxIn = 1000;
	}

	while (!toStreamOut.empty())
	{
		ClientStreamElement* element = toStreamOut.front();

		if (element->getTotalStreamReferences() == 0)
		{
			element->internalStreamOut();
			--maxOut;
		}

		toStreamOut.remove(element);

		if (maxOut <= 0)
			break;
	}

	static std::vector<ClientStreamElement*> closestStreamedOutList;
	static std::vector<ClientStreamElement*> furthestStreamedInList;

	bool reachedLimitValue = reachedLimit();

	for (std::list<ClientStreamElement*>::iterator it = activeElements.begin(); it != activeElements.end(); ++it)
	{
		ClientStreamElement* element = *it;
		float elementDistanceExp = element->getExpDistance();

		if (element->isStreamedIn())
		{
			if (elementDistanceExp > maxDistanceThreshold)
			{
				if (maxOut > 0)
				{
					if (element->getTotalStreamReferences() == 0)
					{
						element->internalStreamOut();
						--maxOut;
					}

					toStreamOut.remove(element);
				}
				else
					toStreamOut.push_back(element);
			}
			else
				furthestStreamedInList.push_back(element);
		}
		else
		{
			if (elementDistanceExp > maxDistanceExp)
				continue;

			if (reachedLimitValue)
			{
				if ((int)closestStreamedOutList.size() < maxIn)
					closestStreamedOutList.push_back(element);
			}
			else
			{
				element->internalStreamIn(movedFar);
				reachedLimitValue = reachedLimit();

				if (!reachedLimitValue)
				{
					--maxIn;

					if (maxIn <= 0)
						break;
				}
			}
		}
	}

	if (reachedLimitValue)
	{
		int furthestStreamedInIndex = furthestStreamedInList.size() - 1;
		uint closestStreamedOutIndex = 0;

		for (uint i = 0; i < 10; ++i)
		{
			if (maxIn <= 0 || maxOut <= 0)
				break;

			if (furthestStreamedInIndex < 0)
				break;
			if (closestStreamedOutIndex >= closestStreamedOutList.size())
				break;

			ClientStreamElement* furthestStreamedIn = furthestStreamedInList[furthestStreamedInIndex];
			ClientStreamElement* closestStreamedOut = closestStreamedOutList[closestStreamedOutIndex];

			if (closestStreamedOut->getExpDistance() >= furthestStreamedIn->getExpDistance())
				break;

			if (furthestStreamedIn->getTotalStreamReferences() == 0)
			{
				furthestStreamedIn->internalStreamOut();
				--maxOut;
			}

			toStreamOut.remove(furthestStreamedIn);

			--furthestStreamedInIndex;

			if (!reachedLimit())
			{
				closestStreamedOut->internalStreamIn(movedFar);
				--maxIn;
				++closestStreamedOutIndex;
			}
		}
	}
}

void ClientStreamer::onEnterSector(ClientStreamSector* sector)
{
	Debug::write("onEnterSector()");
	ClientStreamElement* element = NULL;

	if (this->sector != NULL)
	{
		std::list<ClientStreamSector*> common, uncommon;

		sector->compareSurroundings(this->sector, &common, &uncommon, true);

		ClientStreamSector* tempSector = NULL;
		std::list<ClientStreamSector*>::iterator it = uncommon.begin();

		for (; it != uncommon.end(); ++it)
		{
			tempSector = *it;

			if (tempSector != sector)
			{
				if (tempSector->isActivated())
				{
					for (std::list<ClientStreamElement*>::iterator it = tempSector->begin(); it != tempSector->end(); ++it)
					{
						element = *it;

						if (element->isStreamedIn())
							toStreamOut.push_back(element);
					}

					tempSector->removeElements(&activeElements);
					tempSector->setActivated(false);
				}
			}
		}

		sector->compareSurroundings(sector, &common, &uncommon, true);

		for (it = uncommon.begin(); it != uncommon.end(); ++it)
		{
			tempSector = *it;

			if (!tempSector->isActivated())
			{
				tempSector->addElements(&activeElements);
				tempSector->setActivated(true);
			}
		}
	}

	this->sector = sector;
	setExpDistances(&activeElements);
	activeElements.sort(compareExpDistance);
}

void ClientStreamer::onElementEnterSector(ClientStreamElement* element, ClientStreamSector* sector)
{
	ClientStreamSector* previousSector = element->getStreamSector();

	if (previousSector != NULL)
	{
		if (clientGame->isBeingDeleted())
			return;

		previousSector->remove(element);
	}

	if (sector != NULL)
	{
		sector->add(element);

		if (sector->isActivated())
		{
			if (previousSector == NULL || !previousSector->isActivated())
				addToSortedList(&activeElements, element);
		}
		else
		{
			if (sector->isExtra() && (this->sector->isMySurroundSector(sector) || this->sector == sector))
			{
				sector->addElements(&activeElements);
				sector->setActivated(true);
			}
			else if (element->isStreamedIn())
				toStreamOut.push_back(element);
		}
	}

	element->setStreamSector(sector);
}

void ClientStreamer::onElementForceStreamIn(ClientStreamElement* element)
{
	element->internalStreamIn(true);
}

void ClientStreamer::onElementForceStreamOut(ClientStreamElement* element)
{
	if (isActiveElement(element))
		toStreamOut.push_back(element);
}
