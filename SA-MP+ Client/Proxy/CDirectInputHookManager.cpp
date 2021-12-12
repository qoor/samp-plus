#include "StdInc.h"

#include "CDirectInputHookManager.h"

CDirectInputHookManager::CDirectInputHookManager()
{
	directInputHook8 = NULL;
}

CDirectInputHookManager::~CDirectInputHookManager()
{
	if (directInputHook8 != NULL)
	{
		delete directInputHook8;
		directInputHook8 = NULL;
	}
}

void CDirectInputHookManager::applyHook()
{
	PBYTE directInput8 = reinterpret_cast<PBYTE>(LoadLibrary("DINPUT8.DLL"));

	if (directInput8 != NULL)
	{
		directInputHook8 = new CDirectInputHook8();
		directInputHook8->applyHook();
	}
}

void CDirectInputHookManager::removeHook()
{
	if (directInputHook8 != NULL)
		directInputHook8->removeHook();
}