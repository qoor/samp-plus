/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        game_sa/gamesa_init.cpp
 *  PURPOSE:     Game initialization interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"
#define DECLARE_PROFILER_SECTION_gamesa_init
#include "profiler/SharedUtil.Profiler.h"

CGameSA*        pGame = NULL;
Network*           g_pNet = NULL;
Core* g_pCore = NULL;

//-----------------------------------------------------------
// This function uses the initialized data sections of the executables
// to differentiate between versions.  MUST be called at least once
// in order for proper initialization to occur.
CGame* GetGameInterface(Core* pCore)
{
    DEBUG_TRACE("CGame * GetGameInterface()");

    g_pNet = pCore->getNetwork();
    assert(g_pNet);

    pGame = new CGameSA;
    g_pCore = pCore;

    return (CGame*)pGame;
}

//-----------------------------------------------------------

void MemSet(void* dwDest, int cValue, uint uiAmount)
{
    if (ismemset(dwDest, cValue, uiAmount))
        return;
    SMemWrite hMem = OpenMemWrite(dwDest, uiAmount);
    memset(dwDest, cValue, uiAmount);
    CloseMemWrite(hMem);
}

void MemCpy(void* dwDest, const void* dwSrc, uint uiAmount)
{
    if (memcmp(dwDest, dwSrc, uiAmount) == 0)
        return;
    SMemWrite hMem = OpenMemWrite(dwDest, uiAmount);
    memcpy(dwDest, dwSrc, uiAmount);
    CloseMemWrite(hMem);
}

bool GetDebugIdEnabled(uint uiDebugId)
{
    return g_pCore->getDebugIdEnabled(uiDebugId);
}

void LogEvent(uint uiDebugId, const char* szType, const char* szContext, const char* szBody, uint uiAddReportLogId)
{
    g_pCore->logEvent(uiDebugId, szType, szContext, szBody, uiAddReportLogId);
}
