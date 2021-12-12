#pragma once

#include <iostream>
#include <queue>

#define MIN_ID_BUFFER_AMOUNT 10

class IdAllocator
{
private:
	int idCount;
	std::priority_queue<int, std::vector<int>, std::greater<int>> removeIds;

public:
	IdAllocator() : idCount(-1) {}
	~IdAllocator() {}

	int AllocateId();
	int DisallocateId(int id);
};
