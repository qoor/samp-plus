#include "HookManager.h"
#include "Memory.h"
#include "Game.h"

#include <SA-MP+/Debug.h>
#include <Detours/detours.h>

Direct3DCreate9_t HookManager::directX9Handler = NULL;

DWORD HookManager::onWorldCreateJumpBack;

HookManager::HookManager()
{
	installPatches();
	//addDirectX9Hook();
	addGameEventHook();
}

HookManager::~HookManager()
{
	removeDirectX9Hook();
}

void HookManager::installPatches()
{
	Memory::memCopy((void*)0x0401190, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10); // NOP SetGameSpeed to 1.0 every frame
	Memory::memCopy((void*)0x060CD41, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10); // NOP SetGameSpeed to 1.0 on player death
}

void HookManager::addDirectX9Hook()
{
	if (directX9Handler != NULL)
		return;

	PCHAR moduleFile = const_cast<PCHAR>("d3d9.dll");
	PCHAR functionName = const_cast<PCHAR>("Direct3DCreate9");

	directX9Handler = reinterpret_cast<Direct3DCreate9_t>(DetourFunction(DetourFindFunction(moduleFile, functionName), reinterpret_cast<BYTE*>(HOOK_Direct3DCreate9)));
}

void HookManager::removeDirectX9Hook()
{
	if (directX9Handler == NULL)
		return;

	DetourRemove(reinterpret_cast<BYTE*>(directX9Handler), reinterpret_cast<BYTE*>(HOOK_Direct3DCreate9));
}

void HookManager::addGameEventHook()
{
	Memory::InstallJmp(HOOKPOS_WorldCreate, (DWORD)HookManager::onWorldCreate, onWorldCreateJumpBack, 6);
}

IDirect3D9* WINAPI HookManager::HOOK_Direct3DCreate9(UINT SDKVersion)
{
	IDirect3D9* Direct3D = directX9Handler(SDKVersion);
	IDirect3D9* mineDirect3D = new CD3D9Proxy(Direct3D);

	return mineDirect3D;
}

__declspec(naked) void HookManager::onWorldCreate()
{
	__asm
	{
		pushad
		call Game::onWorldCreate
		popad
		mov[eax], edx
		movzx eax, byte ptr[esi + 0x59]
		jmp[onWorldCreateJumpBack]
	}
}
