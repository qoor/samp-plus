#include "StdInc.h"

#include "CDirect3DHook9.h"
#include "CD3D9Proxy.h"

#include <Detours/detours.h>

template <>
CDirect3DHook9* CSingleton<CDirect3DHook9>::m_pSingleton = NULL;

CDirect3DHook9::CDirect3DHook9()
{
	direct3DCreate9 = NULL;
	direct3DCreate9Suspend = false;
}

CDirect3DHook9::~CDirect3DHook9()
{
	direct3DCreate9 = NULL;
}

bool CDirect3DHook9::applyHook()
{
	if (direct3DCreate9 == NULL)
	{
		char moduleName[] = "D3D9.dll";
		char functionName[] = "Direct3DCreate9";

		PBYTE function = DetourFindFunction(moduleName, functionName);

		if (function != NULL)
			direct3DCreate9 = reinterpret_cast<pDirect3DCreate>(DetourFunction(function, reinterpret_cast<PBYTE>(API_Direct3DCreate9)));
	}

	return true;
}

bool CDirect3DHook9::removeHook()
{
	direct3DCreate9Suspend = true;

	return true;
}

IDirect3D9* CDirect3DHook9::API_Direct3DCreate9(UINT SDKVersion)
{
	CDirect3DHook9* pThis = CDirect3DHook9::GetSingletonPtr();

	if (pThis->direct3DCreate9Suspend == true)
		return pThis->direct3DCreate9(SDKVersion);

	if (!Core::GetSingleton().areModulesLoaded())
	{
		Core::GetSingleton().setModulesLoaded(true);
		Core::GetSingleton().createNetwork();
		Core::GetSingleton().createGame();
		Core::GetSingleton().createMultiplayer();
	}

	IDirect3D9* pDirect3D9 = pThis->direct3DCreate9(SDKVersion);

	if (pDirect3D9 == NULL)
		return NULL;

	CD3D9Proxy* proxyDirect9 = new CD3D9Proxy(pDirect3D9);

	return proxyDirect9;
}