/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        multiplayer_sa/multiplayer_hooksystem.cpp
 *  PURPOSE:     Multiplayer module hook system methods
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

#define MAX_JUMPCODE_SIZE 50

VOID HookInstallMethod(DWORD dwInstallAddress, DWORD dwHookFunction)
{
    MemPut<DWORD>(dwInstallAddress, dwHookFunction);
}

VOID HookInstallCall(DWORD dwInstallAddress, DWORD dwHookFunction)
{
    DWORD dwOffset = dwHookFunction - (dwInstallAddress + 5);
    MemPut<BYTE>(dwInstallAddress, 0xE8);
    MemPut<DWORD>(dwInstallAddress + 1, dwOffset);
}

////////////////////////////////////////////////////////////////////

VOID HookCheckOriginalByte(DWORD dwInstallAddress, uchar ucExpectedValue)
{
    uchar ucValue = *(uchar*)dwInstallAddress;
    dassert(ucValue == ucExpectedValue);
    if (ucValue != ucExpectedValue)
        AddReportLog(8423, SString("HookCheckOriginalByte failed at %08x - Got %02x - expected %02x", dwInstallAddress, ucValue, ucExpectedValue));
}
