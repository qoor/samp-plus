#pragma once

#include <DirectX/d3d9.h>
#include <CSingleton.h>

typedef IDirect3D9*(__stdcall* pDirect3DCreate)(int SDKVersion);

class CDirect3DHook9 : public CSingleton<CDirect3DHook9>
{
public:
	pDirect3DCreate direct3DCreate9;
	bool direct3DCreate9Suspend;

	CDirect3DHook9();
	~CDirect3DHook9();

	static IDirect3D9* __stdcall API_Direct3DCreate9(UINT SDKVersion);

	bool applyHook();
	bool removeHook();
};
