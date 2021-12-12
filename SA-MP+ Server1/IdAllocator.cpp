#include "IdAllocator.h"

int IdAllocator::AllocateId()
{
	int id = -1;

	if (!removeIds.empty())
	{
		id = removeIds.top();

		removeIds.pop();
	}
	else
		id = (++idCount);

	return id;
}

int IdAllocator::DisallocateId(int id)
{
	if (id < 0)
		return 0;
	
	removeIds.push(id);

	return 1;
}
