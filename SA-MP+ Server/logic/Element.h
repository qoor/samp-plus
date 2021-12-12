#pragma once

class Element
{
protected:
	unsigned int id;

	void setID(unsigned int id) { this->id = id; }

public:
	Element(unsigned int id) : id(id) {}
	unsigned int getID() { return id; }
};
