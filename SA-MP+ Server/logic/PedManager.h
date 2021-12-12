#pragma once

class PedManager
{
	friend class Ped;

protected:
	std::list<class Ped*> list;

	void addToList(class Ped* ped) { list.push_back(ped); }
	void removeFromList(class Ped* ped);

public:
	PedManager();
	~PedManager();

	void deleteAll();

	unsigned int count() { return static_cast<unsigned int>(list.size()); }
	bool exists(class Ped* ped);

	std::list<class Ped*>::const_iterator iterBegin() { return list.begin(); }
	std::list<class Ped*>::const_iterator iterEnd() { return list.end(); }
};
