/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        multiplayer_sa/multiplayersa_init.cpp
 *  PURPOSE:     Multiplayer module entry
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"
#define DECLARE_PROFILER_SECTION_multiplayersa_init
#include "profiler/SharedUtil.Profiler.h"

CGame*          pGameInterface = 0;
CMultiplayerSA* pMultiplayer = 0;
extern Network*           g_pNet;
extern Core* g_pCore;

//-----------------------------------------------------------
// This function uses the initialized data sections of the executables
// to differentiate between versions.  MUST be called at least once
// in order for proper initialization to occur.

CMultiplayer* InitMultiplayerInterface(Core* pCore)
{
    // set the internal pointer to the game class
	assert(g_pCore && g_pCore == pCore);
    pGameInterface = pCore->getGame();
    assert(pGameInterface);
    assert(g_pNet);

    // create an instance of our multiplayer class
    pMultiplayer = new CMultiplayerSA;
    pMultiplayer->InitHooks();

    // return the multiplayer class ptr
    return (CMultiplayer*)pMultiplayer;
}

//-----------------------------------------------------------

void OnCrashAverted(uint uiId)
{
    g_pCore->onCrashAverted(uiId);
}

void OnEnterCrashZone(uint uiId)
{
    g_pCore->onEnterCrashZone(uiId);
}

void CallGameEntityRenderHandler(CEntitySAInterface* pEntity)
{
    // Only call if not a building or a dummy
    if (!pEntity || (pEntity->nType != ENTITY_TYPE_BUILDING && pEntity->nType != ENTITY_TYPE_DUMMY))
        if (pGameEntityRenderHandler)
            pGameEntityRenderHandler(pEntity);
}
