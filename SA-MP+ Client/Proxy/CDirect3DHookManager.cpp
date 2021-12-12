#include "StdInc.h"

#include "CDirect3DHookManager.h"

CDirect3DHookManager::CDirect3DHookManager()
{
	direct3DHook9 = NULL;
}

CDirect3DHookManager::~CDirect3DHookManager()
{
	if (direct3DHook9 != NULL)
	{
		direct3DHook9->removeHook();
		delete direct3DHook9;
	}
}

void CDirect3DHookManager::applyHook()
{
	if (direct3DHook9 != NULL)
		return;

	PBYTE direct3D9 = reinterpret_cast<PBYTE>(LoadLibrary("D3D9.DLL"));

	if (direct3D9 != NULL)
	{
		direct3DHook9 = new CDirect3DHook9();
		direct3DHook9->applyHook();
	}
}