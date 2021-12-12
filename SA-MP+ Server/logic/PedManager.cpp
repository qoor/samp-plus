#include "StdInc.h"

PedManager::PedManager()
{

}

PedManager::~PedManager()
{
	deleteAll();
}

void PedManager::deleteAll()
{
	for (std::list<Ped*>::const_iterator it = list.begin(); it != list.end(); ++it)
		delete *it;

	list.clear();
}

void PedManager::removeFromList(Ped* ped)
{
	list.remove(ped);
}

bool PedManager::exists(Ped* ped)
{
	return ListContains(list, ped);
}
