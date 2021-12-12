#include "StdInc.h"

Core* core = NULL;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);

		core = new Core();

		break;

    case DLL_PROCESS_DETACH:
		if (core != NULL)
			delete core;

        break;
    }

    return TRUE;
}
