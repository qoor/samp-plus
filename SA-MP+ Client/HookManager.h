#pragma once

#include "Proxy/CD3D9Proxy.h"

#define HOOKPOS_WorldCreate 0x52B811

typedef IDirect3D9 *(WINAPI* Direct3DCreate9_t)(UINT);

class HookManager
{
private:
	static Direct3DCreate9_t directX9Handler;
	static DWORD onWorldCreateJumpBack;

public:
	HookManager();
	~HookManager();
	void installPatches();
	void addDirectX9Hook();
	void removeDirectX9Hook();
	void addGameEventHook();
	static IDirect3D9* WINAPI HOOK_Direct3DCreate9(UINT SDKVersion);
	static void onWorldCreate();
};
