#pragma once

#include "CDirect3DHook9.h"

class CDirect3DHookManager
{
private:
	CDirect3DHook9* direct3DHook9;

public:
	CDirect3DHookManager();
	~CDirect3DHookManager();

	void applyHook();
	void removeHook();
};
